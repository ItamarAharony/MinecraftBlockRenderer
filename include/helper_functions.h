#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <GLFW/glfw3.h>

// Function for processing input (e.g., for keyboard and mouse)
void processInput(GLFWwindow* window);

// Callback function to adjust the viewport when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
