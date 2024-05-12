import {
    compileShader
} from "../../lib/utils";

import {
    initAttributeVariable,
    initVertexBufferForLaterUse3D,
    initCubeTexture
} from "../../lib/init";

import {
    parseOBJ
} from "../../lib/cube";

import {
    Matrix4,
    Vector3
} from "../../lib/cuon-matrix";

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
    uniform samplerCube u_envCubeMap;
    uniform vec3 u_LightPosition;
    uniform vec3 u_ViewPosition;
    uniform float u_Ka;
    uniform float u_Kd;
    uniform float u_Ks;
    uniform float u_shininess;
    uniform vec3 u_Color;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    void main()
    {
        vec3 ambientLightColor = u_Color;
        vec3 diffuseLightColor = u_Color;
        vec3 specularLightColor = vec3(1.0, 1.0, 1.0);        
        vec3 ambient = ambientLightColor * u_Ka;
        vec3 normal = normalize(v_Normal);
        vec3 lightDirection = normalize(u_LightPosition - v_PositionInWorld);
        float nDotL = max(dot(lightDirection, normal), 0.0);
        vec3 diffuse = diffuseLightColor * u_Kd * nDotL;
        vec3 specular = vec3(0.0, 0.0, 0.0);
        if(nDotL > 0.0) 
        {
            vec3 R = reflect(-lightDirection, normal);
            vec3 V = normalize(u_ViewPosition - v_PositionInWorld); 
            float specAngle = clamp(dot(R, V), 0.0, 1.0);
            specular = u_Ks * pow(specAngle, u_shininess) * specularLightColor; 
        }

        // Adding environment reflection using the cube map
        vec3 reflectedWorld = reflect(normalize(v_PositionInWorld - u_ViewPosition), normal);
        vec4 envColor = textureCube(u_envCubeMap, reflectedWorld);

        gl_FragColor = vec4(ambient + diffuse + specular, 1.0) * envColor;
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

let mvpMatrix: Matrix4;
let modelMatrix: Matrix4;
let normalMatrix: Matrix4;

let cameraX = 0, cameraY = 0, cameraZ = 5;
const objScale = 0.05;
const objComponents: any[] = [];

const cameraDirX = 0, cameraDirY = 0, cameraDirZ = -1;

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
let u_shininess: WebGLUniformLocation | null;
let u_Color: WebGLUniformLocation | null;

let quadObj: any;
let cubeMapTex: WebGLTexture | null;

let quadProgram: WebGLProgram;
let quad_a_Position: number;
let quad_u_envCubeMap: WebGLUniformLocation | null;
let quad_u_viewDirectionProjectionInverse: WebGLUniformLocation | null;

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
    u_shininess = gl.getUniformLocation(program, "u_shininess");
    u_Color = gl.getUniformLocation(program, "u_Color");

    // 3D model sonic
    let response = await fetch("./sonic.obj");
    let text = await response.text();
    let obj = parseOBJ(text);
    for( let i = 0; i < obj.geometries.length; i++)
    {
        let o = initVertexBufferForLaterUse3D(
            gl, 
            obj.geometries[i].data.position,
            obj.geometries[i].data.normal, 
            obj.geometries[i].data.texcoord
        );
        objComponents.push(o);
    }

    mvpMatrix = new Matrix4();
    modelMatrix = new Matrix4();
    normalMatrix = new Matrix4();

    draw(); //draw it once before mouse move

    canvas.onmousedown = function (ev) {
        mouseDown(ev);
    };
    canvas.onmousemove = function (ev) {
        mouseMove(ev);
    };
    canvas.onmouseup = function () {
        mouseUp();
    };
    document.onkeydown = function (ev) {
        keydown(ev);
    };
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

    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.clearColor(0, 0, 0, 1);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.enable(gl.DEPTH_TEST);

    let rotateMatrix = new Matrix4();
    rotateMatrix.setRotate(angleY, 1, 0, 0); // for mouse rotation
    rotateMatrix.rotate(angleX, 0, 1, 0); // for mouse rotation
    const viewDir = new Vector3([cameraDirX, cameraDirY, cameraDirZ]);
    const newViewDir = rotateMatrix.multiplyVector3(viewDir);

    const vpFromCamera = new Matrix4();
    vpFromCamera.setPerspective(60, 1, 1, 15);
    const viewMatrixRotationOnly = new Matrix4();
    
    viewMatrixRotationOnly.lookAt(
        cameraX,
        cameraY,
        cameraZ,
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

    gl.useProgram(program);
    
    modelMatrix.setScale(objScale, objScale, objScale);

    mvpMatrix.setPerspective(30, 1, 1, 100);
    mvpMatrix.lookAt(
        cameraX,
        cameraY,
        cameraZ,
        cameraX + newViewDir.elements[0],
        cameraY + newViewDir.elements[1],
        cameraZ + newViewDir.elements[2],
        0, 1, 0
    );
    mvpMatrix.multiply(modelMatrix);

    //normal matrix
    normalMatrix.setInverseOf(modelMatrix);
    normalMatrix.transpose();

    gl.uniform3f(u_LightPosition, 0, 0, 3);
    gl.uniform3f(u_ViewPosition, cameraX, cameraY, cameraZ);
    gl.uniform1f(u_Ka, 0.2);
    gl.uniform1f(u_Kd, 0.7);
    gl.uniform1f(u_Ks, 1.0);
    gl.uniform1f(u_shininess, 10.0);
    gl.uniform3f(u_Color, 1.0, 0.4, 0.4);

    gl.uniformMatrix4fv(u_MvpMatrix, false, mvpMatrix.elements);
    gl.uniformMatrix4fv(u_modelMatrix, false, modelMatrix.elements);
    gl.uniformMatrix4fv(u_normalMatrix, false, normalMatrix.elements);

    for (let i = 0; i < objComponents.length; i++)
    {
        initAttributeVariable(gl, a_Position, objComponents[i].vertexBuffer);
        initAttributeVariable(gl, a_Normal, objComponents[i].normalBuffer);
        gl.drawArrays(gl.TRIANGLES, 0, objComponents[i].numVertices);
    }
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