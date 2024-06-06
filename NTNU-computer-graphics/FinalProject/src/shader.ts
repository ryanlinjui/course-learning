import {
    compileShader
} from "../../lib/utils";
import {
    initVertexBufferForLaterUse3D,
    initCubeTexture,
} from "../../lib/init";

const VSHADER_SOURCE = `
    attribute vec4 a_Position;
    attribute vec4 a_Normal;
    uniform mat4 u_MvpMatrix;
    uniform mat4 u_modelMatrix;
    uniform mat4 u_normalMatrix;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;

    attribute vec2 a_TexCoord;
    varying vec2 v_TexCoord;

    uniform mat4 u_MvpMatrixOfLight;
    varying vec4 v_PositionFromLight;

    void main(){
        gl_Position = u_MvpMatrix * a_Position;
        v_PositionInWorld = (u_modelMatrix * a_Position).xyz; 
        v_Normal = normalize(vec3(u_normalMatrix * a_Normal));
        v_TexCoord = a_TexCoord;
        v_PositionFromLight = u_MvpMatrixOfLight * a_Position;
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

    varying vec2 v_TexCoord;
    uniform sampler2D u_Sampler;

    uniform sampler2D u_ShadowMap;
    varying vec4 v_PositionFromLight;
    const float deMachThreshold = 0.001;

    float unpack(const in vec4 rgbaDepth)
    {
        const vec4 bitShift = vec4(1.0, 1.0/256.0, 1.0/(256.0*256.0), 1.0/(256.0*256.0*256.0));
        return dot(rgbaDepth, bitShift);
    }

    void main()
    {
        vec3 texColor = texture2D( u_Sampler, v_TexCoord ).rgb;
        if(texColor == vec3(0.0, 0.0, 0.0)) {
            texColor = u_Color;
        }
        
        vec3 ambientLightColor = texColor;
        vec3 diffuseLightColor = texColor;
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

        // vec3 shadowCoord = (v_PositionFromLight.xyz/v_PositionFromLight.w)/2.0 + 0.5;
        // vec4 rgbaDepth = texture2D(u_ShadowMap, shadowCoord.xy);
        
        // float depth = unpack(rgbaDepth);
        // float visibility = 1.0;
        // if(depth != 1.0 && shadowCoord.z > depth + deMachThreshold) {
        //     visibility = 0.3;
        // }
        
        // gl_FragColor = vec4( (ambient + diffuse + specular)*visibility, 1.0);



        vec3 shadowCoord = (v_PositionFromLight.xyz/v_PositionFromLight.w)/2.0 + 0.5;
        float shadows = 0.0;
        float opacity = 0.6;
        float texelSize = 1.0/2048.0;
        vec4 rgbaDepth;
        for(float y = -3.0; y <= 3.0; y += 1.0)
        {
            for(float x = -3.0; x <= 3.0; x += 1.0)
            {
                rgbaDepth = texture2D(u_ShadowMap, shadowCoord.xy + vec2(x,y) * texelSize);
                shadows += ( ( (shadowCoord.z - deMachThreshold) > unpack(rgbaDepth) ) ? 1.0 : 0.1 );
            }
        }
        shadows /= 36.0;
        float visibility = min(opacity + (1.0 - shadows), 1.0);
        specular = visibility < 1.0 ? vec3(0.0, 0.0, 0.0): specular;
        gl_FragColor = vec4( (ambient + diffuse + specular) * visibility, texture2D( u_Sampler, v_TexCoord ).a);
    }
`;

const VSHADER_SOURCE_ENVCUBE = `
    attribute vec4 a_Position;
    varying vec4 v_Position;
    void main()
    {
        v_Position = a_Position;
        gl_Position = a_Position;
    } 
`;

const FSHADER_SOURCE_ENVCUBE = `
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

const VSHADER_SHADOW_SOURCE = `
    attribute vec4 a_Position;
    uniform mat4 u_MvpMatrix;
    void main()
    {
        gl_Position = u_MvpMatrix * a_Position;
    }
