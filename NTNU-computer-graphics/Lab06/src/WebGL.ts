import {
    compileShader
} from "../../utils"

import {
    initVertexBuffers
} from "./init"

import {
    Matrix4
} from "./cuon-matrix"

const VSHADER_SOURCE = `
    attribute vec4 a_Position;
    attribute vec4 a_Color;
    attribute vec4 a_Normal;
    uniform mat4 u_MvpMatrix;
    uniform mat4 u_modelMatrix;
    uniform mat4 u_normalMatrix;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    varying vec4 v_Color;
    void main()
    {
        // TODO-1: transform "a_Position" to clip space and store in "gl_Position"
        gl_Position = u_MvpMatrix * a_Position;

        // TODO-2: transform "a_Position" to world space and store its first three elements to "v_PositionInWorld"
        v_PositionInWorld = (u_modelMatrix * a_Position).xyz;

        // TODO-3: transform normal vector "a_Normal" to world space using "u_normalMatrix" and store the result in "v_Normal", remember to renormalize the result before storing it to v_Normal
        v_Normal = normalize((u_normalMatrix * a_Normal).xyz);
        
        // TODO-4: set "a_Color" to "v_Color"
        v_Color = a_Color;
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
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    varying vec4 v_Color;
    void main()
    {
        // let ambient and diffuse color are v_Color 
        // (you can also input them from ouside and make them different)
        vec3 ambientLightColor = v_Color.rgb;
        vec3 diffuseLightColor = v_Color.rgb;

        // assume white specular light (you can also input it from ouside)
        vec3 specularLightColor = vec3(1.0, 1.0, 1.0);        

        // TODO-5: calculate ambient light color using "ambientLightColor" and "u_Ka"
        vec3 ambient = ambientLightColor * u_Ka;        
        vec3 normal = normalize(v_Normal); // normalize the v_Normal before using it, before it comes from normal vectors interpolation
        
        // TODO-6: calculate diffuse light color using "normal", "u_LightPosition", "v_PositionInWorld", "diffuseLightColor", and "u_Kd"
        vec3 lightDirection = normalize(u_LightPosition - v_PositionInWorld);
        float nDotL = max(dot(normal, lightDirection), 0.0);
        vec3 diffuse = diffuseLightColor * nDotL * u_Kd;
        
        vec3 specular = vec3(0.0, 0.0, 0.0); 
        if(nDotL > 0.0) 
        {
            // TODO-7: calculate specular light color using "normal", "u_LightPosition", "v_PositionInWorld", "u_ViewPosition", "u_shininess", "specularLightColor", and "u_Ks"
            // You probably can store the result of specular calculation into "specular" variable
            
            vec3 viewDirection = normalize(u_ViewPosition - v_PositionInWorld);
            vec3 reflectDirection = reflect(-lightDirection, normal);
            float rDotV = max(dot(reflectDirection, viewDirection), 0.0);
            specular = specularLightColor * pow(rDotV, u_shininess) * u_Ks;            
        }

        // TODO-8: sum up ambient, diffuse, specular light color from above calculation and put them into "gl_FragColor"
        gl_FragColor = vec4(ambient + diffuse + specular, v_Color.a);
    }
`;

let mouseLastX = 0, mouseLastY = 0;
let mouseDragging = false;
let angleX = 0, angleY = 0;
let gl: WebGL2RenderingContext | null;
let canvas: HTMLCanvasElement | null;
let program: WebGLProgram;

let u_MvpMatrix: WebGLUniformLocation | null;
let u_modelMatrix: WebGLUniformLocation | null;
let u_normalMatrix: WebGLUniformLocation | null;
let u_LightPosition: WebGLUniformLocation | null;
let u_ViewPosition: WebGLUniformLocation | null;
let u_Ka: WebGLUniformLocation | null;
let u_Kd: WebGLUniformLocation | null;
let u_Ks: WebGLUniformLocation | null;
let u_shininess: WebGLUniformLocation | null;

const mvpMatrix = new Matrix4();
const modelMatrix = new Matrix4();
const normalMatrix = new Matrix4();

let nVertex = 0;

let cameraX = 3, cameraY = 3, cameraZ = 7;

main();
function main()
{
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

    u_MvpMatrix = gl.getUniformLocation(program, "u_MvpMatrix"); 
    u_modelMatrix = gl.getUniformLocation(program, "u_modelMatrix"); 
    u_normalMatrix = gl.getUniformLocation(program, "u_normalMatrix");
    u_LightPosition = gl.getUniformLocation(program, "u_LightPosition");
    u_ViewPosition = gl.getUniformLocation(program, "u_ViewPosition");
    u_Ka = gl.getUniformLocation(program, "u_Ka"); 
    u_Kd = gl.getUniformLocation(program, "u_Kd");
    u_Ks = gl.getUniformLocation(program, "u_Ks");
    u_shininess = gl.getUniformLocation(program, "u_shininess");

    if (u_MvpMatrix == null)
    {
        throw new Error("Failed to get the storage location of u_MvpMatrix");
    }
    if (u_modelMatrix == null)
    {
        throw new Error("Failed to get the storage location of u_modelMatrix");
    }
    if (u_normalMatrix == null)
    {
        throw new Error("Failed to get the storage location of u_normalMatrix");
    }
    if (u_LightPosition == null)
    {
        throw new Error("Failed to get the storage location of u_LightPosition");
    }
    if (u_ViewPosition == null)
    {
        throw new Error("Failed to get the storage location of u_ViewPosition");
    }
    if (u_Ka == null)
    {
        throw new Error("Failed to get the storage location of u_Ka");
    }
    if (u_Kd == null)
    {
        throw new Error("Failed to get the storage location of u_Kd");
    }
    if (u_Ks == null)
    {
        throw new Error("Failed to get the storage location of u_Ks");
    }
    if (u_shininess == null)
    {
        throw new Error("Failed to get the storage location of u_shininess");
    }

    nVertex = initVertexBuffers(gl, program);

    gl.enable(gl.DEPTH_TEST);

    draw(); // draw it once before mouse move

    canvas.onmousedown = function(ev){mouseDown(ev)};
    canvas.onmousemove = function(ev){mouseMove(ev)};
    canvas.onmouseup = function(ev){mouseUp(ev)};
}

function draw()
{
    if(!gl) 
    {
        throw new Error("gl is null");
    }

    gl.clearColor(0,0,0,1);

    //model Matrix (part of the mvp matrix)
    modelMatrix.setRotate(angleY, 1, 0, 0); //for mouse rotation
    modelMatrix.rotate(angleX, 0, 1, 0); //for mouse rotation
    modelMatrix.translate(0.0, 0.0, -1.0);
    modelMatrix.scale(1.0, 0.5, 2.0);

    //mvp: projection * view * model matrix  
    mvpMatrix.setPerspective(30, 1, 1, 100);
    mvpMatrix.lookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
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


    gl.uniformMatrix4fv(u_MvpMatrix, false, mvpMatrix.elements);
    gl.uniformMatrix4fv(u_modelMatrix, false, modelMatrix.elements);
    gl.uniformMatrix4fv(u_normalMatrix, false, normalMatrix.elements);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    
    gl.drawArrays(gl.TRIANGLES, 0, nVertex);
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
    if(!canvas)
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