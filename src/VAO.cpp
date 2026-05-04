#include "VAO.h"

// Constructor that creates a VAO object
VAO::VAO()
{
  glGenVertexArrays(1, &ID);
}

// Links a VBO to a VAO using a certain layout
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
  VBO.Bind();
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}

// Binds VAO
void VAO::Bind()
{
  glBindVertexArray(ID);
}

// Unbinds VAO so it can't be accidentally modified
void VAO::Unbind()
{
  glBindVertexArray(0);
}

void VAO::Delete()
{
  glDeleteVertexArrays(1, &ID);
}