`;

const FSHADER_SHADOW_SOURCE = `
    precision mediump float;
    vec4 pack (float depth)
    {
        const vec4 bitShift = vec4(1.0, 256.0, 256.0 * 256.0, 256.0 * 256.0 * 256.0);
        const vec4 bitMask = vec4(1.0/256.0, 1.0/256.0, 1.0/256.0, 0.0);
        vec4 rgbaDepth = fract(depth * bitShift);
        rgbaDepth -= rgbaDepth.gbaa * bitMask;
        return rgbaDepth;
    }
    void main()
    {
        /////////** LOW precision depth implementation **/////
        gl_FragColor = pack(gl_FragCoord.z);
    }
`;

const VSHADER_SOURCE_TEXTURE_ON_CUBE = `
    attribute vec4 a_Position;
    attribute vec4 a_Normal;
    uniform mat4 u_MvpMatrix;
    uniform mat4 u_modelMatrix;
    uniform mat4 u_normalMatrix;
    varying vec4 v_TexCoord;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    void main() {
        gl_Position = u_MvpMatrix * a_Position;
        v_TexCoord = a_Position;
        v_PositionInWorld = (u_modelMatrix * a_Position).xyz; 
        v_Normal = normalize(vec3(u_normalMatrix * a_Normal));
    } 
`;

const FSHADER_SOURCE_TEXTURE_ON_CUBE = `
    precision mediump float;
    varying vec4 v_TexCoord;
    uniform vec3 u_ViewPosition;
    uniform vec3 u_Color;
    uniform samplerCube u_envCubeMap;
    varying vec3 v_Normal;
    varying vec3 v_PositionInWorld;
    void main() {
        vec3 V = normalize(u_ViewPosition - v_PositionInWorld); 
        vec3 normal = normalize(v_Normal);
        vec3 R = reflect(-V, normal);
        gl_FragColor = vec4(0.78 * textureCube(u_envCubeMap, R).rgb + 0.3 * u_Color, 1.0);
    }
