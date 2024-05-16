import {
    compileShader
} from "../../lib/utils";

import {
    initAttributeVariable,
    initVertexBufferForLaterUse3D,
    initFrameBufferForCubemapRendering,
    initCubeTexture
} from "../../lib/init";

import {
    parseOBJ
} from "../../lib/cube";

import {
    Matrix4,
    Vector3
} from "../../lib/cuon-matrix"

const VSHADER_SOURCE = `
    attribute vec4 a_Position;
    attribute vec4 a_Normal;
    uniform mat4 u_MvpMatrix;
    uniform mat4 u_modelMatrix;
    uniform mat4 u_normalMatrix;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    void main()
    {
        gl_Position = u_MvpMatrix * a_Position;
        v_PositionInWorld = (u_modelMatrix * a_Position).xyz; 
        v_Normal = normalize(vec3(u_normalMatrix * a_Normal));
    }    
`;

const FSHADER_SOURCE = `
    precision mediump float;
    uniform vec3 u_LightPosition;
    uniform vec3 u_ViewPosition;
    uniform float u_Ka;
    uniform float u_Kd;
    uniform float u_Ks;
    uniform vec3 u_Color;
    uniform float u_shininess;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    void main()
    {
        // (you can also input them from ouside and make them different)
        vec3 ambientLightColor = u_Color.rgb;
        vec3 diffuseLightColor = u_Color.rgb;
        // assume white specular light (you can also input it from ouside)
        vec3 specularLightColor = vec3(1.0, 1.0, 1.0);        

        vec3 ambient = ambientLightColor * u_Ka;

        vec3 normal = normalize(v_Normal);
        vec3 lightDirection = normalize(u_LightPosition - v_PositionInWorld);
        float nDotL = max(dot(lightDirection, normal), 0.0);
        vec3 diffuse = diffuseLightColor * u_Kd * nDotL;

        vec3 specular = vec3(0.0, 0.0, 0.0);
        if(nDotL > 0.0) {
            vec3 R = reflect(-lightDirection, normal);
            // V: the vector, point to viewer       
            vec3 V = normalize(u_ViewPosition - v_PositionInWorld); 
            float specAngle = clamp(dot(R, V), 0.0, 1.0);
            specular = u_Ks * pow(specAngle, u_shininess) * specularLightColor; 
        }

        gl_FragColor = vec4( ambient + diffuse + specular, 1.0 );
    }
`;

const VSHADER_SOURCE_TEXTURE_ON_CUBE = `
    attribute vec4 a_Position;
    attribute vec4 a_Normal;
    uniform mat4 u_MvpMatrix;
    uniform mat4 u_modelMatrix;
    uniform mat4 u_normalMatrix;
    varying vec4 v_TexCoord;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    void main() {
        gl_Position = u_MvpMatrix * a_Position;
        v_TexCoord = a_Position;
        v_PositionInWorld = (u_modelMatrix * a_Position).xyz; 
        v_Normal = normalize(vec3(u_normalMatrix * a_Normal));
    } 
`;

const FSHADER_SOURCE_TEXTURE_ON_CUBE = `
    precision mediump float;
    varying vec4 v_TexCoord;
    uniform vec3 u_ViewPosition;
    uniform vec3 u_Color;
    uniform samplerCube u_envCubeMap;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    void main() 
    {
        vec3 V = normalize(u_ViewPosition - v_PositionInWorld); 
        vec3 normal = normalize(v_Normal);
        vec3 R = reflect(-V, normal);
        gl_FragColor = vec4(0.78 * textureCube(u_envCubeMap, R).rgb + 0.3 * u_Color, 1.0);
    }
`;

const VSHADER_QUAD_SOURCE = `
    attribute vec4 a_Position;
    varying vec4 v_Position;
    void main() 
    {
        v_Position = a_Position;
        gl_Position = a_Position;
    } 
`;

const FSHADER_QUAD_SOURCE = `
    precision mediump float;
    uniform samplerCube u_envCubeMap;
    uniform mat4 u_viewDirectionProjectionInverse;
    varying vec4 v_Position;
    void main() 
    {
        vec4 t = u_viewDirectionProjectionInverse * v_Position;
        gl_FragColor = textureCube(u_envCubeMap, normalize(t.xyz / t.w));
    }
`;

let mouseLastX:number, mouseLastY:number;
let mouseDragging = false;
let angleX = 0, angleY = 0;

let gl: WebGL2RenderingContext | null;
let canvas: HTMLCanvasElement | null;

let cameraX = 0, cameraY = 1, cameraZ = 7;
const cameraDirX = 0, cameraDirY = 0, cameraDirZ = -1;

