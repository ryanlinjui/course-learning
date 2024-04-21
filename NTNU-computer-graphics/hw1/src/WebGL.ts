import {
    compileShader
} from "../../utils"

const VSHADER_SOURCE = `
        attribute vec4 a_Position;
        void main()
        {
            gl_Position = a_Position;
            gl_PointSize = 5.0;
        }    
    `;

const FSHADER_SOURCE = `
        precision mediump float;
        uniform vec4 u_FragColor;
        void main()
        {
            gl_FragColor = u_FragColor;
        }
    `;

let shape = 'p'; // default shape is point
let color = 'r'; // default color is red

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

    const renderProgram = compileShader(gl, VSHADER_SOURCE, FSHADER_SOURCE);
 
    gl.useProgram(renderProgram);

    const a_Position = gl.getAttribLocation(renderProgram, "a_Position");
    const u_FragColor = gl.getUniformLocation(renderProgram, "u_FragColor");

    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    if (a_Position == null || u_FragColor == null)
    {
        throw new Error("a_Position or u_FragColor is null");
    }

    //mouse event
    canvas.onmousedown = function (ev: MouseEvent){click(ev, gl, a_Position, u_FragColor)}
    
    document.addEventListener("keydown", (event)=> {    
        if ( event.key == 'p' || event.key == 'P') // P/p for point
        {
            console.log('P');
            shape = 'p';
        }
        else if( event.key == 'q' || event.key == 'Q') // Q/q for square
        { 
            console.log('Q');
            shape = 'q';
        }
        else if ( event.key == 'c' || event.key == 'C') // C/c for circle
        {
            console.log('C');
            shape = 'c';
        }
        else if ( event.key == 't' || event.key == 'T') // T/t for triangle
        {
            console.log('T');
            shape = 't';
        }
        else if ( event.key == 'g' || event.key == 'G') // G/g for green
        {
            console.log('G');
            color = 'g';
        }
        else if ( event.key == 'r' || event.key == 'R') // R/r for red
        {
            console.log('R');
            color = 'r';
        }
        else if ( event.key == 'b' || event.key == 'B') // B/b for blue
        {
            console.log('B');
            color = 'b';
        }
    });
}

let g: { 
    [shape: string]: {
        points: [number, number][],
        colors: [number, number, number, number][],
        size: number,
        split_len: number
    }
} = {
    'p': {
        points: [],
        colors: [],
        size: 0,
        split_len: 1
    },
    'q': {
        points: [],
        colors: [],
        size: 0.1,
        split_len: 4
    },
    'c': {
        points: [],
        colors: [],
        size: 0.05,
        split_len: 360
    },
    't': {
        points: [],
        colors: [],
        size: 0.1,
        split_len: 3
    }
};

const SHAPE_NUM = 3;

