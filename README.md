# Minecraft Block Renderer

A lightweight C++ project using OpenGL for rendering a rotating Minecraft dirt block.

## Features
- OpenGL-based 3D rendering with GLFW, GLAD, and GLM.
- CMake support for cross-platform compatibility.
- Organized project structure.

## Prerequisites
- C++17-compatible compiler
- CMake (version 3.10 or later)
- OpenGL 3.3 or higher
- GLFW, GLAD, and GLM libraries

## Building the Project

### Windows
1. Open a terminal and navigate to the project directory.
2. Run the following commands:

```
mkdir build 
cd build 
cmake -G "Visual Studio 17 2022" ..
```
3. Open the generated `.sln` file in Visual Studio 2022 and build the solution.

### Linux/Mac
1. Open a terminal and navigate to the project directory.
2. Run the following commands:

```
mkdir build
cd build 
cmake .. make
```
3. Run the executable in the `build` folder.

## Resources
The project includes shaders, textures, and helper functions required for the rendering process.
