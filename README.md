# MinecraftBlockRenderer

This is a C++ OpenGL project that renders a rotating Minecraft dirt block using shaders. The project uses GLFW for window/context management, GLAD for OpenGL function loading, and GLM for matrix transformations. Additionally, texture mapping is used to apply various textures to the block.

## Prerequisites

- CMake (3.10 or higher)
- Visual Studio 2022 (or any compatible IDE)
- GLFW, GLAD, GLM, stb_image libraries

## Building the Project

1. Clone the repository to your local machine.
2. Run `build_project.bat` to generate the solution files.
3. Open the generated `.sln` file in Visual Studio 2022.
4. Build and run the project.

## Folder Structure

- `src/`: Contains source files for the project.
- `include/`: Header files for shaders and helper functions.
- `external/`: External dependencies like GLFW, GLAD, and stb_image.
- `resources/`: Textures used for rendering the block.
- `shaders/`: GLSL shader files for vertex and fragment shaders.
- `CMakeLists.txt`: CMake configuration file for building the project.
- `build_project.bat`: Batch script to clean, build, and open the solution.