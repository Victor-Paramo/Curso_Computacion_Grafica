#version 330 core

in vec3 ourColor;
out vec4 color;

uniform bool usarColorLinea;

void main()
{
    if (usarColorLinea)
        color = vec4(0.02f, 0.02f, 0.02f, 1.0f); // Negro
    else
        color = vec4(ourColor, 1.0f);             // Verde del cubo
}