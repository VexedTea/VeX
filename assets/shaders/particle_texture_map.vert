uniform vec2 screenSize;
uniform vec2 textureSize;

varying out vec2 texCoord;

void main()
{   
    texCoord = gl_Vertex / screenSize;
    texCoord *= screenSize / textureSize;
    if(textureSize.x > textureSize.y){
        texCoord *= textureSize.x / screenSize.x;
        vec2 scale = texCoord / (gl_Vertex / screenSize);
        texCoord.y -= (0.5 * scale.y) - 0.5;
    }else{
        texCoord *= textureSize.y / screenSize.y;
        vec2 scale = texCoord / (gl_Vertex / screenSize);
        texCoord.x -= (0.5 * scale.x) - 0.5;
    }

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    gl_FrontColor = gl_Color;
}