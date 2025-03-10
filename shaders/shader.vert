#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aOffset;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 texCoord;

void main()
{
    vec3 instancePos = aPos + aOffset;
    gl_Position = projection * view * model * vec4(instancePos, 1.0);
    texCoord = aTexCoord;
}
