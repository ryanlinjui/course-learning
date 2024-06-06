import {
    initAttributeVariable
} from "../../lib/init";
import {
    Matrix4
} from "../../lib/cuon-matrix";

import {
    Program,
    ProgramShadow,
    ProgramTextureOnCube
} from "./shader";

export function drawOneObjectOnShadowfbo(
    gl: WebGL2RenderingContext, shadowProgram: ProgramShadow, obj: any[],
    mdlMatrix: Matrix4,
    offScreenWidth: number, offScreenHeight: number,
    lightX: number, lightY: number, lightZ: number
)
{
    const mvpFromLight = new Matrix4();

    // model Matrix (part of the mvp matrix)
    // mvp: projection * view * model matrix
    mvpFromLight.setPerspective(150, offScreenWidth / offScreenHeight, 1, 1000);
    mvpFromLight.lookAt(lightX, lightY, lightZ, 5, 0, 0, 0, 1, 0);
    mvpFromLight.multiply(mdlMatrix);

    gl.useProgram(shadowProgram.program);
    gl.uniformMatrix4fv(
        shadowProgram.u_MvpMatrix,
        false,
        mvpFromLight.elements
    );

    for (let i = 0; i < obj.length; i++)
    {
        initAttributeVariable(
            gl,
            shadowProgram.a_Position,
            obj[i].vertexBuffer
        );
        gl.drawArrays(gl.TRIANGLES, 0, obj[i].numVertices);
    }

    return mvpFromLight;
}

export function drawOneObjectOnScreen(
    gl: WebGL2RenderingContext, program: Program, obj: any[], shadowfbo: any,
    modleMatrix: Matrix4, vpMatrix: Matrix4, mvpFromLight: Matrix4,
    cameraX: number, cameraY: number, cameraZ: number,
    lightX: number, lightY: number, lightZ: number,
    texture: WebGLTexture
){
    gl.useProgram(program.program);
    const mvpMatrix = new Matrix4();
    const normalMatrix = new Matrix4();

    mvpMatrix.set(vpMatrix);
    mvpMatrix.multiply(modleMatrix);

    // normal matrix
    normalMatrix.setInverseOf(modleMatrix);
    normalMatrix.transpose();

    gl.uniform3f(program.u_LightPosition, lightX, lightY, lightZ);
    gl.uniform3f(program.u_ViewPosition, cameraX, cameraY, cameraZ);
    gl.uniform1f(program.u_Ka, 0.4);
    gl.uniform1f(program.u_Kd, 0.7);
    gl.uniform1f(program.u_Ks, 0.5);
    gl.uniform1f(program.u_shininess, 30.0);
    gl.uniform3f(program.u_Color, 0.0, 0.0, 0.0);

    gl.uniformMatrix4fv(program.u_MvpMatrix, false, mvpMatrix.elements);
    gl.uniformMatrix4fv(program.u_modelMatrix, false, modleMatrix.elements);
    gl.uniformMatrix4fv(program.u_normalMatrix, false, normalMatrix.elements);
    gl.uniformMatrix4fv(
        program.u_MvpMatrixOfLight,
        false,
        mvpFromLight.elements
    );

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, texture);
    // WEIRD
    // gl.uniform1i(program.u_Sampler, 0);

    gl.activeTexture(gl.TEXTURE1);
    // WEIRD
    gl.bindTexture(gl.TEXTURE_2D, shadowfbo.texture);
    gl.uniform1i(program.u_ShadowMap, 1);

    for (let i = 0; i < obj.length; i++)
    {
        initAttributeVariable(gl, program.a_Position, obj[i].vertexBuffer);
        initAttributeVariable(gl, program.a_TexCoord, obj[i].texCoordBuffer);
        initAttributeVariable(gl, program.a_Normal, obj[i].normalBuffer);
        gl.drawArrays(gl.TRIANGLES, 0, obj[i].numVertices);
    }
}