`;

/*
==============================
    ProgramTextureOnCube
==============================
*/
export interface ProgramTextureOnCube
{
    program: WebGLProgram;
    a_Position: number;
    a_Normal: number;
    u_MvpMatrix: WebGLUniformLocation;
    u_modelMatrix: WebGLUniformLocation;
    u_normalMatrix: WebGLUniformLocation;
    u_ViewPosition: WebGLUniformLocation;
    u_envCubeMap: WebGLUniformLocation;
    u_Color: WebGLUniformLocation;
}
export function init_dynamic_reflection_program(gl: WebGL2RenderingContext): ProgramTextureOnCube
{
    const program = compileShader(gl, VSHADER_SOURCE_TEXTURE_ON_CUBE, FSHADER_SOURCE_TEXTURE_ON_CUBE);
    
    const a_Position = gl.getAttribLocation(program, "a_Position");
    if (a_Position === -1) throw new Error("Failed to get the storage location of a_Position");
    
    const a_Normal = gl.getAttribLocation(program, "a_Normal");
    if (a_Normal === -1) throw new Error("Failed to get the storage location of a_Normal");
    
    const u_MvpMatrix = gl.getUniformLocation(program, "u_MvpMatrix");
    if (u_MvpMatrix === null) throw new Error("Failed to get the storage location of u_MvpMatrix");
    
    const u_modelMatrix = gl.getUniformLocation(program, "u_modelMatrix");
    if (u_modelMatrix === null) throw new Error("Failed to get the storage location of u_modelMatrix");
    
    const u_normalMatrix = gl.getUniformLocation(program, "u_normalMatrix");
    if (u_normalMatrix === null) throw new Error("Failed to get the storage location of u_normalMatrix");
    
    const u_ViewPosition = gl.getUniformLocation(program, "u_ViewPosition");
    if (u_ViewPosition === null) throw new Error("Failed to get the storage location of u_ViewPosition");
    
    const u_envCubeMap = gl.getUniformLocation(program, "u_envCubeMap");
    if (u_envCubeMap === null) throw new Error("Failed to get the storage location of u_envCubeMap");
    
    const u_Color = gl.getUniformLocation(program, "u_Color");
    if (u_Color === null) throw new Error("Failed to get the storage location of u_Color");

    const programTextureOnCube: ProgramTextureOnCube = {
        program: program,
        a_Position: a_Position,
        a_Normal: a_Normal,
        u_MvpMatrix: u_MvpMatrix,
        u_modelMatrix: u_modelMatrix,
        u_normalMatrix: u_normalMatrix,
        u_ViewPosition: u_ViewPosition,
        u_envCubeMap: u_envCubeMap,
        u_Color: u_Color,
    };

    return programTextureOnCube;
}

/*
==============================
    ProgramEnvCube
==============================
*/
export interface ProgramEnvCube
{
    program: WebGLProgram;
    a_Position: number;
    u_envCubeMap: WebGLUniformLocation;
    u_viewDirectionProjectionInverse: WebGLUniformLocation;
    quadObj: any;
    cubeMapTex: WebGLTexture;
}
export function init_cubemap_program(gl: WebGL2RenderingContext): ProgramEnvCube
{
    const quad: number[] = [
        -1, -1, 1,
        1, -1, 1,
        -1, 1, 1,
        -1, 1, 1,
        1, -1, 1,
        1, 1, 1,
    ];

    const program = compileShader(gl, VSHADER_SOURCE_ENVCUBE, FSHADER_SOURCE_ENVCUBE);

    const a_Position = gl.getAttribLocation(program, "a_Position");
    if (a_Position === -1) throw new Error("Failed to get the storage location of a_Position");

    const u_envCubeMap = gl.getUniformLocation(program, "u_envCubeMap");
    if (u_envCubeMap === null) throw new Error("Failed to get the storage location of u_envCubeMap");

    const u_viewDirectionProjectionInverse = gl.getUniformLocation(program, "u_viewDirectionProjectionInverse");
    if (u_viewDirectionProjectionInverse === null) throw new Error("Failed to get the storage location of u_viewDirectionProjectionInverse");

    const quadObj = initVertexBufferForLaterUse3D(gl, quad, null, null);

    if (quadObj === null) throw new Error("Failed to initialize vertex buffer for quad");

    const cubeMapTex = initCubeTexture(
        gl,
        "texture/out.jpg",
        "texture/coin.jpg",
        "texture/wood.png",
        "texture/wood.png",
        "texture/claw-machine.jpg",
        "texture/claw-machine.jpg",
        512,
        512
    );
    if (cubeMapTex === null) throw new Error("Failed to initialize cube texture");

    const programEnvCube: ProgramEnvCube = {
        program: program,
        a_Position: a_Position,
        u_envCubeMap: u_envCubeMap,
        u_viewDirectionProjectionInverse: u_viewDirectionProjectionInverse,
        quadObj: quadObj,
        cubeMapTex: cubeMapTex,
    };

    return programEnvCube;
}

/*
==============================
    ProgramShadow
==============================
*/
export interface ProgramShadow 
{
    program: WebGLProgram;
    a_Position: number;
    u_MvpMatrix: WebGLUniformLocation;
}

export function init_shadow_program(gl: WebGL2RenderingContext): ProgramShadow
{
    const program = compileShader(gl, VSHADER_SHADOW_SOURCE, FSHADER_SHADOW_SOURCE);
    
    const a_Position = gl.getAttribLocation(program, "a_Position");
    if (a_Position === -1) throw new Error("Failed to get the storage location of a_Position");

    const u_MvpMatrix = gl.getUniformLocation(program, "u_MvpMatrix");
    if (u_MvpMatrix === null) throw new Error("Failed to get the storage location of u_MvpMatrix");

    const programShadow: ProgramShadow = {
        program: program,
        a_Position: a_Position,
        u_MvpMatrix: u_MvpMatrix,
    };
    return programShadow;
}

/*
==============================
    Program
==============================
*/
export interface Program
{
    program: WebGLProgram;
    a_Position: number;
    a_Normal: number;
    u_MvpMatrix: WebGLUniformLocation;
    u_modelMatrix: WebGLUniformLocation;
    u_normalMatrix: WebGLUniformLocation;
    u_LightPosition: WebGLUniformLocation;
    u_ViewPosition: WebGLUniformLocation;
    u_Ka: WebGLUniformLocation;
    u_Kd: WebGLUniformLocation;
    u_Ks: WebGLUniformLocation;
    u_shininess: WebGLUniformLocation;
    u_Color: WebGLUniformLocation;
    u_ShadowMap: WebGLUniformLocation;
    u_MvpMatrixOfLight: WebGLUniformLocation;
    a_TexCoord: number;
}
export function init_normal_program(gl: WebGL2RenderingContext): Program
{
    const program = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);

    const a_Position = gl.getAttribLocation(program, "a_Position");
    if (a_Position === -1) throw new Error("Failed to get the storage location of a_Position");

    const a_Normal = gl.getAttribLocation(program, "a_Normal");
    if (a_Normal === -1) throw new Error("Failed to get the storage location of a_Normal");

    const u_MvpMatrix = gl.getUniformLocation(program, "u_MvpMatrix");
    if (u_MvpMatrix === null) throw new Error("Failed to get the storage location of u_MvpMatrix");

    const u_modelMatrix = gl.getUniformLocation(program, "u_modelMatrix");
    if (u_modelMatrix === null) throw new Error("Failed to get the storage location of u_modelMatrix");

    const u_normalMatrix = gl.getUniformLocation(program, "u_normalMatrix");
    if (u_normalMatrix === null) throw new Error("Failed to get the storage location of u_normalMatrix");

    const u_LightPosition = gl.getUniformLocation(program, "u_LightPosition");
    if (u_LightPosition === null) throw new Error("Failed to get the storage location of u_LightPosition");

    const u_ViewPosition = gl.getUniformLocation(program, "u_ViewPosition");
    if (u_ViewPosition === null) throw new Error("Failed to get the storage location of u_ViewPosition");

    const u_Ka = gl.getUniformLocation(program, "u_Ka");
    if (u_Ka === null) throw new Error("Failed to get the storage location of u_Ka");

    const u_Kd = gl.getUniformLocation(program, "u_Kd");
    if (u_Kd === null) throw new Error("Failed to get the storage location of u_Kd");

    const u_Ks = gl.getUniformLocation(program, "u_Ks");
    if (u_Ks === null) throw new Error("Failed to get the storage location of u_Ks");

    const u_shininess = gl.getUniformLocation(program, "u_shininess");
    if (u_shininess === null) throw new Error("Failed to get the storage location of u_shininess");

    const u_Color = gl.getUniformLocation(program, "u_Color");
    if (u_Color === null) throw new Error("Failed to get the storage location of u_Color");

    const u_ShadowMap = gl.getUniformLocation(program, "u_ShadowMap");
    if (u_ShadowMap === null) throw new Error("Failed to get the storage location of u_ShadowMap");

    const u_MvpMatrixOfLight = gl.getUniformLocation(program, "u_MvpMatrixOfLight");
    if (u_MvpMatrixOfLight === null) throw new Error("Failed to get the storage location of u_MvpMatrixOfLight");

    const a_TexCoord = gl.getAttribLocation(program, "a_TexCoord");
    if (a_TexCoord === -1) throw new Error("Failed to get the storage location of a_TexCoord");

    const programObj: Program = {
        program: program,
        a_Position: a_Position,
        a_Normal: a_Normal,
        u_MvpMatrix: u_MvpMatrix,
        u_modelMatrix: u_modelMatrix,
        u_normalMatrix: u_normalMatrix,
        u_LightPosition: u_LightPosition,
        u_ViewPosition: u_ViewPosition,
        u_Ka: u_Ka,
        u_Kd: u_Kd,
        u_Ks: u_Ks,
        u_shininess: u_shininess,
        u_Color: u_Color,
        u_ShadowMap: u_ShadowMap,
        u_MvpMatrixOfLight: u_MvpMatrixOfLight,
        a_TexCoord: a_TexCoord,
    };

    return programObj;
}