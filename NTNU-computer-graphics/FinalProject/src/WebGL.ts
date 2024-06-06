import {
    initFrameBuffer,
    initFrameBufferForCubemapRendering,
    initAttributeVariable
} from "../../lib/init";
import {
    Matrix4,
    Vector3
} from "../../lib/cuon-matrix";

import {
    Program, init_normal_program,
    ProgramShadow, init_shadow_program,
    ProgramTextureOnCube, init_dynamic_reflection_program,
    ProgramEnvCube, init_cubemap_program
} from "./shader";
import {
    load_all_model,
    set_mdl,
    draw_all_shadow,
    draw_all_object,
    draw_all_reflection_object
} from "./object";

let gl: WebGL2RenderingContext | null;
let canvas: HTMLCanvasElement | null;

let program: Program;
let programShadow: ProgramShadow;
let programEnvCube: ProgramEnvCube;
let programTextureOnCube: ProgramTextureOnCube;

let shadowfbo: WebGLFramebuffer;
let reflectfbo: WebGLFramebuffer;

let textures: {[key: string]: WebGLTexture} = {};

const offScreenWidth = 2048, offScreenHeight = 2048;

let angleX = 0, angleY = 0;

let playerX = 0, playerY = 0, playerZ = 0;
const player_step = 0.3;

const clawX_init = 40, clawY_init = 8, clawZ_init = -1;
let clawX = clawX_init, clawY = clawY_init, clawZ = clawZ_init;
const claw_step = 0.2;
let claw_catch_mode = 0;

let firstcameraX = 0, firstcameraY = 4, firstcameraZ = 0;
let thirdcameraX = -3, thirdcameraY = 4.5, thirdcameraZ = 0;
let cameraDirX = 1, cameraDirY = 0, cameraDirZ = 0;
let lightX = -5, lightY = 15, lightZ = 10;

let third_view = true;

const view_size = 60;

let bomb_mode = false;
let bomb_toggle_count = 0;

const inits: (() => Promise<void>)[] = [];
inits.push(main);
inits.push(load_all_texture);
inits.push(async () => {
    if (canvas == null)
    {
        throw new Error("canvas is null");
    }
    canvas.onclick = function ()
    {
        if (canvas == null)
        {
            throw new Error("canvas is null");
        }
        canvas.requestPointerLock();
    };
    document.addEventListener("pointerlockchange", lockChangeAlert, false);
    document.addEventListener("mozpointerlockchange", lockChangeAlert, false);
});

window.onload = async () => {
    for (const func of inits) {
        await func();
    }
};

async function main()
{
    canvas = document.getElementById("webgl") as HTMLCanvasElement | null;
    if(canvas == null)
    {
        throw new Error("Canvas is null");
    }

    gl = canvas.getContext("webgl2");
    if(gl == null)
    {
        throw new Error("gl is null");
    }

    programTextureOnCube = init_dynamic_reflection_program(gl);
    programEnvCube = init_cubemap_program(gl);
    programShadow = init_shadow_program(gl);
    program = init_normal_program(gl);

    shadowfbo = initFrameBuffer(gl, offScreenWidth, offScreenHeight);
    reflectfbo = initFrameBufferForCubemapRendering(gl, offScreenWidth, offScreenHeight);

    load_all_model(gl);
    load_all_texture();
    
    draw_all();

    const tick = function () {
        draw_all();
        requestAnimationFrame(tick);
    };
    tick();
}

