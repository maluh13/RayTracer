#include "Model.h"
#include "glm/gtc/matrix_transform.hpp"

#include "Constants.h"

Model::Model(GLuint type)
{
    if(type == 0)
    {
        m_vertices = g_vertex_buffer_data_triangle;
        m_color = g_color_buffer_data_triangle;
        m_numVertices = sizeof(g_vertex_buffer_data_triangle);
    }
    else if(type == 1)
    {
        m_vertices = g_vertex_buffer_data_cube;
        m_color = g_color_buffer_data_cube;
        m_numVertices = sizeof(g_vertex_buffer_data_cube);
    }

    glGenVertexArrays(1, &m_vertexArrayId);
    glBindVertexArray(m_vertexArrayId);

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &m_vertexbuffer);
 
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
 
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, m_numVertices, m_vertices, GL_STATIC_DRAW);

    glGenBuffers(1,&m_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_numVertices, m_color, GL_STATIC_DRAW);

    SetUpMatrices();
}

void Model::SetUpMatrices()
{
    // Model matrix : an identity matrix (model will be at the origin)
    m_model = glm::mat4(1.0f);
    m_translate = glm::mat4(1.0f);
    m_scale = glm::mat4(1.0f);
    m_rotate = glm::mat4(1.0f);
}

Model::~Model()
{
    glDeleteBuffers(1, &m_vertexbuffer);
    glDeleteVertexArrays(1, &m_vertexArrayId);
    glDeleteBuffers(1, &m_colorBuffer);
}

mat4 Model::GetModelMatrix()
{
    return m_model;
}

GLuint Model::GetMatrixId()
{
    return m_matrixId;
}

GLuint Model::GetVertexBuffer()
{
    return m_vertexbuffer;
}

GLuint Model::GetColorBuffer()
{
    return m_colorBuffer;
}

GLuint Model::GetNumberOfVertices()
{
    return m_numVertices;
}

void Model::TranslateModel(vec3 translateAmount)
{
    m_translate = glm::translate(m_model, translateAmount);
}

void Model::ScaleModel(vec3 scaleAmount)
{
    m_scale = glm::scale(m_model, scaleAmount);
}

void Model::RotateModel(float angle, vec3 axis)
{
    m_rotate = glm::rotate(m_model, angle, axis);
}

void Model::ApplyTransformations()
{
    m_model = m_translate * m_rotate * m_scale;
}

void Model::Draw(mat4 MV)
{
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // color attribute
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, m_numVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
 
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}