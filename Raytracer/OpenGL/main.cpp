#include <stdio.h>
#include <stdlib.h>

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL\glew.h>

// Include GLFW
#define GLFW_DLL
#include <GLFW\glfw3.h>

// Include GLM
#include <glm\glm.hpp>
using namespace glm;

#include <shader.hpp>
#include "Drawer.h"


int main()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
 
    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow( 1024, 768, "RayTracer", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed in core profile
    GLenum err = glewInit();
    if (err != GLEW_OK) 
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    // Ensure we can capture the escape key being pressed
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Create and compile our GLSL program from the shaders
    GLuint programId = LoadShaders( "Shaders\\SimpleVertexShader.vertexshader", "Shaders\\SimpleFragmentShader.fragmentshader" );

    // Initialize our drawer
    Drawer drawer = Drawer(programId);

    Model modelCube = Model(1);
    Model modelTriangle = Model(0);

    drawer.AddModel(&modelCube);
    drawer.AddModel(&modelTriangle);

    modelCube.TranslateModel(vec3(3.0f, 0.0f, 0.0f));
    modelCube.RotateModel(45.0, vec3(0.0, 1.0, 0.0));
    modelCube.ApplyTransformations();

    do 
    {
        drawer.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
           && glfwWindowShouldClose(window) == 0 );

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    // Cleanup
    glDeleteProgram(programId);

    return 0;
}