import {
    Matrix4
} from "../../lib/cuon-matrix";
import {
    loadOBJtoCreateVBO
} from "../../lib/cube";

import {
    drawOneObjectOnShadowfbo,
    drawOneObjectOnScreen,
    drawDynamicReflectionObject
} from "./draw";
import {
    Program,
    ProgramShadow,
    ProgramTextureOnCube
} from "./shader";


let cubeObj: any[] = [];
let playerObj: any[] = [];
let bombObj: any[] = [];
let coinObj: any[] = [];
let claw_machineObj: any[] = [];
let lightObj: any[] = [];
let clawObj: any[] = [];

let bearObj: any[] = [];
let catObj: any[] = [];
let cool_headObj: any[] = [];

export async function load_all_model(gl: WebGL2RenderingContext)
{
    cubeObj = await loadOBJtoCreateVBO(gl, "obj/cube.obj");
    playerObj = await loadOBJtoCreateVBO(gl, "obj/apple.obj");
    bombObj = await loadOBJtoCreateVBO(gl, "obj/bomb.obj");
    coinObj = await loadOBJtoCreateVBO(gl, "obj/coin.obj");
    claw_machineObj = await loadOBJtoCreateVBO(gl, "obj/claw-machine.obj");
    lightObj = await loadOBJtoCreateVBO(gl, "obj/light.obj");
    clawObj = await loadOBJtoCreateVBO(gl, "obj/claw.obj");

    bearObj = await loadOBJtoCreateVBO(gl, "obj/doll/bear.obj");
    catObj = await loadOBJtoCreateVBO(gl, "obj/doll/cat.obj");
    cool_headObj = await loadOBJtoCreateVBO(gl, "obj/doll/cool-head.obj");
}

let groundMdlMatrix = new Matrix4();
let playerMdlMatrix = new Matrix4();
let bombMdlMatrix = new Matrix4();
let bomb2MdlMatrix = new Matrix4();
let coinMdlMatrix = new Matrix4();
let claw_machineMdlMatrix = new Matrix4();
let lightMdlMatrix = new Matrix4();
let clawMdlMatrix = new Matrix4();

let bearMdlMatrix = new Matrix4();
let catMdlMatrix = new Matrix4();
let cool_headMdlMatrix = new Matrix4();

let groundMdlFromLight = new Matrix4();
let playerMdlFromLight = new Matrix4();
let bomb2MdlFromLight = new Matrix4();
let claw_machineMdlFromLight = new Matrix4();

let bomb2_angle = 0;

