//Rectangle
#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform float visibility;
uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;

void main()
{
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    FragColor = mix(texture(ourTexture0, TexCoord), texture(ourTexture1, TexCoord), visibility); //vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}