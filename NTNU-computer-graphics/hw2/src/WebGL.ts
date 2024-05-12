import {
    compileShader
} from "../../lib/utils";

import {
    Interface,
    initAttributeVariable,
    initVertexBufferForLaterUse
} from "../../lib/init";

import {
    Matrix4,
    Vector4
} from "../../lib/cuon-matrix";

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

// wheel model
const wheel1 : {
    vertices: number[],
    colors: number[],
    radius: number
} = {
    vertices: [],
    colors: [],
    radius: 0.05
}
for (let i = 0; i <= 1000; i++)
{
    const x = wheel1.radius * Math.cos(i * 2 * Math.PI / 200)
    const y = wheel1.radius * Math.sin(i * 2 * Math.PI / 200)
    wheel1.vertices.push(x, y);
    wheel1.colors.push(1, 0, 0); // red color
}
const wheel2 = {...wheel1};

// body model
const body : {
    vertices: number[],
    colors: number[],
} = {
    vertices: [ // coordinates for a horizontal rectangle
        0, 0, 0,
        0.4, 0, 0,
        0.4, -0.2, 0,
        0, -0.2, 0,
    ],
    colors: []
}
for (let i = 0; i < 4; i++) 
{
    body.colors.push(0, 1, 0); // green color
}

// head model
const head : {
    vertices: number[],
    colors: number[]
} = {
    vertices: [
        0.0, 0.0, 0.0,
        -0.1, -0.2, 0.0,
        0.1, -0.2, 0.0
    ],
    colors: []
}
for (let i = 0; i < 9; i++) 
{
    head.colors.push(0, 1, 0); // green color
}

// arm model
const arm1 : {
    vertices: number[],
    colors: number[]
} = {
    vertices: [ // coordinates for a vertical rectangle
        0, 0, 0, -0.04, -0.25, 0.0, 0.04, -0.25, 0.0,
        -0.04, -0.25, 0.0, -0.04, 0, 0, 0, 0, 0,
        0.04, -0.25, 0.0, 0.04, 0, 0, 0, 0, 0,
    ], 
    colors: []
}
for (let i = 0; i < 9; i++) 
{
    arm1.colors.push(1, 1, 1); // white color
}
const arm2 = {...arm1};
// joint model
const joint1 : {
    vertices: number[],
    colors: number[],
    radius: number,
    angle: number
} = {
    vertices: [],
    colors: [],
    radius: 0.04,
    angle: 0,
}
for (let i = 0; i <= 1000; i++)
{
    const x = joint1.radius * Math.cos(i * 2 * Math.PI / 200)
    const y = joint1.radius * Math.sin(i * 2 * Math.PI / 200)
    joint1.vertices.push(x, y);
    joint1.colors.push(0, 0, 1); // blue color
}
const joint2 = {...joint1};
joint2.angle = -110;
const joint3 = {...joint1};
joint3.angle = 0;

// catcher model
const catcher : {
    vertices: number[],
    colors: number[]
} = {
    vertices: [
        0.0, 0.0, 0.0,
        -0.05, -0.1, 0.0,
        0.05, -0.1, 0.0
    ],
    colors: []
}

for (let i = 0; i < 3; i++) 
{
    catcher.colors.push(1, 0, 0); // red color
}

// independent joint model
const joint4 : {
    vertices: number[],
    colors: number[],
    radius: number,
    angle: number
} = {
    vertices: [],
    colors: [],
    radius: 0.1,
    angle: 0
}
for (let i = 0; i <= 1000; i++)
{
    const x = joint4.radius * Math.cos(i * 2 * Math.PI / 200)
    const y = joint4.radius * Math.sin(i * 2 * Math.PI / 200)
    joint4.vertices.push(x, y);
    joint4.colors.push(0.5, 0.5, 0.5); // gray color
}

const joint5 = {...joint4};

const arm3 = {...arm1};
const arm4 = {...arm2};

let x_move = 0;
let y_move = 0;
let view = 1;

let ball_x = 0.5;
let ball_y = 0;

let joint_mode = 0;
let grab_mode = false;
let touch_mode = false;

let renderProgram:WebGLProgram;
let a_Position:number;
let a_Color:number;
let u_modelMatrix:number | null;