const lightX = 5, lightY = 1, lightZ = 7;

let quadObj: any;
let cubeMapTex: WebGLTexture | null;

let quadProgram: WebGLProgram;
let quad_a_Position: number;
let quad_u_envCubeMap: WebGLUniformLocation | null;
let quad_u_viewDirectionProjectionInverse: WebGLUniformLocation | null;

let sphereObj: any;
let marioObj: any;
let sonicObj: any;

let rotateAngle = 0;
let fbo: any;

const offScreenWidth = 256, offScreenHeight = 256; //for cubemap render

let program: WebGLProgram;

let a_Position: number;
let a_Normal: number;
let u_MvpMatrix: WebGLUniformLocation | null;
let u_modelMatrix: WebGLUniformLocation | null;
let u_normalMatrix: WebGLUniformLocation | null;
let u_LightPosition: WebGLUniformLocation | null;
let u_ViewPosition: WebGLUniformLocation | null;
let u_Ka: WebGLUniformLocation | null;
let u_Kd: WebGLUniformLocation | null;
let u_Ks: WebGLUniformLocation | null;
let u_Color: WebGLUniformLocation | null;
let u_shininess: WebGLUniformLocation | null;

let programTextureOnCube: WebGLProgram;
let programTextureOnCube_a_Position: number;
let programTextureOnCube_a_Normal: number;
let programTextureOnCube_u_MvpMatrix: WebGLUniformLocation | null;
let programTextureOnCube_u_modelMatrix: WebGLUniformLocation | null;
let programTextureOnCube_u_normalMatrix: WebGLUniformLocation | null;
let programTextureOnCube_u_ViewPosition: WebGLUniformLocation | null;
let programTextureOnCube_u_envCubeMap: WebGLUniformLocation | null;
let programTextureOnCube_u_Color: WebGLUniformLocation | null;

main();
async function main()
{
    canvas = document.getElementById("webgl") as HTMLCanvasElement | null;
    if(canvas == null) throw new Error("Canvas is null");

    gl = canvas.getContext("webgl2");
    if(!gl)
    {
        console.log("Failed to get the rendering context for WebGL");
        return;
    }

    const quad: number[] = [
        -1, -1, 1,
        1, -1, 1,
        -1, 1, 1,
        -1, 1, 1,
        1, -1, 1,
        1, 1, 1,
    ]; // just a quad

    quadProgram = compileShader(gl, VSHADER_QUAD_SOURCE, FSHADER_QUAD_SOURCE);
    quad_a_Position = gl.getAttribLocation(quadProgram, "a_Position");
    quad_u_envCubeMap = gl.getUniformLocation(quadProgram, "u_envCubeMap");
    quad_u_viewDirectionProjectionInverse = gl.getUniformLocation(quadProgram, "u_viewDirectionProjectionInverse");

    quadObj = initVertexBufferForLaterUse3D(gl, quad, null, null);

    cubeMapTex = initCubeTexture(
        gl,
        "pos-x.jpg",
        "neg-x.jpg",
        "pos-y.jpg",
        "neg-y.jpg",
        "pos-z.jpg",
        "neg-z.jpg",
        512,
        512
    );

    sphereObj = await loadOBJtoCreateVBO("sphere.obj");
    sonicObj = await loadOBJtoCreateVBO("sonic.obj");
    marioObj = await loadOBJtoCreateVBO("mario.obj");

    program = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);
    a_Position = gl.getAttribLocation(program, "a_Position"); 
    a_Normal = gl.getAttribLocation(program, "a_Normal"); 
    u_MvpMatrix = gl.getUniformLocation(program, "u_MvpMatrix"); 
    u_modelMatrix = gl.getUniformLocation(program, "u_modelMatrix"); 
    u_normalMatrix = gl.getUniformLocation(program, "u_normalMatrix");
    u_LightPosition = gl.getUniformLocation(program, "u_LightPosition");
    u_ViewPosition = gl.getUniformLocation(program, "u_ViewPosition");
    u_Ka = gl.getUniformLocation(program, "u_Ka"); 
    u_Kd = gl.getUniformLocation(program, "u_Kd");
    u_Ks = gl.getUniformLocation(program, "u_Ks");
    u_Color = gl.getUniformLocation(program, "u_Color");
    u_shininess = gl.getUniformLocation(program, "u_shininess");

    programTextureOnCube = compileShader(gl, VSHADER_SOURCE_TEXTURE_ON_CUBE, FSHADER_SOURCE_TEXTURE_ON_CUBE);
    programTextureOnCube_a_Position = gl.getAttribLocation(programTextureOnCube, "a_Position"); 
    programTextureOnCube_a_Normal = gl.getAttribLocation(programTextureOnCube, "a_Normal"); 
    programTextureOnCube_u_MvpMatrix = gl.getUniformLocation(programTextureOnCube, "u_MvpMatrix"); 
    programTextureOnCube_u_modelMatrix = gl.getUniformLocation(programTextureOnCube, "u_modelMatrix"); 
    programTextureOnCube_u_normalMatrix = gl.getUniformLocation(programTextureOnCube, "u_normalMatrix");
    programTextureOnCube_u_ViewPosition = gl.getUniformLocation(programTextureOnCube, "u_ViewPosition");
    programTextureOnCube_u_envCubeMap = gl.getUniformLocation(programTextureOnCube, "u_envCubeMap"); 
    programTextureOnCube_u_Color = gl.getUniformLocation(programTextureOnCube, "u_Color"); 
    
    fbo = initFrameBufferForCubemapRendering(gl, offScreenWidth, offScreenHeight);

    canvas.onmousedown = function(ev){mouseDown(ev)};
    canvas.onmousemove = function(ev){mouseMove(ev)};
    canvas.onmouseup = function(ev){mouseUp()}
    document.onkeydown = function(ev){keydown(ev)};

    const tick = function() 
    {
        rotateAngle += 0.45;
        draw();
        requestAnimationFrame(tick);
    }
    tick();
}

