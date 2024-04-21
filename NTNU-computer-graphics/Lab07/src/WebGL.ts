import {
  compileShader
} from "../../utils"

import {
    initAttributeVariable,
    initVertexBufferForLaterUse3D,
} from "./init"

import {
    getNormalOnVertices,
    parseOBJ
} from "./cube"

import {
    Matrix4
} from "./cuon-matrix"

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
    uniform float u_shininess;
    uniform vec3 u_Color;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    void main()
    {
        // let ambient and diffuse color are u_Color 
        // (you can also input them from ouside and make them different)
        vec3 ambientLightColor = u_Color;
        vec3 diffuseLightColor = u_Color;
        // assume white specular light (you can also input it from ouside)
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

        gl_FragColor = vec4( ambient + diffuse + specular, 1.0 );
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

let cameraX = 3, cameraY = 3, cameraZ = 7;
let mario: any[] = [];
let sonic: any[] = [];
let cube: any[] = [];
let moveDistance = 0;
let rotateAngle = 0;

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

    const program = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);

    gl.useProgram(program);

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

    // 3D model sonic
    response = await fetch("./sonic.obj");
    text = await response.text();
    obj = parseOBJ(text);
    for( let i = 0; i < obj.geometries.length; i++ )
    {
      let o = initVertexBufferForLaterUse3D(
            gl, 
            obj.geometries[i].data.position,
            obj.geometries[i].data.normal, 
            obj.geometries[i].data.texcoord
        );
        sonic.push(o);
    }

    // cube
    // TODO-1: create vertices for the cube whose edge length is 2.0 (or 1.0 is also fine)
    // F: Face, T: Triangle, V: vertex (XYZ)
    const cubeVertices: number[] = [
        //F1_T1_V1,  F1_T1_V2,  F1_T1_V3,  F1_T2_V4,  F1_T2_V5,  F1_T2_V6, // this row for the face z = 1.0
        1.0, 1.0, 1.0, -1.0, 1.0, 1.0,
        -1.0, -1.0, 1.0, -1.0, -1.0, 1.0,
        1.0, -1.0, 1.0, 1.0, 1.0, 1.0,

        //F2_T1_V1,  F2_T1_V2,  F2_T1_V3,  F2_T2_V4,  F2_T2_V5,  F2_T2_V6, // this row for the face x = 1.0
        1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0,
        -1.0, -1.0, 1.0, -1.0, -1.0, 1.0,
        1.0, -1.0, 1.0, 1.0, 1.0, 1.0,

        //F3_T1_V1,  F3_T1_V2,  F3_T1_V3,  F3_T2_V4,  F3_T2_V5,  F3_T2_V6, // this row for the face y = 1.0
        1.0, 1.0, 1.0, 1.0, -1.0, -1.0,
        1.0, -1.0, -1.0, 1.0, -1.0, -1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, -1.0,

        //F4_T1_V1,  F4_T1_V2,  F4_T1_V3,  F4_T2_V4,  F4_T2_V5,  F4_T2_V6, // this row for the face x = -1.0
        1.0, 1.0, -1.0, -1.0, 1.0, -1.0,
        -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0, 1.0, 1.0, 1.0,
        
        //F5_T1_V1,  F5_T1_V2,  F5_T1_V3,  F5_T2_V4,  F5_T2_V5,  F5_T2_V6,   //this row for the face y = -1.0
        -1.0, 1.0, 1.0, -1.0, -1.0, -1.0,
        -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
        -1.0, 1.0, 1.0, -1.0, 1.0, 1.0,

        //F6_T1_V1,  F6_T1_V2,  F6_T1_V3,  F6_T2_V4,  F6_T2_V5,  F6_T2_V6,   //this row for the face z = -1.0
        1.0, -1.0, -1.0, 1.0, -1.0, -1.0,
        -1.0, -1.0, -1.0, -1.0, -1.0, 1.0,
        -1.0, -1.0, 1.0, 1.0, -1.0, 1.0
    ];

    const cubeNormals = getNormalOnVertices(cubeVertices);
    let o = initVertexBufferForLaterUse3D(gl, cubeVertices, cubeNormals, null);
    cube.push(o);

    mvpMatrix = new Matrix4();
    modelMatrix = new Matrix4();
    normalMatrix = new Matrix4();

    gl.enable(gl.DEPTH_TEST);

    draw(); //draw it once before mouse move

    canvas.onmousedown = function(ev){mouseDown(ev)};
    canvas.onmousemove = function(ev){mouseMove(ev)};
    canvas.onmouseup = function(ev){mouseUp(ev)};

    const slider1 = document.getElementById("move") as HTMLInputElement;
    if (slider1 == null) throw new Error("slider1 is null");

    slider1.oninput = function() 
    {
        moveDistance = parseFloat(slider1.value) / 60.0;
        draw();
    }

    const slider2 = document.getElementById("rotate") as HTMLInputElement;
    if (slider2 == null) throw new Error("slider2 is null");

    slider2.oninput = function() 
    {
        rotateAngle = parseFloat(slider2.value);
        draw();
    }
}