main();
function main()
{
    const canvas = document.getElementById("webgl") as HTMLCanvasElement | null;
    if(canvas == null) throw new Error("Canvas is null");
    
    const gl = canvas.getContext("webgl2");
    if(!gl)
    {
        console.log("Failed to get the rendering context for WebGL");
        return;
    }

    renderProgram = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);
    gl.useProgram(renderProgram);

    a_Position = gl.getAttribLocation(renderProgram, "a_Position");
    a_Color = gl.getAttribLocation(renderProgram, "a_Color");
    u_modelMatrix = gl.getUniformLocation(renderProgram, "u_modelMatrix") as number | null;
    if(u_modelMatrix == null) throw new Error("u_modelMatrix is null");

    if(a_Position < 0 || a_Color < 0 || u_modelMatrix < 0) 
    {
        console.log("Failed to get the storage location of a_Position or a_Color or u_modelMatrix");
    }
        
    document.addEventListener("keydown", (event)=> {    
        if( event.key == 'a' || event.key == 'A')
        { 
            console.log('A');
            x_move -= 0.05;
            draw(gl);

        }
        else if ( event.key == 'd' || event.key == 'D')
        {
            console.log('D');
            x_move += 0.05;
            draw(gl);

        }
        else if ( event.key == 's' || event.key == 'S')
        { 
            console.log('S');
            y_move -= 0.05;
            draw(gl);

        }
        else if ( event.key == 'w' || event.key == 'W')
        { 
            console.log('W');
            y_move += 0.05;
            draw(gl);

        }
        else if ( event.key == '1')
        { 
            console.log('1');
            joint_mode = 1;
            draw(gl);

        }
        else if ( event.key == '2')
        { 
            console.log('2');
            joint_mode = 2;
            draw(gl);

        }
        else if ( event.key == '3')
        { 
            console.log('3');
            joint_mode = 3;
            draw(gl);

        }
        else if ( event.key == '4')
        {
            console.log('4');
            joint_mode = 4;
            draw(gl);
        }
        else if ( event.key == '5')
        {
            console.log('5');
            joint_mode = 5;
            draw(gl);
        }
        else if (event.key === "ArrowLeft") 
        {
            console.log("ArrowLeft");
            if(joint_mode == 1)
            {
                joint1.angle += 10;
            }
            else if(joint_mode == 2)
            {
                joint2.angle += 10;
            }
            else if(joint_mode == 3)
            {
                joint3.angle += 10;
            }
            else if(joint_mode == 4)
            {
                joint4.angle += 10;
            }
            else if(joint_mode == 5)
            {
                joint5.angle += 10;
            }
            draw(gl);
        }
        else if (event.key === "ArrowRight") 
        {
            console.log("ArrowRight");
            if(joint_mode == 1)
            {
                joint1.angle -= 10;
            }
            else if(joint_mode == 2)
            {
                joint2.angle -= 10;
            }
            else if(joint_mode == 3)
            {
                joint3.angle -= 10;
            }
            else if(joint_mode == 4 && grab_mode)
            {
                joint4.angle -= 10;
            }
            else if(joint_mode == 5 && grab_mode)
            {
                joint5.angle -= 10;
            }
            draw(gl);
        }
        else if ( event.key == 'q' || event.key == 'Q')
        {
            console.log('Q');
            joint_mode = 0;
            draw(gl);
        }
        else if ( event.key == 'g' || event.key == 'G')
        {
            console.log('G');
            
            if(grab_mode == true)
            {
                grab_mode = false;
                console.log('grab_mode = false');
            }
            else if(touch_mode)
            {
                grab_mode = true;
                console.log('grab_mode = true');
            }
            draw(gl);
        }
        else if ( event.key == '+')
        {
            console.log('+');
            view += 0.1;
            draw(gl);
        }
        else if ( event.key == '-')
        {
            console.log('-');
            if(view > 0.1)
            {
                view -= 0.1;
            }
            draw(gl);
        }
    });

    draw(gl);
}

