cmake_minimum_required (VERSION 2.6)
project (OpenGL_Tutorial)

# set directories
set (PROJECT_BINARY_DIR "bin")
set (PROJECT_SOURCE_DIR "sources")

set (APP_SRC_FILES 
    ${PROJECT_SOURCE_DIR}/App/App.cpp
    ${PROJECT_SOURCE_DIR}/App/AppInit.cpp
    ${PROJECT_SOURCE_DIR}/App/Debug.cpp
    ${PROJECT_SOURCE_DIR}/App/Errors.cpp
    ${PROJECT_SOURCE_DIR}/App/ImGui.cpp
    ${PROJECT_SOURCE_DIR}/App/IndexBuffer.cpp
    ${PROJECT_SOURCE_DIR}/App/Renderer.cpp
    ${PROJECT_SOURCE_DIR}/App/Shader.cpp
    ${PROJECT_SOURCE_DIR}/App/Texture.cpp
    ${PROJECT_SOURCE_DIR}/App/Uniform.cpp
    ${PROJECT_SOURCE_DIR}/App/VertexArray.cpp
    ${PROJECT_SOURCE_DIR}/App/VertexBuffer.cpp
    ${PROJECT_SOURCE_DIR}/App/VertexBufferLayout.cpp
    ${PROJECT_SOURCE_DIR}/App/Tests/TestClearColour.cpp
    ${PROJECT_SOURCE_DIR}/App/Tests/TestCube.cpp
    ${PROJECT_SOURCE_DIR}/App/Tests/TestDoge.cpp
    ${PROJECT_SOURCE_DIR}/App/Tests/TestMenu.cpp
    ${PROJECT_SOURCE_DIR}/App/Tests/TestRainbow.cpp
    ${PROJECT_SOURCE_DIR}/App/Tests/TestTexture.cpp)

# set compiler
set (CMAKE_C_COMPILER C:/MinGW/bin/gcc.exe)
set (CMAKE_CXX_COMPILER C:/MinGW/bin/g++.exe)

# version number
set (OpenGLBegin_VERSION_MAJOR 1)
set (OpenGLBegin_VERSION_MINOR 0)

# config file
configure_file (
    ${PROJECT_SOURCE_DIR}/OpenGLBeginConfig.h.in
    ${PROJECT_BINARY_DIR}/OpenGLBeginConfig.h
)
include_directories (build/${PROJECT_BINARY_DIR})

# include vendor libraries
include_directories (${PROJECT_SOURCE_DIR}/vendor)

# glew
set (BUILD_UTILS OFF CACHE BOOL "" FORCE)
include_directories (${PROJECT_SOURCE_DIR}/vendor/glew/include)
add_subdirectory (${PROJECT_SOURCE_DIR}/vendor/glew/build/cmake)
set (EXTRA_LIBS ${EXTRA_LIBS} glew_s)

# glfw
set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
include_directories (${PROJECT_SOURCE_DIR}/vendor/glfw/include)
add_subdirectory (${PROJECT_SOURCE_DIR}/vendor/glfw)
set (EXTRA_LIBS ${EXTRA_LIBS} glfw)

# glm
add_subdirectory (${PROJECT_SOURCE_DIR}/vendor/glm)
set (EXTRA_LIBS ${EXTRA_LIBS} glm_static)

# imgui
add_subdirectory (${PROJECT_SOURCE_DIR}/vendor/imgui)
set (EXTRA_LIBS ${EXTRA_LIBS} imgui)

# stb_image
add_subdirectory (${PROJECT_SOURCE_DIR}/vendor/stb_image)
set (EXTRA_LIBS ${EXTRA_LIBS} stb_image)

# rainbow colour
add_subdirectory (${PROJECT_SOURCE_DIR}/vendor/RainbowColour)
set (EXTRA_LIBS ${EXTRA_LIBS} RainbowColour)

# include app
include_directories (${PROJECT_SOURCE_DIR}/App)
include_directories (${PROJECT_SOURCE_DIR}/App/Tests)
add_library (App ${APP_SRC_FILES})
target_link_libraries (App ${EXTRA_LIBS})
target_compile_definitions (App PRIVATE)

# create executable
add_executable (main ${PROJECT_SOURCE_DIR}/main.cpp)
set_target_properties (main PROPERTIES EXECUTABLE_OUTPUT_PATH ".")
target_link_libraries (main App)
target_compile_options (main PRIVATE -std=c++17 -O3)

install (TARGETS main DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)
