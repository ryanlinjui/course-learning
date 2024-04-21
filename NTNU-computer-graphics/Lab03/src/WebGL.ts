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
        varying vec4 v_Color;
        uniform mat4 u_modelMatrix;
        void main(){
            gl_Position = u_modelMatrix * a_Position;
            gl_PointSize = 10.0;
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

const transformMat = new Matrix4(null); //cuon 4x4 matrix

//NOTE: You are NOT allowed to change the vertex information here
const triangleVerticesA = [0.0, 0.2, 0.0, -0.1, -0.3, 0.0, 0.1, -0.3, 0.0]; //green rotating triangle vertices
const triangleColorA = [0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0 ]; //green trotating riangle color

//NOTE: You are NOT allowed to change the vertex information here
const triangleVerticesB = [0.0, 0.0, 0.0, -0.1, -0.5, 0.0, 0.1, -0.5, 0.0]; //green rotating triangle vertices
const triangleColorB = [0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0 ]; //green trotating riangle color
   
let triangle1XMove = 0;
let triangle2Angle = 125;
let triangle2HeightScale = 1;
let triangle3Angle = 0;

let renderProgram:WebGLProgram;
let a_Position:number;
let a_Color:number;
let u_modelMatrix:number | null;

let triangleModelA: Interface;
let triangleModelB: Interface;

main();

function main()
{
    //////Get the canvas context
    const canvas = document.getElementById("webgl") as HTMLCanvasElement | null;
    if(canvas == null) throw new Error("Canvas is null");
    
    const gl = canvas.getContext("webgl2");
    if(!gl)
    {
        console.log("Failed to get the rendering context for WebGL");
        return ;
    }

    /////compile shader and use it
    renderProgram = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);
    gl.useProgram(renderProgram);

    /////prepare attribute reference of the shader
    a_Position = gl.getAttribLocation(renderProgram, "a_Position");
    a_Color = gl.getAttribLocation(renderProgram, "a_Color");
    u_modelMatrix = gl.getUniformLocation(renderProgram, "u_modelMatrix") as number | null;
    if(u_modelMatrix == null) throw new Error("u_modelMatrix is null");

    if(a_Position < 0 || a_Color < 0 || u_modelMatrix < 0) 
    {
        console.log("Error: f(program.a_Position<0 || program.a_Color<0 || .....");
    }
        

    /////create vertex buffer of rotating point, center points, rotating triangle for later use
    triangleModelA = initVertexBufferForLaterUse(gl, triangleVerticesA, triangleColorA);
    triangleModelB = initVertexBufferForLaterUse(gl, triangleVerticesB, triangleColorB);
    
    document.addEventListener("keydown", (event)=> {    
        if( event.key == 'a' || event.key == 'A'){ //move triangle1 to the left
            console.log('A')
            triangle1XMove -= 0.05;
            draw(gl);
        }else if ( event.key == 'd' || event.key == 'D'){  //move triangle1 to the right
            console.log('D')
            triangle1XMove += 0.05;
            draw(gl);
        }else if ( event.key == 'r' || event.key == 'R'){  //rotate the second triangle
            console.log('R')
            triangle2Angle += 10;
            draw(gl);
        }else if ( triangle2HeightScale < 1.5 && (event.key == 'l' || event.key == 'L')){ //elongate the second triangle
            console.log('L')
            triangle2HeightScale += 0.1;
            draw(gl);
        }else if ( triangle2HeightScale >0.2 && (event.key == 's' || event.key == 'S')){ //shorten the second triangle
            console.log('S')
            triangle2HeightScale -= 0.1;
            draw(gl);
        }else if ( (event.key == 'o' || event.key == 'O')){ //rotate the third triangle
            console.log('O')
            triangle3Angle += 10;
            draw(gl);
        }
    });
    draw(gl);
}

function draw(gl:WebGL2RenderingContext)
{
    ////clear background color by black
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    transformMat.setIdentity(); //set identity matrix to transformMat
    
    //Note: You are NOT Allowed to change the following code
    transformMat.translate(triangle1XMove, 0, 0);
    initAttributeVariable(gl, a_Position, triangleModelA.vertexBuffer);//set triangle  vertex to shader varibale
    initAttributeVariable(gl, a_Color, triangleModelA.colorBuffer); //set triangle  color to shader varibale
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);//pass current transformMat to shader
    gl.drawArrays(gl.TRIANGLES, 0, triangleModelA.numVertices);//draw a triangle using triangleModelA
    ////////////// END: draw the first triangle

    //////////TODO: draw the other 2 triangles////////////////
    transformMat.translate(0, 0.18, triangle1XMove);
    transformMat.rotate(triangle2Angle, 0, 0, 1);
    transformMat.scale(triangle2HeightScale, triangle2HeightScale, 0);
    initAttributeVariable(gl, a_Position, triangleModelB.vertexBuffer);
    initAttributeVariable(gl, a_Color, triangleModelB.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLES, 0, triangleModelB.numVertices);

    
    transformMat.translate(0.1, -0.49, triangle1XMove);
    transformMat.rotate(triangle3Angle, 0, 0, 1);
    transformMat.scale(1/triangle2HeightScale, 1/triangle2HeightScale, 0);
    initAttributeVariable(gl, a_Position, triangleModelB.vertexBuffer);
    initAttributeVariable(gl, a_Color, triangleModelB.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLES, 0, triangleModelB.numVertices);

   
    
    /////////The code segment from here to the end of draw() function 
    /////////   is the only code segment you are allowed to change in this practice

}