function draw()
{
    if (gl == null)
    {
        throw new Error("gl is null");
    }
    if (canvas == null)
    {
        throw new Error("canvas is null");
    }

    renderCubeMap(0, 0, 0);

    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.clearColor(0.4, 0.4, 0.4, 1);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.enable(gl.DEPTH_TEST);

    const rotateMatrix = new Matrix4();
    rotateMatrix.setRotate(angleY, 1, 0, 0); // for mouse rotation
    rotateMatrix.rotate(angleX, 0, 1, 0); // for mouse rotation
    const viewDir = new Vector3([cameraDirX, cameraDirY, cameraDirZ]);
    const newViewDir = rotateMatrix.multiplyVector3(viewDir);
    const vpMatrix = new Matrix4();
    vpMatrix.setPerspective(70, 1, 1, 100);
    vpMatrix.lookAt(
        cameraX, cameraY, cameraZ,   
        cameraX + newViewDir.elements[0], 
        cameraY + newViewDir.elements[1],
        cameraZ + newViewDir.elements[2], 
        0, 1, 0
    );

    const vpFromCamera = new Matrix4();
    vpFromCamera.setPerspective(60, 1, 1, 15);
    const viewMatrixRotationOnly = new Matrix4();
    viewMatrixRotationOnly.lookAt(
        cameraX, cameraY, cameraZ,
        cameraX + newViewDir.elements[0],
        cameraY + newViewDir.elements[1],
        cameraZ + newViewDir.elements[2],
        0, 1, 0
    );
    viewMatrixRotationOnly.elements[12] = 0; // ignore translation
    viewMatrixRotationOnly.elements[13] = 0;
    viewMatrixRotationOnly.elements[14] = 0;
    vpFromCamera.multiply(viewMatrixRotationOnly);
    const vpFromCameraInverse = vpFromCamera.invert();
    
    // quad
    gl.useProgram(quadProgram);
    gl.depthFunc(gl.LEQUAL);
    gl.uniformMatrix4fv(
        quad_u_viewDirectionProjectionInverse,
        false,
        vpFromCameraInverse.elements
    );
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_CUBE_MAP, cubeMapTex);
    gl.uniform1i(quad_u_envCubeMap, 0);
    
    initAttributeVariable(gl, quad_a_Position, quadObj.vertexBuffer);
    gl.drawArrays(gl.TRIANGLES, 0, quadObj.numVertices);

    drawRegularObjects(vpMatrix); // ground, mario, sonic
    
    // the sphere
    const mdlMatrix = new Matrix4();
    mdlMatrix.setScale(0.5, 0.5, 0.5);
    drawObjectWithDynamicReflection(
        sphereObj, mdlMatrix, vpMatrix,
        0.95, 0.85, 0.4
    );
}

function drawRegularObjects(vpMatrix: Matrix4)
{
    const mdlMatrix = new Matrix4();

    mdlMatrix.setRotate(rotateAngle, 0, 1, 0);
    mdlMatrix.translate(-2.0, -0.5, 2.0);
    mdlMatrix.scale(0.05, 0.05,0.05);
    drawOneRegularObject(sonicObj, mdlMatrix, vpMatrix, 0.4, 1.0, 0.4);

    mdlMatrix.setRotate(rotateAngle, 0, 1, 0);
    mdlMatrix.translate(2.5, -0.5, 1.5);
    mdlMatrix.scale(0.02, 0.02, 0.02);
    drawOneRegularObject(marioObj, mdlMatrix, vpMatrix, 1.0, 0.4, 0.4);
}