function draw_all()
{

    if (gl == null) 
    {
        throw new Error("gl is null");
    }
    if (canvas == null)
    {
        throw new Error("canvas is null");
    }

    if (claw_catch_mode < 0)
    {
        clawY -= 0.08;
        if (clawY <= 2.5)
        {
            claw_catch_mode = 1;
        }

    } else if (claw_catch_mode > 0)
    {
        clawY += 0.08;
        if (clawY >= clawY_init)
        {
            claw_catch_mode = 0;
        }
    }

    const viewDir = new Vector3([cameraDirX, cameraDirY, cameraDirZ]);
    const rotateMatrix = new Matrix4();
    rotateMatrix.setRotate(angleX, 0, -1, 0); // for mouse rotation
    rotateMatrix.rotate(angleY, 0, 0, -1); // for mouse rotation
    const newViewDir = rotateMatrix.multiplyVector3(viewDir);

    const vMatrix = new Matrix4();
    const pMatrix = new Matrix4();
    pMatrix.setPerspective(view_size, 1, 1, 1000);

    if (third_view)
    {
        vMatrix.lookAt(
            thirdcameraX, thirdcameraY, thirdcameraZ,
            thirdcameraX + newViewDir.elements[0],
            thirdcameraY + newViewDir.elements[1],
            thirdcameraZ + newViewDir.elements[2],
            0, 1, 0
        );
    }
    else
    {
        vMatrix.lookAt(
            firstcameraX, firstcameraY, firstcameraZ,
            firstcameraX + newViewDir.elements[0],
            firstcameraY + newViewDir.elements[1],
            firstcameraZ + newViewDir.elements[2],
            0, 1, 0
        );
    }

    const vpMatrix = new Matrix4();
    vpMatrix.set(pMatrix);
    vpMatrix.multiply(vMatrix);

    set_mdl(
        playerX, playerY, playerZ,
        clawX, clawY, clawZ,
        third_view,
        angleX, angleY
    );

    gl.useProgram(programShadow.program);
    gl.bindFramebuffer(gl.FRAMEBUFFER, shadowfbo);
    gl.viewport(0, 0, offScreenWidth, offScreenHeight);
    draw_shadow();

    gl.useProgram(program.program);
    gl.bindFramebuffer(gl.FRAMEBUFFER, null);
    gl.viewport(0, -275, canvas.width, canvas.width);

    draw_world(vpMatrix, vMatrix, pMatrix);

    gl.useProgram(programTextureOnCube.program);
    draw_all_reflection_object(
        gl, programTextureOnCube, reflectfbo,
        draw_world,
        vpMatrix,
        third_view,
        offScreenWidth, offScreenHeight,
        thirdcameraX, thirdcameraY, thirdcameraZ,
        firstcameraX, firstcameraY, firstcameraZ,
        playerX, playerY, playerZ,
        bomb_mode
    );
}

function draw_shadow()
{
    if (gl == null) 
    {
        throw new Error("gl is null");
    }

    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.enable(gl.DEPTH_TEST);

    draw_all_shadow(
        gl, programShadow,
        offScreenWidth, offScreenHeight,
        lightX, lightY, lightZ
    );
}

function draw_world(vpMatrix: Matrix4, vMatrix: Matrix4, pMatrix: Matrix4)
{
    if (gl == null) 
    {
        throw new Error("gl is null");
    }

    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.enable(gl.DEPTH_TEST);
    draw_cubemap(programEnvCube.cubeMapTex, vMatrix, pMatrix);

    draw_all_object(
        gl, program, textures, shadowfbo,
        vpMatrix,
        third_view,
        thirdcameraX, thirdcameraY, thirdcameraZ,
        firstcameraX, firstcameraY, firstcameraZ,
        lightX, lightY, lightZ
    );
}

function draw_cubemap(
    Tex: WebGLTexture,
    vMatrix: Matrix4, pMatrix: Matrix4
)
{
    if (gl == null) 
    {
        throw new Error("gl is null");
    }
    const vpFromCamera = new Matrix4();
    vpFromCamera.set(pMatrix);
    
    vMatrix.elements[12] = 0; // ignore translation
    vMatrix.elements[13] = 0;
    vMatrix.elements[14] = 0;
    
    vpFromCamera.multiply(vMatrix);
    const vpFromCameraInverse = vpFromCamera.invert();

    // quad
    gl.useProgram(programEnvCube.program);
    gl.depthFunc(gl.LEQUAL);
    gl.uniformMatrix4fv(
        programEnvCube.u_viewDirectionProjectionInverse,
        false,
        vpFromCameraInverse.elements
    );
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_CUBE_MAP, Tex);
    gl.uniform1i(programEnvCube.u_envCubeMap, 0);
    initAttributeVariable(gl, programEnvCube.a_Position, programEnvCube.quadObj.vertexBuffer);
    gl.drawArrays(gl.TRIANGLES, 0, programEnvCube.quadObj.numVertices);
}

