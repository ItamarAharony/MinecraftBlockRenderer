@echo off
REM Ensure working directory is the project directory
cd /d C:\Users\itama\source\repos\MinecraftBlockRenderer

REM Clean up the previous build folder
rmdir /s /q build

REM Create a new build folder
mkdir build

REM Change to the build directory
cd build

REM Run CMake to regenerate project files
cmake -G "Visual Studio 17 2022" ..

REM Open the generated .sln file with Visual Studio
start MinecraftBlockRenderer.sln
