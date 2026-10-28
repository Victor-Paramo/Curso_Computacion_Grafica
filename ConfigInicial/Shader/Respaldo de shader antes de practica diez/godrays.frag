#version 330 core
in float progress;
out vec4 FragColor;
uniform vec3 rayColor;
uniform float rayOpacity;
void main()
{
    // Difuminado longitudinal; los haces no son iluminacion real del aire.
    float fade = pow(1.0 - smoothstep(0.08, 1.0, progress), 1.45);
    float start = smoothstep(0.0, 0.10, progress);
    float alpha = rayOpacity * fade * start;
    FragColor = vec4(rayColor, alpha);
}
