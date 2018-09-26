#include "App.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include <string>
#include <fstream>
#include <sstream>

using namespace app;

App::App() {
    initOpenGL();
}

void App::run() {
    render();
}

void App::render() {
    struct VertexData vertex_data[3] = {
        {-0.5f, -0.5f},
        { 0.0f,  0.5f},
        { 0.5f, -0.5f},
    };
    // creating and assigning data
    unsigned int buffer_id;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    // void glBufferData(GLenum target,     // tyoe of data
 	//                   GLsizeiptr size,   // size of buffer
 	//                   const GLvoid * data, // pointer to data
 	//                   GLenum usage);     // usage pattern
    // http://docs.gl/gl4/glBufferData
    // Usage specified the expected usage pattern of the data
    // GL_STATIC_DRAW = modified once and drawn many times
    // etc...
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    
    // define vertex layout
    // void glVertexAttribPointer(GLuint index,
 	//                            GLint size,   // total indexes, not sizeof
 	//                            GLenum type,  // GL_<TYPE>
 	//                            GLboolean normalized, // within -1 and 1
 	//                            GLsizei stride, // size of the vertex
 	//                            const GLvoid * pointer); // value of offset to the attribute, not a pointer actually
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct Position), (const void*)offsetof(VertexData, position));
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    struct ShaderFile shaderFile = parseShaderFile("resources/shaders/basicShader.shader");
    unsigned int programId = createProgram(shaderFile.vertex, shaderFile.fragment);
    glUseProgram(programId);

    // main render loop
    while (!glfwWindowShouldClose(window)) 
    {
        // clear window
        glClear(GL_COLOR_BUFFER_BIT);
        // render stuff
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertex_data)/sizeof(VertexData));
        // swap double buffer (front and back)
        glfwSwapBuffers(window); 
        // poll events
        glfwPollEvents();
    }
    glDeleteProgram(programId);
    // terminate the opengl library? or context?
    glfwTerminate();
}

