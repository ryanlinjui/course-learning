import {
    compileShader
} from "../../lib/utils";

import {
    initAttributeVariable,
    initVertexBufferForLaterUse3D,
    initFrameBuffer
} from "../../lib/init";

import {
    parseOBJ
} from "../../lib/cube";

import {
    Matrix4
} from "../../lib/cuon-matrix";

const VSHADER_SOURCE = `
    attribute vec4 a_Position;
    attribute vec4 a_Normal;
    uniform mat4 u_MvpMatrix;
    uniform mat4 u_modelMatrix;
    uniform mat4 u_normalMatrix;
    uniform mat4 u_ProjMatrixFromLight;
    uniform mat4 u_MvpMatrixOfLight;
    varying vec4 v_PositionFromLight;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    void main()
    {
        gl_Position = u_MvpMatrix * a_Position;
        v_PositionInWorld = (u_modelMatrix * a_Position).xyz; 
        v_Normal = normalize(vec3(u_normalMatrix * a_Normal));
        v_PositionFromLight = u_MvpMatrixOfLight * a_Position; // for shadow
    }
`;

const FSHADER_SOURCE = `
    precision mediump float;
    uniform vec3 u_LightPosition;
    uniform vec3 u_ViewPosition;
    uniform float u_Ka;
    uniform float u_Kd;
    uniform float u_Ks;
    uniform float u_shininess;
    uniform vec3 u_Color;
    uniform sampler2D u_ShadowMap;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    varying vec2 v_TexCoord;
    varying vec4 v_PositionFromLight;
    const float deMachThreshold = 0.005; // 0.001 if having high precision depth
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
            // V: the vector, point to viewer       
            vec3 V = normalize(u_ViewPosition - v_PositionInWorld); 
            float specAngle = clamp(dot(R, V), 0.0, 1.0);
            specular = u_Ks * pow(specAngle, u_shininess) * specularLightColor; 
        }

        //***** shadow
        vec3 shadowCoord = (v_PositionFromLight.xyz/v_PositionFromLight.w)/2.0 + 0.5;
        vec4 rgbaDepth = texture2D(u_ShadowMap, shadowCoord.xy);
        /////////******** LOW precision depth implementation ********///////////
        float depth = rgbaDepth.r;
        float visibility = (shadowCoord.z > depth + deMachThreshold) ? 0.3 : 1.0;

        gl_FragColor = vec4( (ambient + diffuse + specular)*visibility, 1.0);
    }
`;

const VSHADER_QUAD_SOURCE = `
    attribute vec4 a_Position;
    void main()
    {
        gl_Position = a_Position;
    }    
`;

const FSHADER_QUAD_SOURCE = `
    precision mediump float;
    uniform sampler2D u_ShadowMap;
    void main()
    {
        // TODO-2: look up the depth from u_ShaodowMap and draw on quad (just one line)
        float depth = texture2D(u_ShadowMap, gl_FragCoord.xy / 800.0).r;
        gl_FragColor = vec4(depth, depth, depth, 1.0);
    }
`;

const VSHADER_SHADOW_SOURCE = `
    attribute vec4 a_Position;
    uniform mat4 u_MvpMatrix;
    void main()
    {
        gl_Position = u_MvpMatrix * a_Position;
    }
`;

const FSHADER_SHADOW_SOURCE = `
    precision mediump float;
    void main()
    {
        /////////** LOW precision depth implementation **/////
        gl_FragColor = vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, 1.0);
    }
`;

let mouseLastX:number, mouseLastY:number;
let mouseDragging = false;
let angleX = 0, angleY = 0;

let gl: WebGL2RenderingContext | null;
let canvas: HTMLCanvasElement | null;

let cameraX = 3, cameraY = 3, cameraZ = 7;
let lightX = 0.01, lightY = 4, lightZ = 5.1;

let mario: any[] = [];
let cube: any[] = [];

const offScreenWidth = 2048, offScreenHeight = 2048;
const rotateAngle = 0;

let normalMode = true;

let fbo: any;
let quad: any;

let shadowProgram: WebGLProgram;
let shadow_a_Position: number;
let shadow_u_MvpMatrix: WebGLUniformLocation | null;

let program: WebGLProgram;
let a_Position: number;
let a_Normal: number;
let u_MvpMatrix: WebGLUniformLocation | null;
let u_modelMatrix: WebGLUniformLocation | null;
let u_normalMatrix: WebGLUniformLocation | null;
let u_LightPosition: WebGLUniformLocation | null;
let u_ViewPosition: WebGLUniformLocation | null;
let u_MvpMatrixOfLight: WebGLUniformLocation | null;
let u_Ka: WebGLUniformLocation | null;
let u_Kd: WebGLUniformLocation | null;
let u_Ks: WebGLUniformLocation | null;
let u_shininess: WebGLUniformLocation | null;
let u_ShadowMap: WebGLUniformLocation | null;
let u_Color: WebGLUniformLocation | null;