function drawOneRegularObject(
    obj: any, modelMatrix: Matrix4, vpMatrix: Matrix4,
    colorR: number, colorG: number, colorB: number
)
{
    if (gl == null)
    {
        throw new Error("gl is null");
    }

    gl.useProgram(program);
    const mvpMatrix = new Matrix4();
    const normalMatrix = new Matrix4();
    mvpMatrix.set(vpMatrix);
    mvpMatrix.multiply(modelMatrix);

    // normal matrix
    normalMatrix.setInverseOf(modelMatrix);
    normalMatrix.transpose();

    gl.uniform3f(u_LightPosition, lightX, lightY, lightZ);
    gl.uniform3f(u_ViewPosition, cameraX, cameraY, cameraZ);
    gl.uniform1f(u_Ka, 0.2);
    gl.uniform1f(u_Kd, 0.7);
    gl.uniform1f(u_Ks, 1.0);
    gl.uniform1f(u_shininess, 10.0);
    gl.uniform3f(u_Color, colorR, colorG, colorB);

    gl.uniformMatrix4fv(u_MvpMatrix, false, mvpMatrix.elements);
    gl.uniformMatrix4fv(u_modelMatrix, false, modelMatrix.elements);
    gl.uniformMatrix4fv(u_normalMatrix, false, normalMatrix.elements);

    for(let i = 0; i < obj.length; i++)
    {
        initAttributeVariable(gl, a_Position, obj[i].vertexBuffer);
        initAttributeVariable(gl, a_Normal, obj[i].normalBuffer);
        gl.drawArrays(gl.TRIANGLES, 0, obj[i].numVertices);
    }
}

function drawObjectWithDynamicReflection(
    obj: any, modelMatrix: Matrix4, vpMatrix: Matrix4,
    colorR: number, colorG: number, colorB: number
)
{
    if (gl == null)
    {
        throw new Error("gl is null");
    }

    gl.useProgram(programTextureOnCube);
    const mvpMatrix = new Matrix4();
    const normalMatrix = new Matrix4();
    mvpMatrix.set(vpMatrix);
    mvpMatrix.multiply(modelMatrix);

    // normal matrix
    normalMatrix.setInverseOf(modelMatrix);
    normalMatrix.transpose();

    gl.uniform3f(
        programTextureOnCube_u_ViewPosition,
        cameraX, cameraY, cameraZ
    );
    gl.uniform3f(programTextureOnCube_u_Color, colorR, colorG, colorB);

    gl.uniformMatrix4fv(programTextureOnCube_u_MvpMatrix, false, mvpMatrix.elements);
    gl.uniformMatrix4fv(programTextureOnCube_u_modelMatrix, false, modelMatrix.elements);
    gl.uniformMatrix4fv(programTextureOnCube_u_normalMatrix, false, normalMatrix.elements);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_CUBE_MAP, fbo.texture);
    gl.uniform1i(programTextureOnCube_u_envCubeMap, 0);

    for (let i = 0; i < obj.length; i++)
    {
        initAttributeVariable(gl, programTextureOnCube_a_Position, obj[i].vertexBuffer);
        initAttributeVariable(gl, programTextureOnCube_a_Normal, obj[i].normalBuffer);
        gl.drawArrays(gl.TRIANGLES, 0, obj[i].numVertices);
    }
}

async function loadOBJtoCreateVBO(objFile: string)
{
    const objComponents: any[] = [];

    let response = await fetch(objFile);
    let text = await response.text();
    let obj = parseOBJ(text);
    for( let i = 0; i < obj.geometries.length; i++)
    {
        if (gl == null) throw new Error("gl is null");
        
        let o = initVertexBufferForLaterUse3D(
            gl, 
            obj.geometries[i].data.position,
            obj.geometries[i].data.normal, 
            obj.geometries[i].data.texcoord
        );
        objComponents.push(o);
    }
    return objComponents;
}

function mouseDown(ev: MouseEvent)
{
    const x = ev.clientX;
    const y = ev.clientY;

    if(!(ev.target instanceof HTMLCanvasElement)) 
    {
        throw new Error("ev.target is null");
    }

    const rect = ev.target.getBoundingClientRect();

    if( rect.left <= x && x < rect.right && rect.top <= y && y < rect.bottom)
    {
        mouseLastX = x;
        mouseLastY = y;
        mouseDragging = true;
    }
}

