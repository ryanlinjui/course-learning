import {
  compileShader
} from "../../lib/utils";

import {
    initAttributeVariable,
    initVertexBufferForLaterUse3D,
    initCubeTexture
} from "../../lib/init";

import {
    getNormalOnVertices,
} from "../../lib/cube";

import {
    Matrix4,
    Vector4,
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

let cameraX = 3, cameraY = 3, cameraZ = 7;

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

// ground 3D model
let ground: any[] = [];

// F: Face, T: Triangle, V: vertex (XYZ)
const groundVertices: number[] = [
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
    
    //F5_T1_V1,  F5_T1_V2,  F5_T1_V3,  F5_T2_V4,  F5_T2_V5,  F5_T2_V6,   // this row for the face y = -1.0
    -1.0, 1.0, 1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, 1.0, 1.0, -1.0, 1.0, 1.0,

    //F6_T1_V1,  F6_T1_V2,  F6_T1_V3,  F6_T2_V4,  F6_T2_V5,  F6_T2_V6,   //this row for the face z = -1.0
    1.0, -1.0, -1.0, 1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0, 1.0,
    -1.0, -1.0, 1.0, 1.0, -1.0, 1.0
];

// wheel 3D circle model
const wheel_radius = 0.2
const wheel_thickness = 0.2;

let wheel: any[] = [];
const wheelVertices: number[] = []

for (let i = 0; i < 360; i++)
{
    const angle1 = i * Math.PI / 180;
    const angle2 = (i + 1) * Math.PI / 180;
    const x1 = wheel_radius * Math.cos(angle1);
    const y1 = wheel_radius * Math.sin(angle1);
    const x2 = wheel_radius * Math.cos(angle2);
    const y2 = wheel_radius * Math.sin(angle2);
    
    wheelVertices.push(0, 0, 0);
    wheelVertices.push(x1, y1, 0);
    wheelVertices.push(x2, y2, 0);

    wheelVertices.push(x2, y2, 0);
    wheelVertices.push(x1, y1, 0);
    wheelVertices.push(x2, y2, wheel_thickness);

    wheelVertices.push(x2, y2, wheel_thickness);
    wheelVertices.push(x1, y1, 0);
    wheelVertices.push(x2, y2, 0);

    wheelVertices.push(x1, y1, 0);
    wheelVertices.push(x1, y1, wheel_thickness);
    wheelVertices.push(x2, y2, wheel_thickness);

    wheelVertices.push(x2, y2, wheel_thickness);
    wheelVertices.push(x1, y1, wheel_thickness);
    wheelVertices.push(0, 0, wheel_thickness);
}

// body 3D rectangle model
const body_length = 2;
const body_width = 0.6;
const body_height = 0.6;

let body: any[] = [];
const bodyVertices: number[] = []

for (let i = 0; i < 6; i++)
{
    bodyVertices.push(0, 0, 0);
    bodyVertices.push(0, body_height, 0);
    bodyVertices.push(body_length, body_height, 0);

    bodyVertices.push(body_length, body_height, 0);
    bodyVertices.push(body_length, 0, 0);
    bodyVertices.push(0, 0, 0);

    bodyVertices.push(0, 0, body_width);
    bodyVertices.push(0, body_height, body_width);
    bodyVertices.push(body_length, body_height, body_width);

    bodyVertices.push(body_length, body_height, body_width);
    bodyVertices.push(body_length, 0, body_width);
    bodyVertices.push(0, 0, body_width);

    bodyVertices.push(0, body_height, 0);
    bodyVertices.push(0, body_height, body_width);
    bodyVertices.push(body_length, body_height, body_width);

    bodyVertices.push(body_length, body_height, body_width);
    bodyVertices.push(body_length, body_height, 0);
    bodyVertices.push(0, body_height, 0);

    bodyVertices.push(0, 0, 0);
    bodyVertices.push(0, 0, body_width);
    bodyVertices.push(body_length, 0, body_width);

    bodyVertices.push(body_length, 0, body_width);
    bodyVertices.push(body_length, 0, 0);
    bodyVertices.push(0, 0, 0);

    bodyVertices.push(0, 0, 0);
    bodyVertices.push(0, 0, body_width);
    bodyVertices.push(0, body_height, body_width);

    bodyVertices.push(0, body_height, body_width);
    bodyVertices.push(0, body_height, 0);
    bodyVertices.push(0, 0, 0);

    bodyVertices.push(body_length, 0, 0);
    bodyVertices.push(body_length, 0, body_width);
    bodyVertices.push(body_length, body_height, body_width);

    bodyVertices.push(body_length, body_height, body_width);
    bodyVertices.push(body_length, body_height, 0);
    bodyVertices.push(body_length, 0, 0);
}

// head 3D triangle model
const head_thickness = 0.6;
const head_size = 0.6;

let head: any[] = [];
const headVertices: number[] = []

for (let i = 0; i < 3; i++)
{
    const angle1 = i * 2 * Math.PI / 3 - Math.PI / 6;
    const angle2 = (i + 1) * 2 * Math.PI / 3 - Math.PI / 6;
    const x1 = head_size * Math.cos(angle1);
    const y1 = head_size * Math.sin(angle1);
    const x2 = head_size * Math.cos(angle2);
    const y2 = head_size * Math.sin(angle2);
    
    headVertices.push(0, 0, 0);
    headVertices.push(x1, y1, 0);
    headVertices.push(x2, y2, 0);
    headVertices.push(x2, y2, 0);
    headVertices.push(x1, y1, 0);
    headVertices.push(x2, y2, head_thickness);
    headVertices.push(x2, y2, head_thickness);
    headVertices.push(x1, y1, 0);
    headVertices.push(x2, y2, 0);
    headVertices.push(x1, y1, 0);
    headVertices.push(x1, y1, head_thickness);
    headVertices.push(x2, y2, head_thickness);
    headVertices.push(x2, y2, head_thickness);
    headVertices.push(x1, y1, head_thickness);
    headVertices.push(0, 0, head_thickness);
}

// joint 3D circle model
const joint_radius = 0.1
const joint_thickness = 0.6;

let joint: any[] = [];
const jointVertices: number[] = []

for (let i = 0; i < 360; i++)
{
    const angle1 = i * Math.PI / 180;
    const angle2 = (i + 1) * Math.PI / 180;
    const x1 = joint_radius * Math.cos(angle1);
    const y1 = joint_radius * Math.sin(angle1);
    const x2 = joint_radius * Math.cos(angle2);
    const y2 = joint_radius * Math.sin(angle2);
    
    jointVertices.push(0, 0, 0);
    jointVertices.push(x1, y1, 0);
    jointVertices.push(x2, y2, 0);

    jointVertices.push(x2, y2, 0);
    jointVertices.push(x1, y1, 0);
    jointVertices.push(x2, y2, joint_thickness);

    jointVertices.push(x2, y2, joint_thickness);
    jointVertices.push(x1, y1, 0);
    jointVertices.push(x2, y2, 0);

    jointVertices.push(x1, y1, 0);
    jointVertices.push(x1, y1, joint_thickness);
    jointVertices.push(x2, y2, joint_thickness);

    jointVertices.push(x2, y2, joint_thickness);
    jointVertices.push(x1, y1, joint_thickness);
    jointVertices.push(0, 0, joint_thickness);
}

// arm 3D rectangle model
const arm_length = 0.2;
const arm_width = 0.6;
const arm_height = 0.6;

let arm: any[] = [];
const armVertices: number[] = []

for (let i = 0; i < 6; i++)
{
    armVertices.push(0, 0, 0);
    armVertices.push(0, arm_height, 0);
    armVertices.push(arm_length, arm_height, 0);

    armVertices.push(arm_length, arm_height, 0);
    armVertices.push(arm_length, 0, 0);
    armVertices.push(0, 0, 0);

    armVertices.push(0, 0, arm_width);
    armVertices.push(0, arm_height, arm_width);
    armVertices.push(arm_length, arm_height, arm_width);

    armVertices.push(arm_length, arm_height, arm_width);
    armVertices.push(arm_length, 0, arm_width);
    armVertices.push(0, 0, arm_width);

    armVertices.push(0, arm_height, 0);
    armVertices.push(0, arm_height, arm_width);
    armVertices.push(arm_length, arm_height, arm_width);

    armVertices.push(arm_length, arm_height, arm_width);
    armVertices.push(arm_length, arm_height, 0);
    armVertices.push(0, arm_height, 0);

    armVertices.push(0, 0, 0);
    armVertices.push(0, 0, arm_width);
    armVertices.push(arm_length, 0, arm_width);

    armVertices.push(arm_length, 0, arm_width);
    armVertices.push(arm_length, 0, 0);
    armVertices.push(0, 0, 0);

    armVertices.push(0, 0, 0);
    armVertices.push(0, 0, arm_width);
    armVertices.push(0, arm_height, arm_width);

    armVertices.push(0, arm_height, arm_width);
    armVertices.push(0, arm_height, 0);
    armVertices.push(0, 0, 0);

    armVertices.push(arm_length, 0, 0);
    armVertices.push(arm_length, 0, arm_width);
    armVertices.push(arm_length, arm_height, arm_width);

    armVertices.push(arm_length, arm_height, arm_width);
    armVertices.push(arm_length, arm_height, 0);
    armVertices.push(arm_length, 0, 0);
}

// catcher 3D triangle model
const catcher_thickness = 0.6;
const catcher_size = 0.2;

let catcher: any[] = [];
const catcherVertices: number[] = []

for (let i = 0; i < 3; i++)
{
    const angle1 = i * 2 * Math.PI / 3 - Math.PI / 6;
    const angle2 = (i + 1) * 2 * Math.PI / 3 - Math.PI / 6;
    const x1 = catcher_size * Math.cos(angle1);
    const y1 = catcher_size * Math.sin(angle1);
    const x2 = catcher_size * Math.cos(angle2);
    const y2 = catcher_size * Math.sin(angle2);
    
    catcherVertices.push(0, 0, 0);
    catcherVertices.push(x1, y1, 0);
    catcherVertices.push(x2, y2, 0);
    catcherVertices.push(x2, y2, 0);
    catcherVertices.push(x1, y1, 0);
    catcherVertices.push(x2, y2, catcher_thickness);
    catcherVertices.push(x2, y2, catcher_thickness);
    catcherVertices.push(x1, y1, 0);
    catcherVertices.push(x2, y2, 0);
    catcherVertices.push(x1, y1, 0);
    catcherVertices.push(x1, y1, catcher_thickness);
    catcherVertices.push(x2, y2, catcher_thickness);
    catcherVertices.push(x2, y2, catcher_thickness);
    catcherVertices.push(x1, y1, catcher_thickness);
    catcherVertices.push(0, 0, catcher_thickness);
}

let view = 0.5;
const init_sight = -3;

let x_move = 0;
let y_move = 0;
let z_move = 0;

let fly_mode = false;

let material_x = 2;
let material_y = -1;
let material_z = 2;

let joint1_angle = 0;
let joint2_angle = 0;
let joint3_angle = 0;
let joint4_angle = 0;
let joint5_angle = 0;

let joint_mode = 0;
let grab_mode = false;
let touch_mode = false;

let program: WebGLProgram;

let quadObj: any;
let cubeMapTex: WebGLTexture | null;

let quadProgram: WebGLProgram;
let quad_a_Position: number;
let quad_u_envCubeMap: WebGLUniformLocation | null;
let quad_u_viewDirectionProjectionInverse: WebGLUniformLocation | null;

const cameraDirX = 0, cameraDirY = 0, cameraDirZ = -1;

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
        "scene-texture.jpg",
        "scene-texture.jpg",
        "scene-texture.jpg",
        "scene-texture.jpg",
        "scene-texture.jpg",
        "scene-texture.jpg",
        512,
        512
    );

    program = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);

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

    const groundNormals = getNormalOnVertices(groundVertices);
    const goundObject = initVertexBufferForLaterUse3D(gl, groundVertices, groundNormals, null);
    ground.push(goundObject);

    const wheelNormals = getNormalOnVertices(wheelVertices);
    const wheelObject = initVertexBufferForLaterUse3D(gl, wheelVertices, wheelNormals, null);
    wheel.push(wheelObject);

    const bodyNormals = getNormalOnVertices(bodyVertices);
    const bodyObject = initVertexBufferForLaterUse3D(gl, bodyVertices, bodyNormals, null);
    body.push(bodyObject);

    const headNormals = getNormalOnVertices(headVertices);
    const headObject = initVertexBufferForLaterUse3D(gl, headVertices, headNormals, null);
    head.push(headObject);

    const jointNormals = getNormalOnVertices(jointVertices);
    const jointObject = initVertexBufferForLaterUse3D(gl, jointVertices, jointNormals, null);
    joint.push(jointObject);

    const armNormals = getNormalOnVertices(armVertices);
    const armObject = initVertexBufferForLaterUse3D(gl, armVertices, armNormals, null);
    arm.push(armObject);

    const catcherNormals = getNormalOnVertices(catcherVertices);
    const catcherObject = initVertexBufferForLaterUse3D(gl, catcherVertices, catcherNormals, null);
    catcher.push(catcherObject);

    mvpMatrix = new Matrix4();
    modelMatrix = new Matrix4();
    normalMatrix = new Matrix4();

    gl.enable(gl.DEPTH_TEST);


    document.addEventListener("keydown", (event)=> {    
        if( event.key == 'a' || event.key == 'A')
        { 
            console.log('A');
            x_move -= 0.1;
            draw();

        }
        else if ( event.key == 'd' || event.key == 'D')
        {
            console.log('D');
            x_move += 0.1;
            draw();

        }
        else if ( event.key == 's' || event.key == 'S')
        { 
            console.log('S');
            if (fly_mode)
            {
                if (y_move < 0.1)
                {
                    y_move = 0.1;
                }
                y_move -= 0.1;
            }
            else
            {
                z_move += 0.1;
            }
            draw();

        }
        else if ( event.key == 'w' || event.key == 'W')
        { 
            console.log('W');
            if (fly_mode)
            {
                y_move += 0.1;
            }
            else
            {
                z_move -= 0.1;
            }
            draw();

        }
        else if ( event.key == 'f' || event.key == 'F')
        {
            console.log('F');
            if(fly_mode == true)
            {
                fly_mode = false;
                console.log('fly_mode = false');
            }
            else
            {
                fly_mode = true;
                console.log('fly_mode = true');
            }
            draw();   
        }
        else if ( event.key == '1')
        { 
            console.log('1');
            joint_mode = 1;
            draw();

        }
        else if ( event.key == '2')
        { 
            console.log('2');
            joint_mode = 2;
            draw();

        }
        else if ( event.key == '3')
        { 
            console.log('3');
            joint_mode = 3;
            draw();

        }
        else if ( event.key == '4')
        {
            console.log('4');
            joint_mode = 4;
            draw();
        }
        else if ( event.key == '5')
        {
            console.log('5');
            joint_mode = 5;
            draw();
        }
        else if (event.key === "ArrowLeft") 
        {
            console.log("ArrowLeft");
            if(joint_mode == 1)
            {
                joint1_angle += 10;
            }
            else if(joint_mode == 2)
            {
                joint2_angle += 10;
            }
            else if(joint_mode == 3)
            {
                joint3_angle += 10;
            }
            else if(joint_mode == 4)
            {
                joint4_angle += 10;
            }
            else if(joint_mode == 5)
            {
                joint5_angle += 10;
            }
            draw();
        }
        else if (event.key === "ArrowRight") 
        {
            console.log("ArrowRight");
            if(joint_mode == 1)
            {
                joint1_angle -= 10;
            }
            else if(joint_mode == 2)
            {
                joint2_angle -= 10;
            }
            else if(joint_mode == 3)
            {
                joint3_angle -= 10;
            }
            else if(joint_mode == 4 && grab_mode)
            {
                joint4_angle -= 10;
            }
            else if(joint_mode == 5 && grab_mode)
            {
                joint5_angle -= 10;
            }
            draw();
        }
        else if ( event.key == 'q' || event.key == 'Q')
        {
            console.log('Q');
            joint_mode = 0;
            draw();
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
            draw();
        }
    });

    draw(); // draw it once before mouse move

    canvas.onmousedown = function(ev){mouseDown(ev)};
    canvas.onmousemove = function(ev){mouseMove(ev)};
    canvas.onmouseup = function(){mouseUp()};
    canvas.onwheel = function(ev){mouseScroll(ev)};
}

