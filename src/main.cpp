//main.cpp


#include <glad/glad.h>   // This must come first!
#include <GLFW/glfw3.h>  // Then glfw3.h can be included after glad
#include <iostream>
#include <stb_image.h>  // Include stb_image for texture loading
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_loader.h"
#include "texture_loader.h"
#include "helper_functions.h"
#include "matrix_helper.h"
#include "vertices.h"




const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char* VERTEX_SHADER_PATH = "../shaders/vertex_shader.glsl";
const char* FRAGMENT_SHADER_PATH = "../shaders/fragment_shader.glsl";
const char* TEXTURE_BOTTOM_PATH = "../resources/Dirt_bottom.png";
const char* TEXTURE_SIDE_PATH = "../resources/Dirt_side.png";
const char* TEXTURE_TOP_PATH = "../resources/Dirt_top.png";




int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Create window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft Dirt Block", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }

    // Load and create the shader program
    unsigned int shaderProgram = createShaderProgram(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);


    // Set up OpenGL
    glEnable(GL_DEPTH_TEST);

    // Load the textures
    unsigned int textureBottom = loadTexture(TEXTURE_BOTTOM_PATH);
    unsigned int textureSide = loadTexture(TEXTURE_SIDE_PATH);
    unsigned int textureTop = loadTexture(TEXTURE_TOP_PATH);

    //  Bind Textures to Texture Units
    glUseProgram(shaderProgram); // Activate the shader program
    glUniform1i(glGetUniformLocation(shaderProgram, "textureBottom"), 0); // Texture unit 0
    glUniform1i(glGetUniformLocation(shaderProgram, "textureSide"), 1);   // Texture unit 1
    glUniform1i(glGetUniformLocation(shaderProgram, "textureTop"), 2);    // Texture unit 2

    // Bind textures to units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBottom);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureSide);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textureTop);


    // Create VAO, VBO, and EBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // Define attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // positions
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // texture coordinates
    glEnableVertexAttribArray(1);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);


        // Set transformation matrices
        setupMatrices(shaderProgram);
     
        // Draw the cube
        glBindVertexArray(VAO);


        // Render each face
        // Draw bottom face
        glUniform1i(glGetUniformLocation(shaderProgram, "faceId"), 0);
        glBindTexture(GL_TEXTURE_2D, textureBottom);
        glDrawArrays(GL_TRIANGLES, 30, 6);

        // Draw top face
        glUniform1i(glGetUniformLocation(shaderProgram, "faceId"), 1);
        glBindTexture(GL_TEXTURE_2D, textureTop);
        glDrawArrays(GL_TRIANGLES, 24, 6);

        // Draw side faces
        glUniform1i(glGetUniformLocation(shaderProgram, "faceId"), 2);
        glBindTexture(GL_TEXTURE_2D, textureSide);
        glDrawArrays(GL_TRIANGLES, 0, 24);




        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteTextures(1, &textureBottom);
    glDeleteTextures(1, &textureSide);
    glDeleteTextures(1, &textureTop);

    glfwTerminate();

    return 0;
}
