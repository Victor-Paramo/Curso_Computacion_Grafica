#version 330 core

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

uniform bool useSolidColor;
uniform vec4 solidColor;

uniform bool hasDiffuseTexture;
uniform vec3 diffuseColor;

uniform vec3 viewPos;

// Dos fuentes de luz
uniform Light sunLight;
uniform Light moonLight;

vec3 CalculateLight(
    Light light,
    vec3 normal,
    vec3 viewDir,
    vec3 objectColor,
    bool solid
)
{
    // ========================================================
    // AMBIENTAL
    // ========================================================

    vec3 ambient =
        light.ambient *
        objectColor;

    // ========================================================
    // DIFUSA
    // ========================================================

    vec3 lightDir =
        normalize(
            light.position -
            FragPos
        );

    float diff =
        max(
            dot(
                normal,
                lightDir
            ),
            0.0
        );

    vec3 diffuse =
        light.diffuse *
        diff *
        objectColor;

    // ========================================================
    // ESPECULAR
    // ========================================================

    vec3 reflectDir =
        reflect(
            -lightDir,
            normal
        );

    float spec =
        pow(
            max(
                dot(
                    viewDir,
                    reflectDir
                ),
                0.0
            ),
            16.0
        );

    vec3 specular;

    if (solid)
    {
        specular =
            light.specular *
            spec *
            0.05;
    }
    else
    {
        specular =
            light.specular *
            spec *
            0.25;
    }

    // ========================================================
    // RESULTADO DE ESTA LUZ
    // ========================================================

    return
        ambient +
        diffuse +
        specular;
}

void main()
{
    // ========================================================
    // COLOR ORIGINAL
    // ========================================================

    vec4 objectColor;

    if (useSolidColor)
    {
        objectColor =
            solidColor;
    }
    else
    {
        if (hasDiffuseTexture)
        {
            objectColor =
                texture(
                    texture_diffuse1,
                    TexCoords
                );

            if (objectColor.a < 0.1)
                discard;
        }
        else
        {
            objectColor =
                vec4(
                    diffuseColor,
                    1.0
                );
        }
    }

    // ========================================================
    // NORMAL
    // ========================================================

    vec3 norm =
        normalize(
            Normal
        );

    // ========================================================
    // DIRECCION A LA CAMARA
    // ========================================================

    vec3 viewDir =
        normalize(
            viewPos -
            FragPos
        );

    // ========================================================
    // LUZ DEL SOL
    // ========================================================

    vec3 sunResult =
        CalculateLight(
            sunLight,
            norm,
            viewDir,
            objectColor.rgb,
            useSolidColor
        );

    // ========================================================
    // LUZ DE LA LUNA
    // ========================================================

    vec3 moonResult =
        CalculateLight(
            moonLight,
            norm,
            viewDir,
            objectColor.rgb,
            useSolidColor
        );

    // ========================================================
    // RESULTADO FINAL
    // ========================================================

    vec3 result =
        sunResult +
        moonResult;

    FragColor =
        vec4(
            result,
            objectColor.a
        );
}