export function set_mdl(
    playerX: number, playerY: number, playerZ: number,
    clawX: number, clawY: number, clawZ: number,
    third_view: boolean,
    angleX: number, angleY: number
)
{
    // set ground mdl
    groundMdlMatrix.setIdentity();
    groundMdlMatrix.translate(20.0, 1, 0);
    groundMdlMatrix.scale(45.0, 0.1, 35.0);

    // set player mdl
    playerMdlMatrix.setIdentity();
    playerMdlMatrix.translate(5, 1, 0);
    playerMdlMatrix.translate(playerX, playerY - 0.3, playerZ);
    playerMdlMatrix.scale(3.0, 3.0, 3.0);

    // set light mdl
    lightMdlMatrix.setIdentity();
    lightMdlMatrix.translate(-20, 30, 0);
    lightMdlMatrix.scale(1.0, 1.0, 1.0);

    // set claw mdl
    clawMdlMatrix.setIdentity();
    clawMdlMatrix.translate(clawX, clawY, clawZ);
    clawMdlMatrix.scale(0.5, 0.5, 0.5);
    clawMdlMatrix.rotate(160, 1, 0, 0);

    // set bear mdl
    bearMdlMatrix.setIdentity();
    bearMdlMatrix.translate(35, 1, 3);
    bearMdlMatrix.scale(0.01, 0.01, 0.01);
    bearMdlMatrix.rotate(-90, 0, 1, 0);

    // set cat mdl
    catMdlMatrix.setIdentity();
    catMdlMatrix.translate(35, 1, 5);
    catMdlMatrix.scale(5.0, 5.0, 5.0);
    catMdlMatrix.rotate(90, 0, 1, 0);

    // set cool_head mdl
    cool_headMdlMatrix.setIdentity();
    cool_headMdlMatrix.translate(35, 1, 7);
    cool_headMdlMatrix.scale(0.15, 0.15, 0.15);
    cool_headMdlMatrix.rotate(90, 0, 1, 0);
    cool_headMdlMatrix.rotate(-90, 1, 0, 0);
    cool_headMdlMatrix.rotate(180, 0, 0, 1);

    if (third_view)
    {
        bombMdlMatrix.setIdentity();
        bombMdlMatrix.translate(playerX + 3, playerY + 2.5, playerZ - 1);
        bombMdlMatrix.rotate(angleY, 0, 0, -1);
        bombMdlMatrix.rotate(angleX, 0, -1, 0);
        bombMdlMatrix.translate(3.2, -1, 1.2);
        bombMdlMatrix.scale(0.6, 0.6, 0.6);

        coinMdlMatrix.setIdentity();
        coinMdlMatrix.translate(playerX + 3, playerY + 2.5, playerZ - 1);
        coinMdlMatrix.rotate(angleY, 0, 0, -1);
        coinMdlMatrix.rotate(angleX, 0, -1, 0);
        coinMdlMatrix.translate(3.2, -1, 1.2);
        coinMdlMatrix.scale(0.6, 0.6, 0.6);
    }
    else
    {
        bombMdlMatrix.setIdentity();
        bombMdlMatrix.translate(playerX, playerY, playerZ);
        bombMdlMatrix.translate(0, 4.5, 0);
        bombMdlMatrix.rotate(angleX - 5, 0, -1, 0);
        bombMdlMatrix.rotate(angleY, 0, 0, -1);
        bombMdlMatrix.rotate(-5, 1, 0, 0);
        bombMdlMatrix.translate(5, -2.0, 1);

        coinMdlMatrix.setIdentity();
        coinMdlMatrix.translate(playerX, playerY, playerZ);
        coinMdlMatrix.translate(0, 4.5, 0);
        coinMdlMatrix.rotate(angleX - 5, 0, -1, 0);
        coinMdlMatrix.rotate(angleY, 0, 0, -1);
        coinMdlMatrix.rotate(-5, 1, 0, 0);
        coinMdlMatrix.translate(5, -2.0, 1);
    }

    // set claw machine mdl
    claw_machineMdlMatrix.setIdentity();
    claw_machineMdlMatrix.translate(50, 1, 10);
    claw_machineMdlMatrix.scale(15.0, 15.0, 15.0);
    claw_machineMdlMatrix.rotate(90, 0, 1, 0);

    // set bomb2 mdl
    bomb2MdlMatrix.setIdentity();
    bomb2MdlMatrix.translate(30, 20, 0);
    bomb2MdlMatrix.scale(4.0, 4.0, 4.0);
    bomb2MdlMatrix.rotate(bomb2_angle, 1, 0, 1);
    bomb2_angle += 1;
}

export function draw_all_shadow(
    gl: WebGL2RenderingContext, shadowProgram: ProgramShadow,
    offScreenWidth: number, offScreenHeight: number,
    lightX: number, lightY: number, lightZ: number
)
{
    groundMdlFromLight = drawOneObjectOnShadowfbo(
        gl, shadowProgram, cubeObj,
        groundMdlMatrix,
        offScreenWidth, offScreenHeight,
        lightX, lightY, lightZ
    );
    playerMdlFromLight = drawOneObjectOnShadowfbo(
        gl, shadowProgram, playerObj,
        playerMdlMatrix,
        offScreenWidth, offScreenHeight,
        lightX, lightY, lightZ
    );
    
    bomb2MdlFromLight = drawOneObjectOnShadowfbo(
        gl, shadowProgram, bombObj,
        bombMdlMatrix,
        offScreenWidth, offScreenHeight,
        lightX, lightY, lightZ
    );
    claw_machineMdlFromLight = drawOneObjectOnShadowfbo(
        gl, shadowProgram, claw_machineObj,
        claw_machineMdlMatrix,
        offScreenWidth, offScreenHeight,
        lightX, lightY, lightZ
    );
}

