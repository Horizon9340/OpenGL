#include "VBO.h"

// Constructor that creates a VBO and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ARRAY_BUFFER, ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds VBO
void VBO::Bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds VBO so it can't be accidentally modified
void VBO::Unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
  glDeleteBuffers(1, &ID);
}