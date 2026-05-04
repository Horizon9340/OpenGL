#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
  public:
    // Reference ID of Vertex Buffer Object
    GLuint ID;
    // Constructor that creates a VAO object
    VAO();

    // Links a VBO to a VAO using a certain layout
    void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset); 
    void Bind(); // Binds VAO
    void Unbind(); // Unbinds VAO so it can't be accidentally modified
    void Delete();

};

#endif
