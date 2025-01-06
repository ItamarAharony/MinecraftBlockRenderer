#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D textureBottom;
uniform sampler2D textureSide;
uniform sampler2D textureTop;
uniform int faceId; // Face identifier

void main()
{
    if (faceId == 0)
        FragColor = texture(textureBottom, TexCoords); // Bottom face
    else if (faceId == 1)
        FragColor = texture(textureTop, TexCoords); // Top face
    else
        FragColor = texture(textureSide, TexCoords); // Side faces
}
