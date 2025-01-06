#include "helper_functions.h"
#include <GLFW/glfw3.h>
#include <iostream>

// This function processes input, handling keyboard events
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); // Close the window if ESC is pressed
}

// This function is a callback to adjust the OpenGL viewport on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);  // Adjust OpenGL's viewport size to the new window size
}
