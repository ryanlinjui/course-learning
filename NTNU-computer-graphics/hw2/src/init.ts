/////BEGIN:///////////////////////////////////////////////////////////////////////////////////////////////
/////The folloing three function is for creating vertex buffer, but link to shader to user later//////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
export function initAttributeVariable(gl:WebGL2RenderingContext, a_attribute, buffer)
{
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
    gl.vertexAttribPointer(a_attribute, buffer.num, buffer.type, false, 0, 0);
    gl.enableVertexAttribArray(a_attribute);
}

function initArrayBufferForLaterUse(gl:WebGL2RenderingContext, data:Float32Array, num:number, type:number) 
{
    // Create a buffer object
    const buffer = gl.createBuffer();
    if (!buffer) 
    {
      console.log("Failed to create the buffer object");
      return null;
    }
    // Write date into the buffer object
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
    gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);
  
    // Store the necessary information to assign the object to the attribute variable later

    return Object.assign(buffer, {num, type})
}

export function initVertexBufferForLaterUse(gl:WebGL2RenderingContext, vertices:number[], colors:number[])
{
    const nVertices = vertices.length / 3;

    const o: Interface = {
        vertexBuffer: initArrayBufferForLaterUse(gl, new Float32Array(vertices), 3, gl.FLOAT),
        colorBuffer: initArrayBufferForLaterUse(gl, new Float32Array(colors), 3, gl.FLOAT),
        numVertices: nVertices
    };

    if (!o.vertexBuffer || !o.colorBuffer) 
    {
        console.log("Error: in initVertexBufferForLaterUse(gl, vertices, colors)"); 
    }
        
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);

    return o;
}
/////END://///////////////////////////////////////////////////////////////////////////////////////////////
/////The folloing three function is for creating vertex buffer, but link to shader to user later//////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


type Type = ReturnType<typeof initArrayBufferForLaterUse>;
export interface Interface {
    vertexBuffer: Type
    colorBuffer: Type,
    numVertices: number
}