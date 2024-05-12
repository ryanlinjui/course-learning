import {
    compileShader
} from "../../lib/utils";

const VSHADER_SOURCE = `
    attribute vec4 a_Position;
    attribute vec4 a_Color;
    varying vec4 v_Color;
    void main()
    {
        gl_Position = a_Position;
        v_Color = a_Color;
    }    
`;

const FSHADER_SOURCE = `
    precision mediump float;
    varying vec4 v_Color;
    void main()
    {
        gl_FragColor = v_Color;
    }
`;

main();
function main()
{
    const canvas = document.getElementById('webgl') as HTMLCanvasElement | null;
    if(canvas == null) throw new Error("Canvas is null");

    const gl = canvas.getContext('webgl2');
    
    if(!gl)
    {
        console.log('Failed to get the rendering context for WebGL');
        return;
    }

    const renderProgram = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);
 
    gl.useProgram(renderProgram);

    const n = initVertexBuffers(gl, renderProgram);

    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    gl.drawArrays(gl.TRIANGLE_STRIP, 0, n); //you are NOT allowed to change this line
}

function initVertexBuffers(gl:WebGL2RenderingContext, program:WebGLProgram)
{
    const vertices = new Float32Array(
        [   -0.5, 0.5, 1.0, 0.0, 0.0,
            0.5, 0.5, 1.0, 1.0, 1.0,
            -0.5, -0.5, 1.0, 1.0, 1.0,
            0.5, -0.5, 0.0, 0.0, 1.0
        ]
        //TODO-1: vertex and color array
    );
    const FSIZE = vertices.BYTES_PER_ELEMENT;
    
    //TODO-2: how many vertices to draw?
    const n = 4;
    
    //TODO-3: create a vertex buffer
    const vertexBuffer = gl.createBuffer();

    //TODO-4: bind buffer (gl.bindBuffer)
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);

    //TODO-5: bind buffer data (gl.bufferData)
    gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

    //TODO-6: get reference of the attribute variable for vertex position
    const a_Position = gl.getAttribLocation(program, "a_Position");
    
    //TODO-7: layout of current vertex buffer object (gl.vertexAttribPointer)
    gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, FSIZE*5, 0);

    //TODO-8: enable the attribute array
    gl.enableVertexAttribArray(a_Position);
    
    //TODO-9 repeat TODO-6~8 for the attribute variable to store vertex color information
    const a_Color = gl.getAttribLocation(program, "a_Color");
    gl.vertexAttribPointer(a_Color, 3, gl.FLOAT, false, FSIZE*5, FSIZE*2)
    gl.enableVertexAttribArray(a_Color);

    return n;
}