export function drawDynamicReflectionObject(
    gl: WebGL2RenderingContext, programTextureOnCube: ProgramTextureOnCube, reflectfbo: any, obj: any[],
    draw_world: (vMatrix: Matrix4, pMatrix: Matrix4, vpMatrix: Matrix4) => void,
    modelMatrix: Matrix4, vpMatrix: Matrix4,
    offScreenWidth: number, offScreenHeight: number,
    cameraX: number, cameraY: number, cameraZ: number,
    posX: number, posY: number, posZ: number
)
{
    // camera 6 direction to render 6 cubemap faces
    const ENV_CUBE_LOOK_DIR = [
        [1.0, 0.0, 0.0],
        [-1.0, 0.0, 0.0],
        [0.0, 1.0, 0.0],
        [0.0, -1.0, 0.0],
        [0.0, 0.0, 1.0],
        [0.0, 0.0, -1.0],
    ];

    // camera 6 look up vector to render 6 cubemap faces
    const ENV_CUBE_LOOK_UP = [
        [0.0, -1.0, 0.0],
        [0.0, -1.0, 0.0],
        [0.0, 0.0, 1.0],
        [0.0, 0.0, -1.0],
        [0.0, -1.0, 0.0],
        [0.0, -1.0, 0.0],
    ];

    gl.activeTexture(gl.TEXTURE2);
    gl.bindFramebuffer(gl.FRAMEBUFFER, reflectfbo);
    gl.viewport(0, 0, offScreenWidth, offScreenHeight);
    gl.clearColor(1.0, 0.0, 0.0, 1);

    for (let side = 0; side < 6; side++)
    {
        // WEIRD
        gl.framebufferTexture2D(
            gl.FRAMEBUFFER,
            gl.COLOR_ATTACHMENT0,
            gl.TEXTURE_CUBE_MAP_POSITIVE_X + side,
            reflectfbo.texture,
            0
        );
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

        const vMatrix = new Matrix4();
        const pMatrix = new Matrix4();
        pMatrix.setPerspective(90, 1, 1, 100);
        vMatrix.lookAt(
            posX, posY, posZ,
            posX + ENV_CUBE_LOOK_DIR[side][0],
            posY + ENV_CUBE_LOOK_DIR[side][1],
            posZ + ENV_CUBE_LOOK_DIR[side][2],
            ENV_CUBE_LOOK_UP[side][0],
            ENV_CUBE_LOOK_UP[side][1],
            ENV_CUBE_LOOK_UP[side][2]
        );
        const vpMatrix = new Matrix4();
        vpMatrix.set(pMatrix);
        vpMatrix.multiply(vMatrix);

        draw_world(vpMatrix, vMatrix, pMatrix);
    }


    gl.bindFramebuffer(gl.FRAMEBUFFER, null);
    gl.useProgram(programTextureOnCube.program);
    
    const mvpMatrix = new Matrix4();
    const normalMatrix = new Matrix4();
    mvpMatrix.set(vpMatrix);
    mvpMatrix.multiply(modelMatrix);

    // normal matrix
    normalMatrix.setInverseOf(modelMatrix);
    normalMatrix.transpose();

    gl.uniform3f(
        programTextureOnCube.u_ViewPosition,
        cameraX,
        cameraY,
        cameraZ
    );
    gl.uniform3f(programTextureOnCube.u_Color, 0.1, 0.1, 0.1);

    gl.uniformMatrix4fv(
        programTextureOnCube.u_MvpMatrix,
        false,
        mvpMatrix.elements
    );
    gl.uniformMatrix4fv(
        programTextureOnCube.u_modelMatrix,
        false,
        modelMatrix.elements
    );
    gl.uniformMatrix4fv(
        programTextureOnCube.u_normalMatrix,
        false,
        normalMatrix.elements
    );

    gl.activeTexture(gl.TEXTURE2);
    // WEIRD
    gl.bindTexture(gl.TEXTURE_CUBE_MAP, reflectfbo.texture);
    gl.uniform1i(programTextureOnCube.u_envCubeMap, 2);

    for (let i = 0; i < obj.length; i++)
    {
        initAttributeVariable(
            gl,
            programTextureOnCube.a_Position,
            obj[i].vertexBuffer
        );
        initAttributeVariable(
            gl,
            programTextureOnCube.a_Normal,
            obj[i].normalBuffer
        );
        gl.drawArrays(gl.TRIANGLES, 0, obj[i].numVertices);
    }
}