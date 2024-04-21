import {
    compileShader
} from "../../utils"

const VSHADER_SOURCE = `
        uniform vec4 u_Position;
        void main()
        {
            gl_Position = u_Position;
            gl_PointSize = 10.0;
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

    const u_Position = gl.getUniformLocation(renderProgram, 'u_Position');
    const u_FragColor = gl.getUniformLocation(renderProgram, 'u_FragColor');

    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    if (u_Position == null || u_FragColor == null)
    {
        throw new Error("u_Position or u_FragColor is null");
    }

    //mouse event
    canvas.onmousedown = function (ev: MouseEvent){click(ev, gl, canvas, u_Position, u_FragColor)}
}

let g_points:[number, number][] = []; // store all clicked positions
let g_colors:[number, number, number, number][] = []; // store colors of each points

function click(
    ev:MouseEvent, 
    gl:WebGLRenderingContext,
    canvas:HTMLCanvasElement,
    u_Position:WebGLUniformLocation,
    u_FragColor:WebGLUniformLocation)
{
    let x = ev.clientX;
    let y = ev.clientY;

    if (!(ev.target instanceof HTMLCanvasElement)) throw new Error("ev.target is null");

    const rect = ev.target.getBoundingClientRect();

    console.log("rect. left, top, width, height: " + rect.left + " "  + rect.top + " " + rect.width + " " + rect.height );

    // Todo-1: convert x and y to canvas space and normal them to (-1, 1) for webgl to use
    x = ((x-rect.left) / 200) - 1;
    y = -(((y-rect.top) / 200) - 1);

    console.log("x: " + x);
    console.log("y: " + y);

    //put mouse click position to g_points
    g_points.push([x, y]); 
    // //Todo-2: calculate color of the point
    if(x >= 0 && y >= 0)
    {
        g_colors.push([1.0, 0.0, 0.0, 1.0]) //red
    }
    else if(x < 0 && y < 0)
    {
        g_colors.push([0.0, 1.0, 0.0, 1.0]) //green
    }
    else if(x < 0 && y >= 0)
    {
        g_colors.push([0.0, 0.0, 1.0, 1.0]) //blue
    }
    else
    {
        g_colors.push([1.0, 1.0, 1.0, 1.0]) //white
    }

    // // Clear canvas by background color before drawing
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    // // TODO-3: draw all points in "g_points" one-by-one
    const len = g_points.length;
    for(let i = 0; i < len; i++)
    {
        const xy = g_points[i];
        const rgba = g_colors[i];

        gl.uniform4f(u_Position, xy[0], xy[1], 0, 1); // TODO: pass position of a point into shader to draw
        gl.uniform4f(u_FragColor, rgba[0], rgba[1], rgba[2], rgba[3]); // TODO: pass color of a point into shader to draw

        gl.drawArrays(gl.POINTS, 0, 1); //draw a point
    }
}