async function load_all_texture()
{
    const loadImage = (src: string): Promise<HTMLImageElement> => {
        return new Promise((resolve, reject) => {
            const img = new Image();
            img.onload = () => resolve(img);
            img.onerror = () => reject(new Error(`Failed to load image: ${src}`));
            img.src = src;
        });
    };

    try
    {
        if (gl == null) 
        {
            throw new Error("gl is null");
        }
        const imagePlayer = await loadImage("texture/apple.jpg");
        initTexture(gl, imagePlayer, "playerTex");

        const imageGround = await loadImage("texture/wood.png");
        initTexture(gl, imageGround, "groundTex");

        const imageClawMachine = await loadImage("texture/marbal.jpg");
        initTexture(gl, imageClawMachine, "clawMachineTex");

        const imageLight = await loadImage("texture/apple.jpg");
        initTexture(gl, imageLight, "lightTex");

        const imageBomb2 = await loadImage("texture/marbal.jpg");
        initTexture(gl, imageBomb2, "bomb2Tex");

        const imageClaw = await loadImage("texture/marbal.jpg");
        initTexture(gl, imageClaw, "clawTex");

        const imageBear = await loadImage("texture/doll.jpg");
        initTexture(gl, imageBear, "bearTex");

        const imageCat = await loadImage("texture/doll.jpg");
        initTexture(gl, imageCat, "catTex");

        const imageCoolHead = await loadImage("texture/doll.jpg");
        initTexture(gl, imageCoolHead, "coolHeadTex");
    }
    catch (error)
    {
        console.error("Error loading textures:", error);
    }
}

function initTexture(
    gl: WebGL2RenderingContext,
    img: HTMLImageElement,
    texKey: string
)
{
    if (gl == null) 
    {
        throw new Error("gl is null");
    }

    const tex = gl.createTexture();
    if (tex == null)
    {
        throw new Error("tex is null");
    }
    gl.bindTexture(gl.TEXTURE_2D, tex);
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, img);

    textures[texKey] = tex;
}

let play_start = false;
function lockChangeAlert()
{
    if (play_start == false)
    {
        const audio = new Audio("sound/claw-machine.mp3");
        audio.loop = true;
        audio.play();
        play_start = true;
    }
    const pointerLockElement = (document as any).pointerLockElement || (document as any).mozPointerLockElement;
    
    if (pointerLockElement === canvas)
    {
        control();
        document.addEventListener("mousemove", updatePosition, false);
    }
    else
    {
        document.removeEventListener("mousemove", updatePosition, false);
    }
}

let animation: number | null = null;
function updatePosition(ev: MouseEvent)
{
    angleX += ev.movementX / 3;
    angleY += ev.movementY / 3;

    if (!animation)
    {
        animation = requestAnimationFrame(function () {
            animation = null;
        });
    }
}