let quadProgram: WebGLProgram;
let quad_a_Position: number;
let quad_u_ShadowMap: WebGLUniformLocation | null;

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

    // setup shaders and prepare shader variables
    shadowProgram = compileShader(gl, VSHADER_SHADOW_SOURCE, FSHADER_SHADOW_SOURCE);
    shadow_a_Position = gl.getAttribLocation(shadowProgram, "a_Position");
    shadow_u_MvpMatrix = gl.getUniformLocation(shadowProgram, "u_MvpMatrix");

    program = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);
    a_Position = gl.getAttribLocation(program, "a_Position");
    a_Normal = gl.getAttribLocation(program, "a_Normal");
    u_MvpMatrix = gl.getUniformLocation(program, "u_MvpMatrix");
    u_modelMatrix = gl.getUniformLocation(program, "u_modelMatrix");
    u_normalMatrix = gl.getUniformLocation(program, "u_normalMatrix");
    u_LightPosition = gl.getUniformLocation(program, "u_LightPosition");
    u_ViewPosition = gl.getUniformLocation(program, "u_ViewPosition");
    u_MvpMatrixOfLight = gl.getUniformLocation(program, "u_MvpMatrixOfLight");
    u_Ka = gl.getUniformLocation(program, "u_Ka");
    u_Kd = gl.getUniformLocation(program, "u_Kd");
    u_Ks = gl.getUniformLocation(program, "u_Ks");
    u_shininess = gl.getUniformLocation(program, "u_shininess");
    u_ShadowMap = gl.getUniformLocation(program, "u_ShadowMap");
    u_Color = gl.getUniformLocation(program, "u_Color");

    quadProgram = compileShader(gl, VSHADER_QUAD_SOURCE, FSHADER_QUAD_SOURCE);
    quad_a_Position = gl.getAttribLocation(quadProgram, "a_Position");
    quad_u_ShadowMap = gl.getUniformLocation(quadProgram, "u_ShadowMap");

    gl.useProgram(program);

    // 3D model mario
    let response = await fetch("./mario.obj");
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
        mario.push(o);
    }

    // 3D model cube
    response = await fetch("./cube.obj");
    text = await response.text();
    obj = parseOBJ(text);
    for( let i = 0; i < obj.geometries.length; i++)
    {
        let o = initVertexBufferForLaterUse3D(
            gl, 
            obj.geometries[i].data.position,
            obj.geometries[i].data.normal, 
            obj.geometries[i].data.texcoord
        );
        cube.push(o);
    }

    // 3D model quad
    const quad_vertices = [
        -1, -1, 0,
        1, -1, 0,
        -1, 1, 0,
        -1, 1, 0,
        1, -1, 0,
        1, 1, 0
    ]; // just a quad
    quad = initVertexBufferForLaterUse3D(gl, quad_vertices, null, null);
    
    fbo = initFrameBuffer(gl, offScreenWidth, offScreenHeight);
    draw();

    canvas.onmousedown = function (ev) { mouseDown(ev) };
    canvas.onmousemove = function (ev) { mouseMove(ev) };
    canvas.onmouseup = function () { mouseUp() };
    
    const menu = document.getElementById("menu") as HTMLSelectElement | null;
    if(menu == null)
    {
        throw new Error("menu is null");
    }
    menu.onchange = function () 
    {
        if (menu.value == "normal")
        {
            normalMode = true;
        }
        else
        {
            normalMode = false;
        }

        draw();
    }
}

function draw() 
{
    ///// off scree shadow
    if (!gl)
    {
        throw new Error("Failed to get the rendering context for WebGL");
    }
    if (!canvas)
    {
        throw new Error("Canvas is null");
    }

    gl.useProgram(shadowProgram);
    gl.bindFramebuffer(gl.FRAMEBUFFER, fbo);
    gl.viewport(0, 0, offScreenWidth, offScreenHeight);
    gl.clearColor(0.0, 0.0, 0.0, 1);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.enable(gl.DEPTH_TEST);
    
    // cube
    let cubeMdlMatrix = new Matrix4();
    cubeMdlMatrix.setScale(2.0, 0.1, 2.0);
    let cubeMvpFromLight = drawOffScreen(cube, cubeMdlMatrix);
    
    // mario
    let marioMdlMatrix = new Matrix4();
    marioMdlMatrix.setTranslate(0.0, 1.4, 0.0);
    marioMdlMatrix.scale(0.02, 0.02, 0.02);
    let marioMvpFromLight = drawOffScreen(mario, marioMdlMatrix);

    ///// on scree rendering
    if (normalMode)
    {
        gl.useProgram(program);
        gl.bindFramebuffer(gl.FRAMEBUFFER, null);
        gl.viewport(0, 0, canvas.width, canvas.height);
        gl.clearColor(0.4, 0.4, 0.4, 1);
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        gl.enable(gl.DEPTH_TEST);
        
        // cube
        drawOneObjectOnScreen(cube, cubeMdlMatrix, cubeMvpFromLight, 1.0, 0.4, 0.4);
        
        // mario
        drawOneObjectOnScreen(mario, marioMdlMatrix, marioMvpFromLight, 0.4, 1.0, 0.4);
    } 
    else 
    {
        // TODO-1:
        // draw the shadow map (the quad)
        // active the quadProgram
        // switch the destination back to normal canvas color buffer
        // pass fbo.texture into the quadProgram
        // draw the quad ()

        gl.useProgram(quadProgram);
        gl.bindFramebuffer(gl.FRAMEBUFFER, null);
        gl.viewport(0, 0, canvas.width, canvas.height);
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, fbo.texture);
        gl.uniform1i(quad_u_ShadowMap, 0);
        initAttributeVariable(gl, quad_a_Position, quad.vertexBuffer);
        gl.drawArrays(gl.TRIANGLES, 0, 6);
    }
}

