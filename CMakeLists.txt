cmake_minimum_required(VERSION 3.10)
project(MinecraftBlockRenderer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Specify the paths to GLFW and Glad (relative paths)
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/external/glfw-3.4")
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/external/glad")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/external/glm")

# Add Glad manually (since it does not have its own CMakeLists.txt)
add_library(glad STATIC ${GLAD_DIR}/src/glad.c)

# Add GLFW
add_subdirectory(${GLFW_DIR})

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR} # For the main project includes
    ${GLFW_DIR}/include # For GLFW headers
    ${GLAD_DIR}/include # For Glad headers
    ${GLM_DIR}          # For GLM headers
    ${CMAKE_SOURCE_DIR}/external # For stb_image.h
)

# Add the source files for the project
set(SOURCES
    src/main.cpp
    external/stb_image.cpp   # Add the path to stb_image.cpp
    # Add other source files here as necessary
)

# Add an executable target for the project
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries (GLFW, Glad, and OpenGL)
target_link_libraries(${PROJECT_NAME} glfw glad opengl32)

# If you're using shaders, you can copy them to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/shaders)

# Optionally, specify additional settings like debugging
set_target_properties(${PROJECT_NAME} PROPERTIES
    DEBUG_POSTFIX "_d"
)