const action = {};
const interval = 1000 / 45;
function control()
{
    document.onkeydown = function (ev: KeyboardEvent) {
        if (action[ev.key])
        {
            return;
        }
        if (ev.key == "e" && third_view)
        {
            third_view = !third_view;
            // bomb_mode = false;
            // bomb_toggle_count = 0;
            clawX = clawX_init;
            clawZ = clawZ_init;
        }
        else if (ev.key == "q" && !third_view)
        {
            third_view = !third_view;
        }
        else if (ev.key == "b" && third_view)
        {
            bomb_toggle_count += 1;
            if (bomb_toggle_count >= 10)
            {
                bomb_mode = !bomb_mode;
            }
        }
        else if (ev.key == "c" && !bomb_mode)
        {
            play_sound("sound/coin.mp3");
        }
        else if (ev.key == " " && !third_view) 
        {
            claw_catch_mode = -1;
            play_sound("sound/claw.mp3");
        }

        action[ev.key] = setInterval(() => {
            keydown(ev);
        }, interval);
    };
    document.onkeyup = function (ev: KeyboardEvent) {
        if (!action[ev.key])
        {
            return;
        }

        clearInterval(action[ev.key]);
        action[ev.key] = undefined;
    };

    document.onmousedown = function (ev) {
        mousedown(ev);
    };
}


function mousedown(ev: MouseEvent)
{
    if (bomb_mode)
    {
        play_sound("sound/explosion.mp3");
    }
}

function keydown(ev: KeyboardEvent)
{
    // implment keydown event here
    const rotateMatrix = new Matrix4();
    rotateMatrix.setRotate(angleY, 0, 0, -1); // for mouse rotation
    rotateMatrix.rotate(angleX, 0, -1, 0); // for mouse rotation
    const orthrotateMatrix = new Matrix4();
    orthrotateMatrix.setRotate(angleY, 0, 0, -1); // for mouse rotation
    orthrotateMatrix.rotate(angleX - 90, 0, -1, 0); // for mouse rotation

    const viewDir = new Vector3([cameraDirX, cameraDirY, cameraDirZ]);
    const newViewDir = rotateMatrix.multiplyVector3(viewDir);
    const orthnewViewDir = orthrotateMatrix.multiplyVector3(viewDir);

    let vdx = 0, vdz = 0;
    if (ev.key == "w")
    {
        vdx = newViewDir.elements[0];
        vdz = newViewDir.elements[2];
    }
    else if (ev.key == "s")
    {
        vdx = newViewDir.elements[0] * -1;
        vdz = newViewDir.elements[2] * -1;
    }
    else if (ev.key == "a")
    {
        vdx = orthnewViewDir.elements[0];
        vdz = orthnewViewDir.elements[2];
    }
    else if (ev.key == "d")
    {
        vdx = orthnewViewDir.elements[0] * -1;
        vdz = orthnewViewDir.elements[2] * -1;
    }
    else if (ev.key == "ArrowUp")
    {
        clawX += claw_step;
        if (clawX > 48)
        {
            clawX = 48;
        }
    }
    else if (ev.key == "ArrowDown")
    {
        clawX -= claw_step;
        if (clawX < 37)
        {
            clawX = 37;
        }
    }
    else if (ev.key == "ArrowRight")
    {
        clawZ += claw_step;
        if (clawZ > 7.4)
        {
            clawZ = 7.4;
        }
    }
    else if (ev.key == "ArrowLeft")
    {
        clawZ -= claw_step;
        if (clawZ < -5)
        {
            clawZ = -5;
        }
    }

    vdx *= player_step;
    vdz *= player_step;
    playerX += vdx;
    playerZ += vdz;
    firstcameraX += vdx;
    firstcameraZ += vdz;
    thirdcameraX += vdx;
    thirdcameraZ += vdz;
    if (playerX < -10 || 20 < playerX || playerZ < -15 || 15 < playerZ)
    {
        playerX -= vdx;
        playerZ -= vdz;
        firstcameraX -= vdx;
        firstcameraZ -= vdz;
        thirdcameraX -= vdx;
        thirdcameraZ -= vdz;
    }
}

function play_sound(sound_file: string)
{
    const pointerLockElement = (document as any).pointerLockElement || (document as any).mozPointerLockElement;
    
    if (pointerLockElement === canvas)
    {
        const sound = new Audio(sound_file);
        sound.play();
    }
}