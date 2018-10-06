cmake_minimum_required (VERSION 2.6)
project (OpenGL_Tutorial)

# set directories
set (PROJECT_BINARY_DIR "bin")
set (PROJECT_SOURCE_DIR "sources")
set (PROJECT_LIBRARY_DIR "libraries")

set (APP_SRC_FILES 
    ${PROJECT_SOURCE_DIR}/App/App.cpp
    ${PROJECT_SOURCE_DIR}/App/AppInit.cpp
    ${PROJECT_SOURCE_DIR}/App/Debug.cpp
    ${PROJECT_SOURCE_DIR}/App/Errors.cpp
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
file (GLOB VENDOR_SRC_FILES 
    ${PROJECT_SOURCE_DIR}/vendor/imgui/*.cpp
    ${PROJECT_SOURCE_DIR}/vendor/RainbowColour/*.cpp
    ${PROJECT_SOURCE_DIR}/vendor/stb_image/*.cpp)

# options
set (BUILD_OPENGL_LIB ON CACHE BOOL "" FORCE)
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

# add vendor libraries
include_directories (${PROJECT_SOURCE_DIR}/vendor)
# glew
if (BUILD_OPENGL_LIB)
    include_directories (${PROJECT_SOURCE_DIR}/vendor/glew/include)
    add_subdirectory (${PROJECT_SOURCE_DIR}/vendor/glew/build/cmake)
    set (EXTRA_LIBS ${EXTRA_LIBS} glew_s)
else ()
    add_library(glew32s STATIC IMPORTED)
    set_property(TARGET glew32s PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/${PROJECT_LIBRARY_DIR}/lib/GLEW/libglew32d.a)
    set (EXTRA_LIBS ${EXTRA_LIBS} glew32s)
endif ()
# glfw
if (BUILD_OPENGL_LIB)
    set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    include_directories (${PROJECT_SOURCE_DIR}/vendor/glfw/include)
    add_subdirectory (${PROJECT_SOURCE_DIR}/vendor/glfw)
    set (EXTRA_LIBS ${EXTRA_LIBS} glfw)
else ()
    add_library(glfw3 STATIC IMPORTED)
    set_property(TARGET glfw3 PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/${PROJECT_LIBRARY_DIR}/lib/GLFW/libglfw3.a)
    set (EXTRA_LIBS ${EXTRA_LIBS} glfw3)
endif ()
# if not building glew or glfw
if (NOT BUILD_OPENGL_LIB)
    include_directories (${PROJECT_LIBRARY_DIR}/include)
endif ()
# glm
add_subdirectory (${PROJECT_SOURCE_DIR}/vendor/glm)
set (EXTRA_LIBS ${EXTRA_LIBS} glm_static)

# include app
include_directories (${PROJECT_SOURCE_DIR}/App)
include_directories (${PROJECT_SOURCE_DIR}/App/Tests)
add_library (App ${APP_SRC_FILES} ${VENDOR_SRC_FILES})
target_link_libraries (App ${EXTRA_LIBS})
target_compile_definitions (App PRIVATE ${GLEW_DFLAGS})

# create executable
add_executable (main ${PROJECT_SOURCE_DIR}/main.cpp)
set_target_properties (main PROPERTIES EXECUTABLE_OUTPUT_PATH ".")
target_link_libraries (main App)
target_compile_options (main PRIVATE -std=c++17)

install (TARGETS main DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)