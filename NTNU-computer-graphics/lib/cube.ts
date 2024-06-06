import {
    initVertexBufferForLaterUse3D
} from "./init";

// normal vector calculation (for the cube)
export function getNormalOnVertices(vertices: number[])
{
    const normals: number[] = [];
    const nTriangles = vertices.length / 9;
    for(let i = 0; i < nTriangles; i++ )
    {
        let idx = i * 9 + 0 * 3;
        const p0x = vertices[idx+0], p0y = vertices[idx+1], p0z = vertices[idx+2];
        idx = i * 9 + 1 * 3;
        var p1x = vertices[idx+0], p1y = vertices[idx+1], p1z = vertices[idx+2];
        idx = i * 9 + 2 * 3;
        var p2x = vertices[idx+0], p2y = vertices[idx+1], p2z = vertices[idx+2];
  
        const ux = p1x - p0x, uy = p1y - p0y, uz = p1z - p0z;
        const vx = p2x - p0x, vy = p2y - p0y, vz = p2z - p0z;
  
        let nx = uy*vz - uz*vy;
        let ny = uz*vx - ux*vz;
        let nz = ux*vy - uy*vx;
  
        const norm = Math.sqrt(nx*nx + ny*ny + nz*nz);
        nx = nx / norm;
        ny = ny / norm;
        nz = nz / norm;
  
        normals.push(nx, ny, nz, nx, ny, nz, nx, ny, nz);
    }
    return normals;
  }

export function parseOBJ(text: string)
{
    // because indices are base 1 let's just fill in the 0th data
    const objPositions = [[0, 0, 0]];
    const objTexcoords = [[0, 0]];
    const objNormals = [[0, 0, 0]];
  
    // same order as `f` indices
    const objVertexData = [
        objPositions,
        objTexcoords,
        objNormals,
    ];
  
    // same order as `f` indices
    let webglVertexData: number[][] = [
        [],   // positions
        [],   // texcoords
        [],   // normals
    ];
  
    const materialLibs: string[] = [];

    interface Geo {
        object: string;
        groups: string[];
        material: string;
        data: {
            position: number[];
            texcoord: number[];
            normal: number[];
        };
    }

    const geometries: Geo[] = [];
    let geometry: Geo | undefined;

    let groups = ['default'];
    let material = 'default';
    let object = 'default';
  
    const noop = () => {};
  
    function newGeometry() 
    {
        // If there is an existing geometry and it's
        // not empty then start a new one.
        if (geometry && geometry.data.position.length) 
        {
            geometry = undefined;
        }
    }
  
    function setGeometry() 
    {
        if (!geometry) 
        {
            const position: number[] = [];
            const texcoord: number[] = [];
            const normal: number[] = [];
            webglVertexData = [position, texcoord, normal];
            geometry = {
                object,
                groups,
                material,
                data: {
                    position,
                    texcoord,
                    normal,
                }
            };
            geometries.push(geometry);
        }
    }
  
    function addVertex(vert: string)
    {
        const ptn = vert.split('/');
        ptn.forEach((objIndexStr, i) => 
        {
            if (!objIndexStr) 
            {
                return;
            }
            const objIndex = parseInt(objIndexStr);
            const index = objIndex + (objIndex >= 0 ? 0 : objVertexData[i].length);
            webglVertexData[i].push(...objVertexData[i][index]);
        });
    }
  
    const keywords = 
    {
        v(parts: string[]) 
        {
            objPositions.push(parts.map(parseFloat));
        },
        vn(parts: string[])
        {
            objNormals.push(parts.map(parseFloat));
        },
        vt(parts: string[])
        {
            // should check for missing v and extra w?
            objTexcoords.push(parts.map(parseFloat));
        },
        f(parts: string[])
        {
            setGeometry();
            const numTriangles = parts.length - 2;
            for (let tri = 0; tri < numTriangles; ++tri) 
            {
                addVertex(parts[0]);
                addVertex(parts[tri + 1]);
                addVertex(parts[tri + 2]);
            }
        },
        s: noop, // smoothing group
        mtllib(parts: string[], unparsedArgs: string)
        {
            // the spec says there can be multiple filenames here
            // but many exist with spaces in a single filename
            materialLibs.push(unparsedArgs);
        },
        usemtl(parts: string[], unparsedArgs: string)
        {
            material = unparsedArgs;
            newGeometry();
        },
        g(parts: string[])
        {
            groups = parts;
            newGeometry();
        },
        o(parts: string[], unparsedArgs: string)
        {
            object = unparsedArgs;
            newGeometry();
        }
    };
  
    const keywordRE = /(\w*)(?: )*(.*)/;
    const lines = text.split('\n');
    for (let lineNo = 0; lineNo < lines.length; ++lineNo) 
    {
        const line = lines[lineNo].trim();
        if (line === '' || line.startsWith('#')) 
        {
            continue;
        }
        const m = keywordRE.exec(line);
        if (!m) 
        {
            continue;
        }
        const [, keyword, unparsedArgs] = m;
        const parts = line.split(/\s+/).slice(1);
        const handler = keywords[keyword];
        if (!handler) 
        {
            console.warn('unhandled keyword:', keyword);  // eslint-disable-line no-console
            continue;
        }
        handler(parts, unparsedArgs);
    }
  
    // remove any arrays that have no entries.
    for (const geometry of geometries) 
    {
        geometry.data = Object.fromEntries(
            Object.entries(geometry.data).filter(([, array]) => array.length > 0)
        ) as Geo["data"];
    }
  
    return {
        geometries,
        materialLibs,
    };
}

export async function loadOBJtoCreateVBO(
    gl: WebGL2RenderingContext,
    objFile: string
)
{
    const objComponents: any[] = [];

    let response = await fetch(objFile);
    let text = await response.text();
    let obj = parseOBJ(text);

    for( let i = 0; i < obj.geometries.length; i++)
    {        
        let o = initVertexBufferForLaterUse3D(
            gl, 
            obj.geometries[i].data.position,
            obj.geometries[i].data.normal, 
            obj.geometries[i].data.texcoord
        );
        objComponents.push(o);
    }
    return objComponents;
}