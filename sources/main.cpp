#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main(int argc, char *argv[]) {
    GLFWwindow* window;
    // init the library
    if (!glfwInit()) {
        fprintf(stderr, "Failed to init glfw library\n");
        return EXIT_FAILURE;
    }
    // create window with opengl context
    window = glfwCreateWindow(640, 480, "OpenGL app", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create opengl window\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    // make window current context
    glfwMakeContextCurrent(window);
    // glew init
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    // main render loop
    while (!glfwWindowShouldClose(window)) {
        // clear window
        glClear(GL_COLOR_BUFFER_BIT);
        // render stuff
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();
        // swap double buffer (front and back)
        glfwSwapBuffers(window); 
        // poll events
        glfwPollEvents();
    }
    // terminate the opengl library? or context?
    glfwTerminate();

    return EXIT_SUCCESS;
}