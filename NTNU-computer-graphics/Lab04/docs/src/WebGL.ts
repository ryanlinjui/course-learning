import {
    compileShader
} from "../../utils"

import {
    Interface,
    initAttributeVariable,
    initVertexBufferForLaterUse
} from "./init"

import {
    Matrix4,
    Vector4
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

const transformMat = new Matrix4(null);
const transformMatCircle1 = new Matrix4(null); //initial circle base transformation matrix
transformMatCircle1.setTranslate(0.5, 0, 0);

//NOTE: You are NOT allowed to change the vertex information here
const triangleVerticesA = [0.0, 0.2, 0.0, -0.1, -0.3, 0.0, 0.1, -0.3, 0.0]; //green rotating triangle vertices
const triangleColorA = [0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0 ]; //green trotating riangle color

//NOTE: You are NOT allowed to change the vertex information here
const triangleVerticesB = [0.0, 0.0, 0.0, -0.1, -0.5, 0.0, 0.1, -0.5, 0.0]; //green rotating triangle vertices
const triangleColorB = [0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0 ]; //green trotating riangle color

   
let triangle1XMove = 0;
let triangle1YMove = 0;
let triangle2Angle = 125;
let triangle2HeightScale = 1;
let triangle3Angle = 0;

let circle1Angle = 0; //the angle of the triangle on the circle


/////// create circle model
let circleVertices: number[] = []
let circleColors: number[] = []
let circleColorsTouch: number[] = []
let circleColorsGrab: number[] = []
let circleRadius = 0.1;
for (let i = 0; i <= 1000; i++)
{
    circleRadius = 0.1
    let x = circleRadius*Math.cos(i * 2 * Math.PI / 200)
    let y = circleRadius*Math.sin(i * 2 * Math.PI / 200) 
    circleVertices.push(x, y);
    circleColors.push(1, 0, 0); //circle normal color
    circleColorsTouch.push(0, 1, 0); //color when the circle connect with the triangle corner
    circleColorsGrab.push(0, 0.5, 0); //color when the circle is grabbed by the triangle corner
}

let renderProgram:WebGLProgram;
let a_Position:number;
let a_Color:number;
let u_modelMatrix:number | null;

let triangleModelA: Interface;
let triangleModelB: Interface;

let circleModel: Interface;
let circleModelTouch: Interface;
let circleModelGrab: Interface;

let grab_mode = false;
let touch_mode = false;

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
        console.log("Error: f(a_Position<0 || a_Color<0 || .....");
    }
        
    
    /////create vertex buffer of rotating point, center points, rotating triangle for later use
    triangleModelA = initVertexBufferForLaterUse(gl, triangleVerticesA, triangleColorA);
    triangleModelB = initVertexBufferForLaterUse(gl, triangleVerticesB, triangleColorB);

    ////create vertex buffer of the circle with red color, light green and dark green color
    circleModel = initVertexBufferForLaterUse(gl, circleVertices, circleColors);
    circleModelTouch = initVertexBufferForLaterUse(gl, circleVertices, circleColorsTouch);
    circleModelGrab = initVertexBufferForLaterUse(gl, circleVertices, circleColorsGrab);
    
    document.addEventListener("keydown", (event)=> {    
        if( event.key == 'a' || event.key == 'A') //move triangle1 to the left
        { 
            console.log('A');
            triangle1XMove -= 0.05;
            draw(gl);

        }
        else if ( event.key == 'd' || event.key == 'D') //move triangle1 to the right
        {
            console.log('D');
            triangle1XMove += 0.05;
            draw(gl);

        }
        else if ( event.key == 's' || event.key == 'S') //move triangle1 to the bottom
        { 
            console.log('S');
            triangle1YMove -= 0.1;
            draw(gl);

        }
        else if ( event.key == 'w' || event.key == 'W') //move triangle1 to the up
        { 
            console.log('W');
            triangle1YMove += 0.1;
            draw(gl);

        }
        else if ( event.key == 'r' || event.key == 'R') //rotate the second triangle
        { 
            console.log('R');
            triangle2Angle += 10;
            draw(gl);

        }
        else if ( event.key == 'g' || event.key == 'G') // hold the circle
        {
            console.log('G');
            ///// TODO: when the user press 'g' or 'G'
            if(grab_mode == true)
            {
                grab_mode = false;
            }
            else if(touch_mode)
            {
                grab_mode = true;
            }
            
            draw(gl);
        }
    });

    ////For creating animation, in short this code segment will keep calling "draw(gl)" 
    ////btw, this needs "webgl-util.js" in the folder (we include it in index.html)
    const tick = function() 
    {
        draw(gl);
        requestAnimationFrame(tick);
    }
    tick();
}