export function draw_all_object(
    gl: WebGL2RenderingContext, program: Program, textures: {[key: string]: WebGLTexture}, shadowfbo: any,
    vpMatrix: Matrix4,
    third_view: boolean,
    thirdcameraX: number, thirdcameraY: number, thirdcameraZ: number,
    firstcameraX: number, firstcameraY: number, firstcameraZ: number,
    lightX: number, lightY: number, lightZ: number
)
{
    let cur_cameraX: number
    let cur_cameraY: number;
    let cur_cameraZ: number;
    if (third_view)
    {
        cur_cameraX = thirdcameraX;
        cur_cameraY = thirdcameraY;
        cur_cameraZ = thirdcameraZ;
    }
    else
    {
        cur_cameraX = firstcameraX;
        cur_cameraY = firstcameraY;
        cur_cameraZ = firstcameraZ;
    }
    
    // draw ground
    drawOneObjectOnScreen(
        gl, program, cubeObj, shadowfbo,
        groundMdlMatrix, vpMatrix, groundMdlFromLight,
        cur_cameraX, cur_cameraY, cur_cameraZ,
        lightX, lightY, lightZ,
        textures["groundTex"]
    );

    // draw light
    drawOneObjectOnScreen(
        gl, program, lightObj, shadowfbo,
        lightMdlMatrix, vpMatrix, groundMdlFromLight,
        cur_cameraX, cur_cameraY, cur_cameraZ,
        lightX, lightY, lightZ,
        textures["lightTex"]
    );

    if (third_view)
    {
        // draw player
        drawOneObjectOnScreen(
            gl, program, playerObj, shadowfbo,
            playerMdlMatrix, vpMatrix, playerMdlFromLight,
            cur_cameraX, cur_cameraY, cur_cameraZ,
            lightX, lightY, lightZ,
            textures["playerTex"]
        );
    }

    // draw claw machine
    drawOneObjectOnScreen(
        gl, program, claw_machineObj, shadowfbo,
        claw_machineMdlMatrix, vpMatrix, claw_machineMdlFromLight,
        cur_cameraX, cur_cameraY, cur_cameraZ,
        lightX, lightY, lightZ,
        textures["clawMachineTex"]
    );

    // draw bomb2
    drawOneObjectOnScreen(
        gl, program, bombObj, shadowfbo,
        bomb2MdlMatrix, vpMatrix, bomb2MdlFromLight,
        cur_cameraX, cur_cameraY, cur_cameraZ,
        lightX, lightY, lightZ,
        textures["bomb2Tex"]
    );

    // draw claw
    drawOneObjectOnScreen(
        gl, program, clawObj, shadowfbo,
        clawMdlMatrix, vpMatrix, groundMdlFromLight,
        cur_cameraX, cur_cameraY, cur_cameraZ,
        lightX, lightY, lightZ,
        textures["clawTex"]
    );

    // draw bear
    drawOneObjectOnScreen(
        gl, program, bearObj, shadowfbo,
        bearMdlMatrix, vpMatrix, groundMdlFromLight,
        cur_cameraX, cur_cameraY, cur_cameraZ,
        lightX, lightY, lightZ,
        textures["bearTex"]
    );

    // draw cat
    drawOneObjectOnScreen(
        gl, program, catObj, shadowfbo,
        catMdlMatrix, vpMatrix, groundMdlFromLight,
        cur_cameraX, cur_cameraY, cur_cameraZ,
        lightX, lightY, lightZ,
        textures["catTex"]
    );

    // draw cool_head
    drawOneObjectOnScreen(
        gl, program, cool_headObj, shadowfbo,
        cool_headMdlMatrix, vpMatrix, groundMdlFromLight,
        cur_cameraX, cur_cameraY, cur_cameraZ,
        lightX, lightY, lightZ,
        textures["coolHeadTex"]
    );
}

export function draw_all_reflection_object(
    gl: WebGL2RenderingContext, programTextureOnCube: ProgramTextureOnCube, reflectfbo: any,
    draw_world: (vMatrix: Matrix4, pMatrix: Matrix4, vpMatrix: Matrix4) => void,
    vpMatrix: Matrix4,
    third_view: boolean,
    offScreenWidth: number, offScreenHeigh: number,
    thirdcameraX: number, thirdcameraY: number, thirdcameraZ: number,
    firstcameraX: number, firstcameraY: number, firstcameraZ: number,
    playerX: number, playerY: number, playerZ: number,
    bomb_mode: boolean
)
{
    let cur_cameraX: number;
    let cur_cameraY: number;
    let cur_cameraZ: number;

    if (third_view)
    {
        cur_cameraX = thirdcameraX;
        cur_cameraY = thirdcameraY;
        cur_cameraZ = thirdcameraZ;
    }
    else
    {
        cur_cameraX = firstcameraX;
        cur_cameraY = firstcameraY;
        cur_cameraZ = firstcameraZ;
    }
    if (bomb_mode)
    {
        drawDynamicReflectionObject(
            gl, programTextureOnCube, reflectfbo, bombObj,
            draw_world,
            bombMdlMatrix, vpMatrix,
            offScreenWidth, offScreenHeigh,
            cur_cameraX, cur_cameraY, cur_cameraZ,
            playerX + 3, playerY + 2.5, playerZ
        );
    }
    else
    {
        drawDynamicReflectionObject(
            gl, programTextureOnCube, reflectfbo, coinObj,
            draw_world,
            coinMdlMatrix, vpMatrix,
            offScreenWidth, offScreenHeigh,
            cur_cameraX, cur_cameraY, cur_cameraZ,
            playerX + 3, playerY + 2.5, playerZ
        );
    }
    
}