function mouseUp()
{
    mouseDragging = false;
}

function mouseMove(ev: MouseEvent)
{
    if (canvas == null)
    {
        throw new Error("canvas is null");
    }
    const x = ev.clientX;
    const y = ev.clientY;

    if( mouseDragging )
    {
        const factor = 100 / canvas.height; // 100 determine the spped you rotate the object
        const dx = factor * (x - mouseLastX);
        const dy = factor * (y - mouseLastY);

        angleX += dx; // yes, x for y, y for x, this is right
        angleY += dy;
    }
    mouseLastX = x;
    mouseLastY = y;

    draw();
}

function keydown(ev: KeyboardEvent)
{
    // implment keydown event here
    const rotateMatrix = new Matrix4();
    rotateMatrix.setRotate(angleY, 1, 0, 0); // for mouse rotation
    rotateMatrix.rotate(angleX, 0, 1, 0); // for mouse rotation
    const viewDir = new Vector3([cameraDirX, cameraDirY, cameraDirZ]);
    const newViewDir = rotateMatrix.multiplyVector3(viewDir);

    if (ev.key == "w")
    {
        cameraX += newViewDir.elements[0] * 0.1;
        cameraY += newViewDir.elements[1] * 0.1;
        cameraZ += newViewDir.elements[2] * 0.1;
    } else if (ev.key == "s")
    {
        cameraX -= newViewDir.elements[0] * 0.1;
        cameraY -= newViewDir.elements[1] * 0.1;
        cameraZ -= newViewDir.elements[2] * 0.1;
    }

    draw();
}


function renderCubeMap(camX:number, camY:number, camZ:number)
{
    if (gl == null)
    {
        throw new Error("gl is null");
    }

    // camera 6 direction to render 6 cubemap faces
    const ENV_CUBE_LOOK_DIR = [
        [1.0, 0.0, 0.0],
        [-1.0, 0.0, 0.0],
        [0.0, 1.0, 0.0],
        [0.0, -1.0, 0.0],
        [0.0, 0.0, 1.0],
        [0.0, 0.0, -1.0]
    ];

    // camera 6 look up vector to render 6 cubemap faces
    const ENV_CUBE_LOOK_UP = [
        [0.0, -1.0, 0.0],
        [0.0, -1.0, 0.0],
        [0.0, 0.0, 1.0],
        [0.0, 0.0, -1.0],
        [0.0, -1.0, 0.0],
        [0.0, -1.0, 0.0]
    ];

    gl.useProgram(program);
    gl.bindFramebuffer(gl.FRAMEBUFFER, fbo);
    gl.viewport(0, 0, offScreenWidth, offScreenHeight);
    gl.clearColor(0.4, 0.4, 0.4, 1);
    
    for (var side = 0; side < 6;side++)
    {
        gl.framebufferTexture2D(
            gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, 
            gl.TEXTURE_CUBE_MAP_POSITIVE_X + side, fbo.texture, 0
        );
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

        let vpMatrix = new Matrix4();
        vpMatrix.setPerspective(90, 1, 1, 100);
        vpMatrix.lookAt(
            camX, camY, camZ,   
            camX + ENV_CUBE_LOOK_DIR[side][0], 
            camY + ENV_CUBE_LOOK_DIR[side][1],
            camZ + ENV_CUBE_LOOK_DIR[side][2], 
            ENV_CUBE_LOOK_UP[side][0],
            ENV_CUBE_LOOK_UP[side][1],
            ENV_CUBE_LOOK_UP[side][2]
        );
        
        drawEnvMap(vpMatrix);
        drawRegularObjects(vpMatrix);
    }
    gl.bindFramebuffer(gl.FRAMEBUFFER, null);
}

function drawEnvMap(viewMatrix: Matrix4)
{
    if (gl == null)
    {
        throw new Error("gl is null");
    }

    const vpFromCamera = new Matrix4();
    vpFromCamera.multiply(viewMatrix);
    const vpFromCameraInverse = vpFromCamera.invert();

    // quad
    gl.useProgram(quadProgram);
    gl.depthFunc(gl.LEQUAL);
    gl.uniformMatrix4fv(
        quad_u_viewDirectionProjectionInverse,
        false,
        vpFromCameraInverse.elements
    );
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_CUBE_MAP, cubeMapTex);
    gl.uniform1i(quad_u_envCubeMap, 0);
    initAttributeVariable(gl, quad_a_Position, quadObj.vertexBuffer);
    gl.drawArrays(gl.TRIANGLES, 0, quadObj.numVertices);
}