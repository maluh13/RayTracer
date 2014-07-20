#include "Drawer.h"
#include "glm/gtc/matrix_transform.hpp"

Drawer::Drawer(GLuint programId)
{
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    m_programId = programId;

    m_models = std::vector<Model*>();

    SetUpMatrices();
}

Drawer::~Drawer()
{
}

void Drawer::SetUpMatrices()
{
    // Get a handle for our "MVP" uniform
    m_matrixId = glGetUniformLocation(m_programId, "MVP");

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    m_projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    // Or, for an ortho camera :
    // Seems like it puts the camera in one place and looks at the origin
    // like looking into a graph that goes from -10 to 10 in x and in y
    //m_projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
    m_view = glm::lookAt(glm::vec3(0,3,10), // Camera is at (4,3,3), in World Space
                         glm::vec3(0,0,0), // and looks at the origin
                         glm::vec3(0,1,0));  // Head is up (set to 0,-1,0 to look upside-down)

    // Our ModelViewProjection : multiplication of our 3 matrices
    // Done for each model i am rendering
    m_MV = m_projection * m_view; // Remember, matrix multiplication is the other way around
}

void Drawer::AddModel(Model* model)
{
    m_models.push_back(model);
}

void Drawer::Draw()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(m_programId);

    for (unsigned int i = 0; i < m_models.size(); i++)
    {
        Model* currentModel = m_models[i];

        mat4 MVP = m_MV * currentModel->GetModelMatrix();
        glUniformMatrix4fv(m_matrixId, 1, GL_FALSE, &MVP[0][0]);

        currentModel->Draw(m_MV);
    }
}