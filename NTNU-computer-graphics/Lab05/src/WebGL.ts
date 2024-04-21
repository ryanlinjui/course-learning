import {
    compileShader
} from "../../utils"

import {
    Interface,
    initAttributeVariable,
    initVertexBufferForLaterUse
} from "./init"

import {
    Matrix4
} from "./cuon-matrix"

const VSHADER_SOURCE = `
        attribute vec4 a_Position;
        attribute vec4 a_Color;
        uniform mat4 u_mvpMatrix;
        varying vec4 v_Color;
        void main(){
            gl_Position = u_mvpMatrix * a_Position;
            v_Color = a_Color;
        }    
    `;

const FSHADER_SOURCE = `
    precision mediump float;
    varying vec4 v_Color;
    void main(){
        gl_FragColor = v_Color;
    }
`;

// 9 vertices (three triangles)
// x, y, z of the 1st vertex of the 1st triangle
const vertices = new Float32Array([
    0.0, 1.0, -2.0,
    -0.5, -1.0, -2.0,
    0.5, -1.0, -2.0,

    0.0, 1.0, -0.0,
    -0.5, -1.0, -0.0,
    0.5, -1.0, -0.0,

    0.0, 1.0, 2.0,
    -0.5, -1.0, 2.0,
    0.5, -1.0, 2.0,
]);

// 9 vertices (three triangles)"s color
// r, g, b of the 1st vertex of the 1st triangle
const colors = new Float32Array([
    0.7, 0.0, 0.0, 
    0.7, 0.0, 0.0,
    0.7, 0.0, 0.0, 

    0.0, 0.7, 0.0, 
    0.0, 0.7, 0.0, 
    0.0, 0.7, 0.0, 

    0.0, 0.0, 0.7, 
    0.0, 0.0, 0.7, 
    0.0, 0.0, 0.7, 
]);

const modelMatrix1 = new Matrix4(null);
const frontViewMatrix1 = new Matrix4(null);
const pespProjMatrix1 = new Matrix4(null);

const modelMatrix2 = new Matrix4(null);
const frontViewMatrix2 = new Matrix4(null);
const pespProjMatrix2 = new Matrix4(null);

const transformMat = new Matrix4(null);

let mouseLastX:number, mouseLastY:number;
let mouseDragging = false;
let angleX = 0, angleY = 0;

let canvas:HTMLCanvasElement | null;
let gl:WebGL2RenderingContext | null;
let program:WebGLProgram;

let a_Position:number;
let a_Color:number;
let u_mvpMatrix:number | null;

let triangles:Interface;

main();
function main()
{
    //////Get the canvas context
    canvas = document.getElementById("webgl") as HTMLCanvasElement | null;
    if(canvas == null) throw new Error("Canvas is null");

    gl = canvas.getContext("webgl2");
    if(!gl)
    {
        console.log("Failed to get the rendering context for WebGL");
        return;
    }

    program = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);
    gl.useProgram(program);

    /////prepare attribute reference of the shader
    a_Position = gl.getAttribLocation(program, "a_Position");
    a_Color = gl.getAttribLocation(program, "a_Color");
    u_mvpMatrix = gl.getUniformLocation(program, "u_mvpMatrix") as number | null;

    if(!u_mvpMatrix)
    {
        console.log("Failed to get the storage location of u_mvpMatrix");
        return;
    }

    if(a_Position < 0 || a_Color < 0 || u_mvpMatrix < 0)
    {
        console.log("Error: f(program.a_Position<0 || program.a_Color<0 || .....");
    }
        
    /////create vertex buffer of rotating point, center points, rotating triangle for later use
    triangles = initVertexBufferForLaterUse(gl, vertices, colors);

    gl.enable(gl.DEPTH_TEST);
    gl.enable(gl.SCISSOR_TEST); //enable scissor test to only apply background clear on one viewport

    frontViewMatrix1.setLookAt(0, 0, -10, 0, 0, 100, 0, 1, 0);
    pespProjMatrix1.setPerspective(30, canvas.width/canvas.height, 1, 100);
    
    frontViewMatrix2.setLookAt(0, 1.5, 15, 0, 1.5, -100, 0, 1, 0);
    pespProjMatrix2.setOrtho(-2, 2, -2, 2, 1, 100);

    canvas.onmousedown = function(ev){mouseDown(ev)};
    canvas.onmousemove = function(ev){mouseMove(ev)};
    canvas.onmouseup = function(){mouseUp()};

    draw(mouseLastX, mouseLastY);
}

