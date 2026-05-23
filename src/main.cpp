#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "camera.h" 

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coords
GLfloat vertices[] = 
{
    //   COORDINATES     /       COLORS      //
    -0.5f, 0.0f,  0.5f,     0.8f, 0.3f,  0.02f, 
    -0.5f, 0.0f, -0.5f,     0.8f, 0.3f,  0.02f,
    0.5f,  0.0f, -0.5f,     1.0f, 0.6f,  0.32f,
    0.5f,  0.0f,  0.5f,     0.9f, 0.45f, 0.17f,
    0.0f,   0.8f, 0.0f,     0.9f, 0.45f, 0.17f,
};

GLuint indices [] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4,
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
    GLFWwindow* window = glfwCreateWindow(width, height, "kill me", NULL, NULL);
    if (window == NULL) 
    { // Error check if it fails
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window); // Tell stupid OpenGL that we want to use this window
    gladLoadGL();
    glViewport(0, 0, width, height);

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

    // Enables depth buffer, 3D shapes look stupid without it
    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();

        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); // triangle primitive
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