function click(
    ev:MouseEvent, 
    gl:WebGLRenderingContext,
    a_Position:number,
    u_FragColor:WebGLUniformLocation)
{
    let x = ev.clientX;
    let y = ev.clientY;

    if (!(ev.target instanceof HTMLCanvasElement)) throw new Error("ev.target is null");

    const rect = ev.target.getBoundingClientRect();
    x = ((x-rect.left) / 200) - 1 - (g[shape].size/2);
    y = -(((y-rect.top) / 200) - 1 - (g[shape].size/2));
    
    // set the points
    if( shape == 'p')
    {
        g[shape].points.push([
            x - 0.001,
            y + 0.002
        ]);
    }
    else if (shape == 'q')
    {
        g[shape].points.push([x, y]);
        g[shape].points.push([x+g[shape].size, y]);
        g[shape].points.push([x+g[shape].size, y-g[shape].size]);
        g[shape].points.push([x, y-g[shape].size]);
    }
    else if (shape == 'c')
    {
        for (let i = 0; i < 360; i++)
        {
            g[shape].points.push([
                x + g[shape].size * Math.cos(i * Math.PI / 180) + 0.02, 
                y + g[shape].size * Math.sin(i * Math.PI / 180) - 0.01
            ]);
        }
    }
    else if (shape == 't')
    {
        g[shape].points.push([x, y-g[shape].size]);
        g[shape].points.push([x+g[shape].size, y-g[shape].size]);
        g[shape].points.push([x+(g[shape].size/2) , y]);
    }
    
    if (g[shape].points.length > g[shape].split_len * SHAPE_NUM)
    {
        for (let i = 0; i < g[shape].split_len; i++)
        {
            g[shape].points.shift();
        }
    }

    // set the colors
    for (let i = 0; i < g[shape].split_len; i++)
    {
        if(color == 'r')
        {
            g[shape].colors.push([1.0, 0.0, 0.0, 1.0]) //red
        }
        else if(color == 'g')
        {
            g[shape].colors.push([0.0, 1.0, 0.0, 1.0]) //green
        }
        else if(color == 'b')
        {
            g[shape].colors.push([0.0, 0.0, 1.0, 1.0]) //blue
        }
        if (g[shape].colors.length > g[shape].split_len * SHAPE_NUM)
        {
            for(let j = 0; j < g[shape].split_len; j++)
            {
                g[shape].colors.shift();
            }
        }
    }

    // // Clear canvas by background color before drawing
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    for(let key in g)
    {
        console.log("key: " + key);
        const len = g[key].points.length / g[key].split_len;
        console.log("len: " + len);
        for(let i = 0; i < len; i++)
        {   
            const vertexBuffer = gl.createBuffer(); // create a vertex buffer to store the point vertices
            
            if(!vertexBuffer) 
            {
                console.log('Failed to create the buffer object');
            }

            if (key== 'p') // draw point
            {
                gl.uniform4f(u_FragColor, g[key].colors[i][0], g[key].colors[i][1], g[key].colors[i][2], g[key].colors[i][3]);

                ///// bind buffer and pass the vertices data
                gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
                const vertices = new Float32Array([
                    g[key].points[i][0], g[key].points[i][1]
                ]);
                
                gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
                
                ///// get the reference of the variable in the shader program
                gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0); //setting of the vertex buffer
                gl.enableVertexAttribArray(a_Position); //enable the vetex buffer
                gl.drawArrays(gl.POINTS, 0, 1);
            }
            else if (key == 'q') // draw square
            {
                for (let j = 0; j < g[key].split_len; j++)
                {
                    gl.uniform4f(u_FragColor, g[key].colors[i*4+j][0], g[key].colors[i*4+j][1], g[key].colors[i*4+j][2], g[key].colors[i*4+j][3]);
                }
                gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
                const vertices = new Float32Array([
                    g[key].points[i*4][0], g[key].points[i*4][1], 
                    g[key].points[i*4+1][0], g[key].points[i*4+1][1],
                    g[key].points[i*4+2][0], g[key].points[i*4+2][1],
                    g[key].points[i*4+3][0], g[key].points[i*4+3][1]
                ]);
                gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
                gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0); 
                gl.enableVertexAttribArray(a_Position); 
                gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
            }
            else if (key == 'c') // draw circle
            {
                for (let j = 0; j < g[key].split_len; j++)
                {
                    gl.uniform4f(u_FragColor, g[key].colors[i*360+j][0], g[key].colors[i*360+j][1], g[key].colors[i*360+j][2], g[key].colors[i*360+j][3]);
                }
                gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
                const vertices = new Float32Array(g[key].points.slice(i*360, (i+1)*360).flat());
                gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
                gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
                gl.enableVertexAttribArray(a_Position);
                gl.drawArrays(gl.TRIANGLE_FAN, 0, 360);
            }
            else if (key == 't') // draw triangle
            {
                for (let j = 0; j < g[key].split_len; j++)
                {
                    gl.uniform4f(u_FragColor, g[key].colors[i*3+j][0], g[key].colors[i*3+j][1], g[key].colors[i*3+j][2], g[key].colors[i*3+j][3]);
                }
                gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
                const vertices = new Float32Array([
                    g[key].points[i*3][0], g[key].points[i*3][1], 
                    g[key].points[i*3+1][0], g[key].points[i*3+1][1],
                    g[key].points[i*3+2][0], g[key].points[i*3+2][1]
                ]);
                gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
                gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
                gl.enableVertexAttribArray(a_Position);
                gl.drawArrays(gl.TRIANGLES, 0, 3);
            }
        }
    }
}