function draw(gl:WebGL2RenderingContext)
{
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    const transformMat = new Matrix4();

    // draw wheel1
    const wheel1Model: Interface = initVertexBufferForLaterUse(gl, wheel1.vertices, wheel1.colors);
    transformMat.setIdentity();
    transformMat.scale(view, view, view);
    transformMat.translate(-0.1 + x_move, -0.5 + y_move, 0);
    initAttributeVariable(gl, a_Position, wheel1Model.vertexBuffer);
    initAttributeVariable(gl, a_Color, wheel1Model.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLES, 0, wheel1Model.numVertices);

    // draw wheel2
    const wheel2Model: Interface = initVertexBufferForLaterUse(gl, wheel2.vertices, wheel2.colors);
    transformMat.setIdentity();
    transformMat.scale(view, view, view);
    transformMat.translate(0.1 + x_move, -0.5 + y_move, 0);
    initAttributeVariable(gl, a_Position, wheel2Model.vertexBuffer);
    initAttributeVariable(gl, a_Color, wheel2Model.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLES, 0, wheel2Model.numVertices);

    // draw body
    const bodyModel: Interface = initVertexBufferForLaterUse(gl, body.vertices, body.colors);
    transformMat.setIdentity();
    transformMat.scale(view, view, view);
    transformMat.translate(-0.2 + x_move, -0.25 + y_move, 0);
    initAttributeVariable(gl, a_Position, bodyModel.vertexBuffer);
    initAttributeVariable(gl, a_Color, bodyModel.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, bodyModel.numVertices);
    
    // draw head
    const headModel: Interface = initVertexBufferForLaterUse(gl, head.vertices, head.colors);
    transformMat.setIdentity();
    transformMat.scale(view, view, view);
    transformMat.translate(0 + x_move, -0.05 + y_move, 0);
    initAttributeVariable(gl, a_Position, headModel.vertexBuffer);
    initAttributeVariable(gl, a_Color, headModel.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, headModel.numVertices);

    // start to draw action part
    transformMat.setIdentity();
    transformMat.scale(view, view, view);
    // draw joint1
    const joint1Model: Interface = initVertexBufferForLaterUse(gl, joint1.vertices, joint1.colors);
    transformMat.translate(0 + x_move, -0.02 + y_move, 0);
    initAttributeVariable(gl, a_Position, joint1Model.vertexBuffer);
    initAttributeVariable(gl, a_Color, joint1Model.colorBuffer);
    transformMat.rotate(joint1.angle, 0, 0, 1);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, joint1Model.numVertices);

    // draw arm1
    const arm1Model: Interface = initVertexBufferForLaterUse(gl, arm1.vertices, arm1.colors);
    transformMat.translate(0, 0.3, 0);
    initAttributeVariable(gl, a_Position, arm1Model.vertexBuffer);
    initAttributeVariable(gl, a_Color, arm1Model.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, arm1Model.numVertices);

    // draw joint2
    const joint2Model: Interface = initVertexBufferForLaterUse(gl, joint2.vertices, joint2.colors);
    transformMat.translate(0, 0.05, 0);
    initAttributeVariable(gl, a_Position, joint2Model.vertexBuffer);
    initAttributeVariable(gl, a_Color, joint2Model.colorBuffer);
    transformMat.rotate(joint2.angle, 0, 0, 1);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, joint2Model.numVertices);

    // draw arm2
    const arm2Model: Interface = initVertexBufferForLaterUse(gl, arm2.vertices, arm2.colors);
    transformMat.translate(0, -0.05, 0);
    initAttributeVariable(gl, a_Position, arm2Model.vertexBuffer);
    initAttributeVariable(gl, a_Color, arm2Model.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, arm2Model.numVertices);

    // draw joint3
    const joint3Model: Interface = initVertexBufferForLaterUse(gl, joint3.vertices, joint3.colors);
    transformMat.translate(0, -0.3, 0);
    initAttributeVariable(gl, a_Position, joint3Model.vertexBuffer);
    initAttributeVariable(gl, a_Color, joint3Model.colorBuffer);
    transformMat.rotate(joint3.angle, 0, 0, 1);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, joint3Model.numVertices);

    // draw catcher
    const catcherModel: Interface = initVertexBufferForLaterUse(gl, catcher.vertices, catcher.colors);
    transformMat.translate(0, -0.05, 0);
    initAttributeVariable(gl, a_Position, catcherModel.vertexBuffer);
    initAttributeVariable(gl, a_Color, catcherModel.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, catcherModel.numVertices);

    // check if the ball is grabbed
    touch_mode = false;
    const transformMat_ball = new Matrix4();
    const catcher_point = [
        transformMat.multiplyVector4( new Vector4 ([...(catcher.vertices.slice(0, 3)), 1])).elements,
        transformMat.multiplyVector4( new Vector4 ([...(catcher.vertices.slice(3, 6)), 1])).elements,
        transformMat.multiplyVector4( new Vector4 ([...(catcher.vertices.slice(6, 9)), 1])).elements
    ];
    const circle_point =  transformMat_ball.multiplyVector4( new Vector4 ([0, 0, 0, 1])).elements;

    console.log(catcher_point);
    console.log(circle_point);
    console.log(Math.sqrt((catcher_point[0][0] - circle_point[0] - ball_x * view) ** 2 + (catcher_point[0][1] - circle_point[1] - ball_y * view) ** 2));
    console.log(Math.sqrt((catcher_point[1][0] - circle_point[0] - ball_x * view) ** 2 + (catcher_point[1][1] - circle_point[1] - ball_y * view) ** 2));
    console.log(Math.sqrt((catcher_point[2][0] - circle_point[0] - ball_x * view) ** 2 + (catcher_point[2][1] - circle_point[1] - ball_y * view) ** 2));
    console.log(joint4.radius * view);

    if (
        Math.sqrt((catcher_point[0][0] - circle_point[0] - ball_x * view) ** 2 + (catcher_point[0][1] - circle_point[1] - ball_y * view) ** 2) <= joint4.radius * view ||
        Math.sqrt((catcher_point[1][0] - circle_point[0] - ball_x * view) ** 2 + (catcher_point[1][1] - circle_point[1] - ball_y * view) ** 2) <= joint4.radius * view ||
        Math.sqrt((catcher_point[2][0] - circle_point[0] - ball_x * view) ** 2 + (catcher_point[2][1] - circle_point[1] - ball_y * view) ** 2) <= joint4.radius * view
    )
    {
        touch_mode = true;
    }

    // draw joint4
    transformMat_ball.scale(view, view, view);
    const ballModel: Interface = initVertexBufferForLaterUse(gl, joint4.vertices, joint4.colors);
    
    if (grab_mode)
    {
        ball_x = ((catcher_point[0][0] + catcher_point[1][0] + catcher_point[2][0]) / 3 ) * (1 / view) - 0.05;
        ball_y = ((catcher_point[0][1] + catcher_point[1][1] + catcher_point[2][1]) / 3 ) * (1 / view) + 0.05;
    }

    transformMat_ball.translate(ball_x, ball_y , 0);
    transformMat_ball.rotate(joint4.angle, 0, 0, 1);
    initAttributeVariable(gl, a_Position, ballModel.vertexBuffer);
    initAttributeVariable(gl, a_Color, ballModel.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat_ball.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, ballModel.numVertices);

    // draw arm3
    const arm3Model: Interface = initVertexBufferForLaterUse(gl, arm3.vertices, arm3.colors);
    transformMat_ball.translate(0, 0.34, 0);
    initAttributeVariable(gl, a_Position, arm3Model.vertexBuffer);
    initAttributeVariable(gl, a_Color, arm3Model.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat_ball.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, arm3Model.numVertices);

    // draw joint5
    const joint5Model: Interface = initVertexBufferForLaterUse(gl, joint5.vertices, joint5.colors);
    transformMat_ball.translate(0, 0.1, 0);
    transformMat_ball.rotate(joint5.angle, 0, 0, 1);
    
    initAttributeVariable(gl, a_Position, joint5Model.vertexBuffer);
    initAttributeVariable(gl, a_Color, joint5Model.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat_ball.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, joint5Model.numVertices);

    // draw arm4
    const arm4Model: Interface = initVertexBufferForLaterUse(gl, arm4.vertices, arm4.colors);
    transformMat_ball.translate(0, 0.34, 0);
    initAttributeVariable(gl, a_Position, arm4Model.vertexBuffer);
    initAttributeVariable(gl, a_Color, arm4Model.colorBuffer);
    gl.uniformMatrix4fv(u_modelMatrix, false, transformMat_ball.elements);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, arm4Model.numVertices);
}