import { 
    compileShader
} from "../../lib/utils";


const VSHADER_SOURCE = `
    attribute vec4 a_Position;
    void main(){
        //gl_Position is key variable in GLSL (pass vertex location to fragment shader)
        gl_Position = a_Position;
    }    
`;

const FSHADER_SOURCE = `
    void main(){
        //gl_FragColor is key variable in GLSL (assign color of a pixel)
        gl_FragColor = vec4(0.0/255.0, 28.0/255.0, 245.0/255.0, 1.0);
    }
`;

main();
function main()
{
    ///// Step 1. get the canvas
    const canvas = document.getElementById('webgl') as HTMLCanvasElement | null;

    if (canvas === null)
    {
        throw new Error("Fail");
    }

    ///// Step 2. get the context for draw
    const gl = canvas.getContext('webgl2');
    if(!gl)
    {
        console.log('Failed to get the rendering context for WebGL');
        return ;
    }

    ///// Step 3. compile the shader program (vertex and framgment shader)
    const renderProgram = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);
 
    ///// Step 4. what program you want to use (you may have multiple shader program later)
    gl.useProgram(renderProgram);
    

    // var n = initVertexBuffers(gl, renderProgram);
    ///// 5. prepare the vertices for draw (we just draw 2D object here)
    /////    These are vertices of a triangle in 2D
    const vertices = new Float32Array(
        [-0.5, 0.5, 0.5, 0.5, 0, -0.5]   
    );

    const n = 3; /// number of vertices

    const vertexBuffer = gl.createBuffer(); ///// create a vertex buffer to store the triangle vertices
    if(!vertexBuffer) 
    {
        console.log('Failed to create the buffer object');
    }

    ///// bind buffer and pass the vertices data
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

    ///// get the reference of the variable in the shader program
    const a_Position = gl.getAttribLocation(renderProgram, 'a_Position');
    if( a_Position < 0 )console.log("a_Position < 0"); //check you get the refernce of the variable

    gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0); //setting of the vertex buffer
    gl.enableVertexAttribArray(a_Position); //enable the vetex buffer

    ///// 6. clear the scrren by designated background color
    gl.clearColor(116.0/255.0, 250.0/255.0, 76.0/255.0, 1.0); //background color
    gl.clear(gl.COLOR_BUFFER_BIT); // clear

    ///// 7. draw the shape
    gl.drawArrays(gl.TRIANGLES, 0, n);
    
}