function draw()
{
    if (gl == null)
    {
        throw new Error("gl is null");
    }

    if (canvas == null)
    {
        throw new Error("Canvas is null");
    }
    
    // set the scene
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
    viewMatrixRotationOnly.elements[12] = 0;
    viewMatrixRotationOnly.elements[13] = 0;
    viewMatrixRotationOnly.elements[14] = 0;
    vpFromCamera.multiply(viewMatrixRotationOnly);
    const vpFromCameraInverse = vpFromCamera.invert();

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


    // draw the 3D objects
    gl.useProgram(program);
    
    // draw ground with red color
    const transformMat = new Matrix4();
    transformMat.setIdentity();
    transformMat.scale(4 * view, 0.1 * view, 4 * view);
    transformMat.translate(0, init_sight * 10, 0);
    drawOneObject(
        ground,
        transformMat,
        1.0, 0.4, 0.4
    );

    // draw wheel1 with green color
    transformMat.setIdentity();
    transformMat.scale(view, view, view);
    transformMat.translate(-0.5 + x_move, 0.3 + y_move + init_sight, z_move);
    drawOneObject(
        wheel,
        transformMat,
        0.4, 1.0, 0.4
    );

    // draw wheel2 with green color
    transformMat.setIdentity();
    transformMat.scale(view, view, view);
    transformMat.translate(0.5 + x_move, 0.3 + y_move + init_sight, z_move);
    drawOneObject(
        wheel,
        transformMat,
        0.4, 1.0, 0.4
    );

    // draw body with green color
    transformMat.setIdentity();
    transformMat.scale(view, view, view);
    transformMat.translate(-1 + x_move, 0.5 + y_move + init_sight, -0.2 + z_move);
    drawOneObject(
        body,
        transformMat,
        0.4, 1.0, 0.4
    );

    // draw head with green color
    transformMat.setIdentity();
    transformMat.scale(view, view, view);
    transformMat.translate(x_move, 1.4 + y_move + init_sight, -0.2 + z_move);
    drawOneObject(
        head,
        transformMat,
        0.4, 1.0, 0.4
    );
    
    // start to draw action part
    transformMat.setIdentity();
    transformMat.scale(view, view, view);

    // draw joint1 with blue color
    transformMat.translate(x_move, 2.1 + y_move + init_sight, -0.2 + z_move);
    drawOneObject(
        joint,
        transformMat,
        0.4, 0.4, 1.0
    );
    transformMat.rotate(joint1_angle, 0, 0, 1);

    // draw arm1 with white color
    transformMat.translate(-0.1, 0.1, 0);
    drawOneObject(
        arm,
        transformMat,
        1.0, 1.0, 1.0
    );

    // draw joint2 with blue color
    transformMat.translate(0.1, 0.7, 0);
    drawOneObject(
        joint,
        transformMat,
        0.4, 0.4, 1.0
    );
    transformMat.rotate(joint2_angle, 0, 0, 1);

    // draw arm2 with white color
    transformMat.translate(-0.1, 0.1, 0);
    drawOneObject(
        arm,
        transformMat,
        1.0, 1.0, 1.0
    );

    // draw joint3 with blue color
    transformMat.translate(0.1, 0.7, 0);
    drawOneObject(
        joint,
        transformMat,
        0.4, 0.4, 1.0
    );
    transformMat.rotate(joint3_angle, 0, 0, 1);

    // draw catcher with red color
    transformMat.translate(-0.25, 0.1, 0);
    drawOneObject(
        catcher,
        transformMat,
        1.0, 0.4, 0.4
    );

    // check if the material is grabbed
    touch_mode = false;
    const transformMat_material = new Matrix4();
    const catcher_point = [
        transformMat.multiplyVector4( new Vector4 ([...(catcherVertices.slice(0, 3)), 1])).elements,
        transformMat.multiplyVector4( new Vector4 ([...(catcherVertices.slice(3, 6)), 1])).elements,
        transformMat.multiplyVector4( new Vector4 ([...(catcherVertices.slice(6, 9)), 1])).elements
    ];
    const circle_point =  transformMat_material.multiplyVector4( new Vector4 ([0, 0, 0, 1])).elements;

    // console.log(catcher_point);
    // console.log(circle_point);
    // console.log(Math.sqrt((catcher_point[0][0] - circle_point[0] - material_x * view) ** 2 + (catcher_point[0][1] - circle_point[1] - material_y * view) ** 2));
    // console.log(Math.sqrt((catcher_point[1][0] - circle_point[0] - material_x * view) ** 2 + (catcher_point[1][1] - circle_point[1] - material_y * view) ** 2));
    // console.log(Math.sqrt((catcher_point[2][0] - circle_point[0] - material_x * view) ** 2 + (catcher_point[2][1] - circle_point[1] - material_y * view) ** 2));
    // console.log(joint_radius * view);

    let joint4_colorR = 0.4;
    let joint4_colorG = 0.4;
    let joint4_colorB = 1.0;
    if (
        Math.sqrt((catcher_point[0][0] - circle_point[0] - material_x * view) ** 2 + (catcher_point[0][1] - circle_point[1] - material_y * view) ** 2) <= joint_radius * view ||
        Math.sqrt((catcher_point[1][0] - circle_point[0] - material_x * view) ** 2 + (catcher_point[1][1] - circle_point[1] - material_y * view) ** 2) <= joint_radius * view ||
        Math.sqrt((catcher_point[2][0] - circle_point[0] - material_x * view) ** 2 + (catcher_point[2][1] - circle_point[1] - material_y * view) ** 2) <= joint_radius * view
    )
    {
        touch_mode = true;

        // change color to white if the material is grabbed and the joint4 is touched
        joint4_colorR = 1.0;
        joint4_colorG = 1.0;
        joint4_colorB = 1.0;
    }

    // draw joint4 with blue color
    transformMat_material.scale(view, view, view);

    if (grab_mode)
    {
        material_x = ((catcher_point[0][0] + catcher_point[1][0] + catcher_point[2][0]) / 3 ) * (1 / view) - 0.2;
        material_y = ((catcher_point[0][1] + catcher_point[1][1] + catcher_point[2][1]) / 3 ) * (1 / view) + 0.2;
        material_z = ((catcher_point[0][2] + catcher_point[1][2] + catcher_point[2][2]) / 3 ) * (1 / view);
    }

    transformMat_material.translate(material_x, material_y, material_z);
    transformMat_material.rotate(joint4_angle, 0, 0, 1);
    drawOneObject(
        joint,
        transformMat_material,
        joint4_colorR, joint4_colorG, joint4_colorB
    );

    // draw arm3 with white color
    transformMat_material.translate(-0.1, 0.1, 0);
    drawOneObject(
        arm,
        transformMat_material,
        1.0, 1.0, 1.0
    );

    // draw joint5 with blue color
    transformMat_material.translate(0.1, 0.7, 0);
    transformMat_material.rotate(joint5_angle, 0, 0, 1);
    drawOneObject(
        joint,
        transformMat_material,
        0.4, 0.4, 1.0
    );

    // draw arm4 with white color
    transformMat_material.translate(-0.1, 0.1, 0);
    drawOneObject(
        arm,
        transformMat_material,
        1.0, 1.0, 1.0
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

function mouseScroll(ev: WheelEvent)
{
    ev.preventDefault();
    
    view -= ev.deltaY * 0.0005;
    
    if (view < 0)
    {
        view = 0;
    }

    draw();
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
        const factor = 100 / canvas.height;
        const dx = factor * (x - mouseLastX);
        const dy = factor * (y - mouseLastY);

        angleX += dx;
        angleY += dy;
    }
    mouseLastX = x;
    mouseLastY = y;

    draw();
}