function drawOneViewport(
    gl:WebGL2RenderingContext, viewportX:number, viewportY:number, viewportWidth:number, viewportHeight:number,
    bgColorR:number, bgColorG:number, bgColorB:number,
    projMatrix:Matrix4, viewMatrix:Matrix4, modelMatrixTriangleSet1:Matrix4, modelMatrixTriangleSet2:Matrix4 | null
)
{
    gl.viewport(viewportX, viewportY, viewportWidth, viewportHeight);

    //scissor: make the background clear only apply to this region
    gl.scissor(viewportX, viewportY, viewportWidth, viewportHeight);

    ////clear background color and depth buffer
    gl.clearColor(bgColorR, bgColorG, bgColorB, 1.0);
    gl.clear(gl.DEPTH_BUFFER_BIT | gl.COLOR_BUFFER_BIT) 
    
    //draw a set of triangles
    transformMat.set(projMatrix);
    transformMat.multiply(viewMatrix);
    transformMat.multiply(modelMatrixTriangleSet1);
    initAttributeVariable(gl, a_Position, triangles.vertexBuffer);
    initAttributeVariable(gl, a_Color, triangles.colorBuffer); 
    gl.uniformMatrix4fv(u_mvpMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLES, 0, triangles.numVertices);

    if( modelMatrixTriangleSet2 != null) //if we have the second modelMatrix
    {
        //draw the second set of triangles
        transformMat.set(projMatrix);
        transformMat.multiply(viewMatrix);
        transformMat.multiply(modelMatrixTriangleSet2);
        initAttributeVariable(gl, a_Position, triangles.vertexBuffer);
        initAttributeVariable(gl, a_Color, triangles.colorBuffer); 
        gl.uniformMatrix4fv(u_mvpMatrix, false, transformMat.elements);
        gl.drawArrays(gl.TRIANGLES, 0, triangles.numVertices);
    }
}

function mouseDown(ev:MouseEvent)
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

function mouseMove(ev:MouseEvent)
{
    const x = ev.clientX;
    const y = ev.clientY;

    draw(x, y);
}

function draw(x:number, y:number)
{
    if(canvas == null) throw new Error("Canvas is null");
    if(gl == null) throw new Error("gl is null");
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

    //call drawOneViewPort three times to draw the three views
    modelMatrix1.setRotate(-angleY, 1, 0, 0);
    modelMatrix1.rotate(angleX, 0, 1, 0);
    modelMatrix1.translate(0.7, 0, 0);

    modelMatrix2.setRotate(-angleY, 1, 0, 0);
    modelMatrix2.rotate(angleX, 0, 1, 0);
    modelMatrix2.translate(-0.7, 0, 0);

    //this only draw one set of triangles because we pass "null" for the last argument
    drawOneViewport(
        gl, 0, canvas.height / 2, canvas.width, canvas.height,
        0.77, 0.77, 0.77,
        pespProjMatrix1, frontViewMatrix2, modelMatrix1, modelMatrix2
    );

    drawOneViewport(
        gl, 0, 0, canvas.width / 2, canvas.height / 2,
        0, 0, 0,
        pespProjMatrix1, frontViewMatrix1, modelMatrix1, modelMatrix2
    );

    drawOneViewport(
        gl, canvas.width / 2, 0, canvas.width / 2, canvas.height / 2,
        0.35, 0.35, 0.35,
        pespProjMatrix2, frontViewMatrix1, modelMatrix1, modelMatrix2
    );
}