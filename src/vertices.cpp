#include "vertices.h"

// Define the vertices array
const float vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // Top-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // Top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // Bottom-left

    // Back face
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Bottom-left
     -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // Bottom-right
     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // Top-right
     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // Top-right
    0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // Top-left
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Bottom-left

    // Left face (adjust texture coordinates)
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // Top-right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // Bottom-right
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // Bottom-left
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // Bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // Top-left
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // Top-right

    // Right face (adjust texture coordinates)
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // Top-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // Bottom-right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // Top-left
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // Top-right

     // Bottom face (reversed texture coordinates)
     -0.5f, 0.5f, -0.5f,  1.0f, 1.0f,  // Top-left
      0.5f, 0.5f, -0.5f,  0.0f, 1.0f,  // Top-right
      0.5f, 0.5f,  0.5f,  0.0f, 0.0f,  // Bottom-right
      0.5f, 0.5f,  0.5f,  0.0f, 0.0f,  // Bottom-right
     -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,  // Bottom-left
     -0.5f, 0.5f, -0.5f,  1.0f, 1.0f,  // Top-left

     // Top face (reversed texture coordinates)
    -0.5f,  -0.5f, -0.5f,  1.0f, 0.0f,  // Top-left
     0.5f,  -0.5f, -0.5f,  0.0f, 0.0f,  // Top-right
     0.5f,  -0.5f,  0.5f,  0.0f, 1.0f,  // Bottom-right
     0.5f,  -0.5f,  0.5f,  0.0f, 1.0f,  // Bottom-right
    -0.5f,  -0.5f,  0.5f,  1.0f, 1.0f,  // Bottom-left
    -0.5f,  -0.5f, -0.5f,  1.0f, 0.0f   // Top-left
};

// Define the size of the array (in bytes)
const unsigned int verticesSize = sizeof(vertices);