function draw(gl:WebGL2RenderingContext)
{
    ////clear background color by black
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    transformMat.setIdentity(); //set identity matrix to transformMat
    
    //Note: You are NOT Allowed to change the following code
    transformMat.translate(triangle1XMove, triangle1YMove, 0);
    initAttributeVariable(gl, a_Position, triangleModelA.vertexBuffer);//set triangle  vertex to shader varibale
    initAttributeVariable(gl, a_Color, triangleModelA.colorBuffer); //set triangle  color to shader varibale
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);//pass current transformMat to shader
    gl.drawArrays(gl.TRIANGLES, 0, triangleModelA.numVertices);//draw a triangle using triangleModelA
    ////////////// END: draw the first triangle

    /////////The code segment from here to the end of draw() function 
    /////////   is the only code segment you are allowed to change in this practice
    transformMat.translate(0.0, 0.2, 0);
    transformMat.rotate(triangle2Angle, 0, 0, 1);
    transformMat.scale(1, triangle2HeightScale, 1);
    initAttributeVariable(gl, a_Position, triangleModelB.vertexBuffer);//set triangle  vertex to shader varibale
    initAttributeVariable(gl, a_Color, triangleModelB.colorBuffer); //set triangle  color to shader varibale
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);//pass current transformMat to shader
    gl.drawArrays(gl.TRIANGLES, 0, triangleModelB.numVertices);//draw the triangle 

    ///////TODO: calculate whenther the triangle corner and the circle touch each other
    ///////      show the circle by different color according to the touch-grab conditions
    ///////      Draw the circle and its triangle and the proper locations
    const transformMat_cir = new Matrix4(transformMatCircle1);

    const triangle_point = [
        transformMat.multiplyVector4( new Vector4 ([...(triangleVerticesB.slice(0, 3)), 1])).elements,
        transformMat.multiplyVector4( new Vector4 ([...(triangleVerticesB.slice(3, 6)), 1])).elements,
        transformMat.multiplyVector4( new Vector4 ([...(triangleVerticesB.slice(6, 9)), 1])).elements
    ];

    const circle_point = transformMat_cir.multiplyVector4( new Vector4([0,0,0,1])).elements;
    touch_mode = false;

    if (
        Math.sqrt((triangle_point[0][0] - circle_point[0])**2 + (triangle_point[0][1] - circle_point[1])**2) <= circleRadius ||
        Math.sqrt((triangle_point[1][0] - circle_point[0])**2 + (triangle_point[1][1] - circle_point[1])**2) <= circleRadius ||
        Math.sqrt((triangle_point[2][0] - circle_point[0])**2 + (triangle_point[2][1] - circle_point[1])**2) <= circleRadius
    )
    {
        touch_mode = true;
    }
    
    if (grab_mode)
    {
        transformMat_cir.translate(triangle1XMove - 0.5, triangle1YMove + 0.2, 0);
        transformMat_cir.rotate(triangle2Angle, 0, 0, 1);
        transformMat_cir.translate(-0.1, -triangle2HeightScale * 0.5, 0);
        initAttributeVariable(gl, a_Color, circleModelGrab.colorBuffer);
    }
    else if(touch_mode)
    {
        initAttributeVariable(gl, a_Color, circleModelTouch.colorBuffer);
    } 
    else 
    {
        initAttributeVariable(gl, a_Color, circleModel.colorBuffer); //set circle normal color to shader varibale
    }


    initAttributeVariable(gl, a_Position, circleModel.vertexBuffer);//set circle  vertex to shader varibale
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat_cir.elements);//pass current transformMat_cir to shader
    gl.drawArrays(gl.TRIANGLES, 0, circleModel.numVertices);//draw the triangle 

    circle1Angle++; //keep changing the angle of the triangle
    transformMat_cir.rotate(circle1Angle, 0, 0, 1);
    initAttributeVariable(gl, a_Position, triangleModelB.vertexBuffer);//set triangle  vertex to shader varibale
    initAttributeVariable(gl, a_Color, triangleModelB.colorBuffer); //set triangle  color to shader varibale
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat_cir.elements);//pass current transformMat_cir to shader
    gl.drawArrays(gl.TRIANGLES, 0, triangleModelB.numVertices);//draw the triangle 
}
