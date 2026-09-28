#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

// false = usar textura del modelo
// true  = usar un color sólido
uniform bool useSolidColor;

uniform vec4 solidColor;

// AGREGADO: indica si el mesh tiene textura difusa
uniform bool hasDiffuseTexture;

// AGREGADO: color Kd obtenido del archivo MTL
uniform vec3 diffuseColor;

void main()
{
    if (useSolidColor)
    {
        FragColor = solidColor;
    }
    else
    {
        if (hasDiffuseTexture)
        {
            vec4 texColor = texture(texture_diffuse1, TexCoords);

            if (texColor.a < 0.1)
                discard;

            FragColor = texColor;
        }
        else
        {
            FragColor = vec4(diffuseColor, 1.0);
        }
    }
}