// Call drawOneObject() here to draw all object one by one 
// (setup the model matrix and color to draw)
function draw()
{
    if (gl == null)
    {
        console.log("Failed to get the rendering context for WebGL");
        return;
    }

    gl.clearColor(0, 0, 0, 1);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // Cube (ground)
    // TODO-1: set mdlMatrix for the cube
    drawOneObject(cube, new Matrix4().scale(2, 0.1, 2), 1.0, 0.4, 0.4);

    // mario
    // TODO-2: set mdlMatrix for mario
    drawOneObject(mario, new Matrix4()
        .translate(-1.0, 0.8, -1.0)
        .scale(0.01, 0.01, 0.01),
        0.4, 1.0, 0.4
    );

    // sonic
    // TODO-3: set mdlMatrix for sonic (include rotation and movement)
    drawOneObject(sonic, new Matrix4()
        .translate(moveDistance, 0.2, 0.0)
        .rotate(rotateAngle, 0.0, 1.0, 0.0)
        .scale(0.05, 0.05, 0.05),
        0.4, 0.4, 1.0
    );
}

// obj: the object components
// mdlMatrix: the model matrix without mouse rotation
// colorR, G, B: object color
function drawOneObject(obj: any[], mdlMatrix: Matrix4, colorR: number, colorG: number, colorB: number)
{
    // model Matrix (part of the mvp matrix)
    modelMatrix.setRotate(angleY, 1, 0, 0);//for mouse rotation
    modelMatrix.rotate(angleX, 0, 1, 0);//for mouse rotation
    modelMatrix.multiply(mdlMatrix);

    // mvp: projection * view * model matrix  
    mvpMatrix.setPerspective(30, 1, 1, 100);
    mvpMatrix.lookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
    mvpMatrix.multiply(modelMatrix);

    // normal matrix
    normalMatrix.setInverseOf(modelMatrix);
    normalMatrix.transpose();

    if (gl == null)
    {
        console.log("Failed to get the rendering context for WebGL");
        return;
    }

    gl.uniform3f(u_LightPosition, 0, 5, 3);
    gl.uniform3f(u_ViewPosition, cameraX, cameraY, cameraZ);
    gl.uniform1f(u_Ka, 0.2);
    gl.uniform1f(u_Kd, 0.7);
    gl.uniform1f(u_Ks, 1.0);
    gl.uniform1f(u_shininess, 10.0);
    gl.uniform3f(u_Color, colorR, colorG, colorB);

    gl.uniformMatrix4fv(u_MvpMatrix, false, mvpMatrix.elements);
    gl.uniformMatrix4fv(u_modelMatrix, false, modelMatrix.elements);
    gl.uniformMatrix4fv(u_normalMatrix, false, normalMatrix.elements);

    for( let i = 0; i < obj.length; i++)
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

function mouseUp(ev: MouseEvent)
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
        var factor = 100 / canvas.height; // 100 determine the spped you rotate the object
        var dx = factor * (x - mouseLastX);
        var dy = factor * (y - mouseLastY);

        angleX += dx; // yes, x for y, y for x, this is right
        angleY += dy;
    }
    mouseLastX = x;
    mouseLastY = y;

    draw();
}