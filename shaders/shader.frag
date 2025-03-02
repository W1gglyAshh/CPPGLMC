#version 410 core

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D blockTexture;

void main()
{
    fragColor = texture(blockTexture, texCoord);
}
