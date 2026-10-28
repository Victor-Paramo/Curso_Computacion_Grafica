#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in float aProgress;
uniform mat4 view;
uniform mat4 projection;
out float progress;
void main()
{
    progress = aProgress;
    gl_Position = projection * view * vec4(aPos, 1.0);
}
