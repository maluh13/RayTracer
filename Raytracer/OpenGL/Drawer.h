#pragma once

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL\glew.h>

// Include GLFW
#define GLFW_DLL
#include <GLFW\glfw3.h>

// Include GLM
#include <glm\glm.hpp>
using namespace glm;

#include <vector>
#include "Model.h"


// The Drawer sets up the drawing environment
// (projection, view, etc) for each model to be drawn
class Drawer
{
public:

    Drawer(GLuint programId);

    ~Drawer();
    
    void Draw();

    void AddModel(Model* model);

private:
    
    glm::mat4 m_view;
    glm::mat4 m_projection;
    glm::mat4 m_MV;

    GLuint m_programId;

    std::vector<Model*> m_models;

    void SetUpMatrices();

    GLuint m_vertexArrayId;
    GLuint m_matrixId;
    
    // This will identify our vertex buffer
    GLuint m_vertexbuffer;
    GLuint m_colorBuffer;

};