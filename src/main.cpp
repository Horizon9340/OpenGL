#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"



// Vertices coords
GLfloat vertices[] = 
{
    //          COORDINATES                          /      COLORS          //
    -0.5f,  -0.5f * float(sqrt(3)) / 3,       0.0f,     0.8f, 0.3f,  0.02f, // lower left
    0.5f,   -0.5f * float(sqrt(3)) / 3,       0.0f,     0.8f, 0.3f,  0.02f, // lower right
    0.0f,    0.5f * float(sqrt(3)) * 2 / 3,   0.0f,     1.0f, 0.6f,  0.32f, // upper
    -0.25f,  0.5f * float(sqrt(3)) / 6,       0.0f,     0.9f, 0.45f, 0.17f, // inner left
    0.25f,   0.5f * float(sqrt(3)) / 6,       0.0f,     0.9f, 0.45f, 0.17f, // inner right
    0.0f,   -0.5f * float(sqrt(3)) / 3,       0.0f,     0.8f, 0.3f,  0.02f, // inner down
};

GLuint indices [] =
{
    0, 3, 5, // low left triangle
    3, 2, 4, // low right triangle
    5, 4, 1, // upper triangle
};


// Main everything
int main() 
{
    // Initialize GLFW
    glfwInit();

    // Version info
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFWwindow object of 800x800 pixels
    GLFWwindow* window = glfwCreateWindow(800, 800, "Please delete me", NULL, NULL);
    if (window == NULL) 
    { // Error check if it fails
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Tell stupid OpenGL that we want to use this window
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    gladLoadGL();

    // Specify the viewport of OpenGL in this window
    glViewport(0, 0, 800, 800);


    // Creates shader object with vert and frag files
    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

    // Create Vertex Array Object and bind it
    VAO VAO1;
    VAO1.Bind();

    // Create Vertex Buffer Object and Element Buffer Object, link them to vertices
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0); // Link VAO to VBO, only specifying the vertex coordinates
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Link VBO to VAO, only specifying the fragment colors
    // Unbind all objects
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Gets ID of a uniform called "scale"
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();

        // Assigns a scale factor
        glUniform1f(uniID, 0.5f);

        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // triangle primitive
        glfwSwapBuffers(window);

        // Update the window or something
        glfwPollEvents();
    }

    // Delete everything
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();


    // Kill window and everything else
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

