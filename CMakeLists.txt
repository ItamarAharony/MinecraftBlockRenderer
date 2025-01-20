cmake_minimum_required(VERSION 3.10)
project(MinecraftBlockRenderer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Specify the paths to GLFW, Glad, and GLM (relative paths)
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/external/glfw-3.4")
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/external/glad")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/external/glm")

# Add Glad manually (since it does not have its own CMakeLists.txt)
add_library(glad STATIC ${GLAD_DIR}/src/glad.c)

# Include the glad header directory for the glad target
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)



# Add GLFW
add_subdirectory(${GLFW_DIR})

# Collect all source files (C++ files) in the src directory
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Collect all header files (C++ header files) in the include directory
file(GLOB HEADERS
    include/*.h
)

# Collect shader files
file(GLOB SHADERS
    shaders/*.vert
    shaders/*.frag
    shaders/*.glsl
)

# Collect resource files (if you have a resources folder)
file(GLOB RESOURCES
    resources/*
)

# Group shaders into a "Shaders" filter for Visual Studio
source_group("Shaders" FILES ${SHADERS})

# Group resources into a "Resources" filter for Visual Studio (optional)
source_group("Resources" FILES ${RESOURCES})

# Add an executable target for the project
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${SHADERS} ${RESOURCES})

# Include directories for the target
target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLFW_DIR}/include             # For GLFW headers
    ${GLAD_DIR}/include             # For Glad headers
    ${GLM_DIR}                      # For GLM headers
    ${CMAKE_SOURCE_DIR}/external    # For stb_image.h
    ${CMAKE_SOURCE_DIR}/include     # For shader_loader.h and helper_functions.h
)

# Link libraries (GLFW, Glad, and OpenGL)
target_link_libraries(${PROJECT_NAME} glfw glad opengl32)

# Organize libraries and dependencies into a "Dependencies" filter in Visual Studio
set_target_properties(glad PROPERTIES FOLDER "Dependencies")
set_target_properties(glfw PROPERTIES FOLDER "Dependencies")

# Copy shaders and resources to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/shaders)
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/resources)

# Set this project as the default startup project in Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Optionally, specify additional settings like debugging or postfix
set_target_properties(${PROJECT_NAME} PROPERTIES
    DEBUG_POSTFIX "_d"
)
