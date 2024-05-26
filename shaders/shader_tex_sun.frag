#version 430 core

uniform vec3 objectColor;
uniform vec3 lightDir;
uniform sampler2D sampler2dtype;

in vec3 interpNormal;
in vec2 vertexTexCoord1;
out vec4 fragColor;

void main()
{
    vec3 normal = normalize(interpNormal);
    
    // Without lighting
    /*
    float diffuse = max(dot(normal, -lightDir), 0.0);
    fragColor = vec4(textureColor.xyz * diffuse, 1.0);
    */
    
    vec4 textureColor = texture(sampler2dtype, vertexTexCoord1);  // Use texture() instead of texture2D()
    fragColor = vec4(textureColor.xyz, 1.0);  // Use the defined output variable
}
