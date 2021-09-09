#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform float r;
uniform float g;
uniform float b;
uniform float a = 1.0f;

void main()
{
   FragColor = vec4(ourColor.r + r, ourColor.g + g, ourColor.b + b, a);
}