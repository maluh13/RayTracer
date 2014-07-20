#pragma once

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL\glew.h>

// Include GLFW
#define GLFW_DLL
#include <GLFW\glfw3.h>

// Include GLM
#include <glm\glm.hpp>
using namespace glm;


// The model class holds the vertices, color and transformation
// information for a Model
class Model
{
public:

    Model(GLuint type);

    ~Model();

    // Returns the model matrix (the one that
    // should be multiplied with  projection * view)
    mat4 GetModelMatrix();
    GLuint GetMatrixId();
    GLuint GetVertexBuffer();
    GLuint GetColorBuffer();
    GLuint GetNumberOfVertices();

    void TranslateModel(vec3 translateAmount);
    void ScaleModel(vec3 scaleAmount);
    void RotateModel(float angle, vec3 axis);
    void ApplyTransformations();

    void Draw(mat4 MV);

private:

    const GLfloat* m_vertices;
    const GLfloat* m_color;
    GLuint m_numVertices;

    GLuint m_vertexArrayId;
    GLuint m_matrixId;
    
    // This will identify our vertex buffer
    GLuint m_vertexbuffer;
    GLuint m_colorBuffer;

    glm::mat4 m_model;
    glm::mat4 m_translate;
    glm::mat4 m_rotate;
    glm::mat4 m_scale;

    void SetUpMatrices();
};