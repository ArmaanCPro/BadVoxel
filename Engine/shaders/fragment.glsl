#version 330 core
out vec4 FragColor; 

uniform vec4 ourColor; // we set this variable in OpenGl code

void main()
{
    FragColor = ourColor;
} 