uniform vec2 screenDimensions;
uniform vec2 textureSize;

varying out vec2 texCoord;

void main()
{   
    texCoord = vec2(gl_Vertex.x/2560, gl_Vertex.y/1440);

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    // texCoord = (gl_Position.xy + 1.0) / 2.0;
    // texCoord.y = 1.0 - texCoord.y;

    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    gl_FrontColor = vec4(1,1,1,1); //gl_Color;
}