#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>  // Include stb_image for texture loading
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <fstream>
#include <sstream>

std::string readShaderFile(const char* filePath) {
    std::ifstream shaderFile(filePath);
    std::stringstream shaderStream;

    if (shaderFile.is_open()) {
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
    }
    else {
        std::cerr << "ERROR: Could not open shader file " << filePath << std::endl;
    }

    return shaderStream.str();
}

unsigned int compileShader(const char* shaderSource, GLenum shaderType) {
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // Check for shader compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader compilation failed\n" << infoLog << std::endl;
    }

    return shader;
}

unsigned int createShaderProgram(const char* vertexPath, const char* fragmentPath) {
    // Read the shader files
    std::string vertexCode = readShaderFile(vertexPath);
    std::string fragmentCode = readShaderFile(fragmentPath);

    // Compile the shaders
    unsigned int vertexShader = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

    // Create and link the shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader program linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}





void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
GLuint loadTexture(const char* path)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // Horizontal direction
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  // Vertical direction

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  // Flip the image vertically if needed
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture at path: " << path << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}


int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Minecraft Dirt Block with Cat Texture", nullptr, nullptr);
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
    const char* vertexShaderPath = "../shaders/vertex_shader.glsl";
    const char* fragmentShaderPath = "../shaders/fragment_shader.glsl";
 

    unsigned int shaderProgram = createShaderProgram(vertexShaderPath, fragmentShaderPath);




    // Set up OpenGL
    glEnable(GL_DEPTH_TEST);
    float vertices[] = {
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




    // Load the textures
    unsigned int texture = loadTexture("../resources/Untitled.png");
    unsigned int textureBottom = loadTexture("../resources/Dirt_bottom.png");
    unsigned int textureSide = loadTexture("../resources/Dirt_side.png");
    unsigned int textureTop = loadTexture("../resources/Dirt_top.png");

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


     
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
