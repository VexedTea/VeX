uniform sampler2D texture;

in vec2 texCoord;

void main()
{
    vec4 pixel = texture2D(texture, texCoord.xy);
    //vec4 pixel = texture2D(texture, vec2(texCoord.x/2560, texCoord.y/1440));

    gl_FragColor = gl_Color * pixel;
}