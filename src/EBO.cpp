#include "EBO.h"

// Constructor that creates an EBO and links it to vertices
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Binds EBO
void EBO::Bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds EBO so it can't be accidentally modified
void EBO::Unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
  glDeleteBuffers(1, &ID);
}