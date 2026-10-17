#version 330 core

#define NUMBER_OF_POINT_LIGHTS 4

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform DirLight windowLight; // Fuente direccional independiente, recortada por la abertura.
uniform vec3 windowOrigin;  // Centro del plano XY de la ventana (en coordenadas mundo).
uniform vec2 windowSize;    // Ancho y alto reales de la imagen de ventana.

uniform PointLight pointLights[NUMBER_OF_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;
uniform int transparency;

uniform bool useSolidColor;
uniform vec4 solidColor;
uniform bool hasDiffuseTexture;
uniform vec3 diffuseColor;
uniform sampler2D texture_diffuse1;

// Function prototypes
vec3 CalcDirLight( DirLight light, vec3 normal, vec3 viewDir, vec3 baseColor );
float WindowProjectionMask(vec3 fragPos);
vec3 CalcPointLight( PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 baseColor );
vec3 CalcSpotLight( SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 baseColor );

void main( )
{
    // Base color: same conventions used by the 8th-practice models.
    vec4 baseColor = useSolidColor ? solidColor :
        (hasDiffuseTexture ? texture(texture_diffuse1, TexCoords) : vec4(diffuseColor, 1.0));
    if (baseColor.a < 0.1) discard;
    // Properties
    vec3 norm = normalize( Normal );
    vec3 viewDir = normalize( viewPos - FragPos );
    
    // Directional lighting
    vec3 result = CalcDirLight( dirLight, norm, viewDir, baseColor.rgb );
    // Solo se suma la luz si el rayo inverso atraviesa la abertura de la ventana.
    result += WindowProjectionMask(FragPos) * CalcDirLight( windowLight, norm, viewDir, baseColor.rgb );
    
    // Point lights
    for ( int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++ )
    {
        result += CalcPointLight( pointLights[i], norm, FragPos, viewDir, baseColor.rgb );
    }
    
    // Spot light
    result += CalcSpotLight( spotLight, norm, FragPos, viewDir, baseColor.rgb );
    
    color = vec4(result, baseColor.a);

}


// Proyeccion espacial de la abertura de la ventana sobre suelo y muebles.
// La luz es paralela (direccional), pero su contribucion se limita al haz
// rectangular definido por windowOrigin, windowSize y windowLight.direction.
// No requiere nuevas texturas ni modelos y conserva las otras luces.
float WindowProjectionMask(vec3 fragPos)
{
    vec3 rayDirection = normalize(windowLight.direction);
    // La ventana yace en el plano XY a Z = windowOrigin.z.
    // Una direccion con componente Z negativa entra al interior.
    if (rayDirection.z >= -0.0001) return 0.0;

    // Seguir el rayo HACIA ATRAS desde el fragmento hasta el plano de la ventana.
    float t = (windowOrigin.z - fragPos.z) / (-rayDirection.z);
    if (t < 0.0) return 0.0; // Fragmento exterior, detras de la ventana.
    vec3 intersection = fragPos - rayDirection * t;
    vec2 local = intersection.xy - windowOrigin.xy;
    vec2 halfSize = windowSize * 0.5;

    // Atenuacion adicional segun la distancia recorrida DESDE la ventana.
    // Asi la proyeccion es mas intensa cerca del marco y desaparece
    // gradualmente hacia el centro de la biblioteca.
    float nearWindow = 1.0 - smoothstep(2.0, 7.0, t);

    // Bordes suaves de la abertura (0.10 unidades alrededor del limite).
    float edgeX = 1.0 - smoothstep(halfSize.x - 0.10, halfSize.x, abs(local.x));
    float edgeY = 1.0 - smoothstep(halfSize.y - 0.10, halfSize.y, abs(local.y));
    float aperture = edgeX * edgeY;

    // Divisiones aproximadas de los marcos. Dejan sombras sutiles
    // sobre la proyeccion; sus posiciones son editables.
    float frame = 1.0;
    if (abs(local.x) < 0.035 || abs(local.y) < 0.035 ||
        abs(local.y - windowSize.y * 0.25) < 0.025 ||
        abs(local.y + windowSize.y * 0.25) < 0.025)
        frame = 0.18;

    return aperture * frame * nearWindow;
}

// Calculates the color when using a directional light.
vec3 CalcDirLight( DirLight light, vec3 normal, vec3 viewDir, vec3 baseColor )
{
    vec3 lightDir = normalize( -light.direction );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), 16.0 );
    
    // Combine results
    vec3 ambient = light.ambient * baseColor;
    vec3 diffuse = light.diffuse * diff * baseColor;
    vec3 specular = light.specular * spec * vec3(0.25);
    
    return ( ambient + diffuse + specular );
}

// Calculates the color when using a point light.
vec3 CalcPointLight( PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 baseColor )
{
    vec3 lightDir = normalize( light.position - fragPos );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), 16.0 );
    
    // Attenuation
    float distance = length( light.position - fragPos );
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * ( distance * distance ) );
    
    // Combine results
    vec3 ambient = light.ambient * baseColor;
    vec3 diffuse = light.diffuse * diff * baseColor;
    vec3 specular = light.specular * spec * vec3(0.25);
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return ( ambient + diffuse + specular );
}

// Calculates the color when using a spot light.
vec3 CalcSpotLight( SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 baseColor )
{
    vec3 lightDir = normalize( light.position - fragPos );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), 16.0 );
    
    // Attenuation
    float distance = length( light.position - fragPos );
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * ( distance * distance ) );
    
    // Spotlight intensity
    float theta = dot( lightDir, normalize( -light.direction ) );
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp( ( theta - light.outerCutOff ) / epsilon, 0.0, 1.0 );
    
    // Combine results
    vec3 ambient = light.ambient * baseColor;
    vec3 diffuse = light.diffuse * diff * baseColor;
    vec3 specular = light.specular * spec * vec3(0.25);
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return ( ambient + diffuse + specular );
}
