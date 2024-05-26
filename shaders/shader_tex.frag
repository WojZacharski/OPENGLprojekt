#version 430 core

uniform vec3 objectColor;
uniform vec3 lightDir;
uniform sampler2D sampler2dtype;

in vec3 interpNormal;
in vec2 vertexTexCoord1;
in vec3 Position;

out vec4 fragColor;  

void main()
{
    //Obliczanie kierunku padania œwiat³a
    vec3 lightDir2 = normalize(Position - vec3(0, 0, 0));

  
    vec3 normal = normalize(interpNormal);

    // Obliczanie parametru rozproeszenia
    float diffuse = max(dot(normal, -lightDir2), 0.0);

    // Sample the texture
    vec4 textureColor = texture(sampler2dtype, vertexTexCoord1);

    // Obliczanie ostatecznego koloru
    fragColor = vec4(textureColor.xyz * diffuse, 1.0);  
}
