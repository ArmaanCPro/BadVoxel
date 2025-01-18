#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec3 ourPos;

uniform float uHorizOffset;


void main()
{
    ourPos = vec3(aPos.x + uHorizOffset, aPos.y * -1.0, aPos.z);
    gl_Position = vec4(ourPos, 1.0);
    ourColor = aColor;
}