function drawOffScreen(obj: any[], mdlMatrix: Matrix4)
{
    if (!gl)
    {
        throw new Error("Failed to get the rendering context for WebGL");
    }
    const mvpFromLight = new Matrix4();
    
    // model Matrix (part of the mvp matrix)
    const modelMatrix = new Matrix4();
    
    modelMatrix.setRotate(angleY, 1, 0, 0);
    modelMatrix.rotate(angleX, 0, 1, 0);
    modelMatrix.multiply(mdlMatrix);

    // mvp: projection * view * model matrix  
    mvpFromLight.setPerspective(70, offScreenWidth / offScreenHeight, 1, 15);
    mvpFromLight.lookAt(lightX, lightY, lightZ, 0, 0, 0, 0, 1, 0);
    mvpFromLight.multiply(modelMatrix);

    gl.uniformMatrix4fv(shadow_u_MvpMatrix, false, mvpFromLight.elements);

    for (let i = 0; i < obj.length; i++) 
    {
        initAttributeVariable(gl, shadow_a_Position, obj[i].vertexBuffer);
        gl.drawArrays(gl.TRIANGLES, 0, obj[i].numVertices);
    }

    return mvpFromLight;
}

// obj: the object components
// mdlMatrix: the model matrix without mouse rotation
// colorR, G, B: object color
function drawOneObjectOnScreen(
    obj: any[], mdlMatrix: Matrix4, mvpFromLight: Matrix4,
    colorR: number, colorG: number, colorB: number
)
{
    if (!gl)
    {
        throw new Error("Failed to get the rendering context for WebGL");
    }

    const mvpFromCamera = new Matrix4();
    
    // model Matrix (part of the mvp matrix)
    const modelMatrix = new Matrix4();
    
    modelMatrix.setRotate(angleY, 1, 0, 0);
    modelMatrix.rotate(angleX, 0, 1, 0);
    modelMatrix.multiply(mdlMatrix);
    
    // mvp: projection * view * model matrix  
    mvpFromCamera.setPerspective(60, 1, 1, 15);
    mvpFromCamera.lookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
    mvpFromCamera.multiply(modelMatrix);

    // normal matrix
    let normalMatrix = new Matrix4();
    normalMatrix.setInverseOf(modelMatrix);
    normalMatrix.transpose();

    gl.uniform3f(u_LightPosition, lightX, lightY, lightZ);
    gl.uniform3f(u_ViewPosition, cameraX, cameraY, cameraZ);
    gl.uniform1f(u_Ka, 0.2);
    gl.uniform1f(u_Kd, 0.7);
    gl.uniform1f(u_Ks, 1.0);
    gl.uniform1f(u_shininess, 10.0);
    gl.uniform1i(u_ShadowMap, 0);
    // gl.uniform1i(u_normalMode, normalMode);
    gl.uniform3f(u_Color, colorR, colorG, colorB);

    gl.uniformMatrix4fv(u_MvpMatrix, false, mvpFromCamera.elements);
    gl.uniformMatrix4fv(u_modelMatrix, false, modelMatrix.elements);
    gl.uniformMatrix4fv(u_normalMatrix, false, normalMatrix.elements);
    gl.uniformMatrix4fv(u_MvpMatrixOfLight, false, mvpFromLight.elements);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, fbo.texture);

    for (let i = 0; i < obj.length; i++) 
    {
        initAttributeVariable(gl, a_Position, obj[i].vertexBuffer);
        initAttributeVariable(gl, a_Normal, obj[i].normalBuffer);
        gl.drawArrays(gl.TRIANGLES, 0, obj[i].numVertices);
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
