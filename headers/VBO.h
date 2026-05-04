#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

  class VBO
  {
    public:
    // Reference ID of Vertex Buffer Object
      GLuint ID;
      // Constructor that creates a VBO and links it to vertices
      VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind(); // Binds VBO
    void Unbind(); // Unbinds VBO so it can't be accidentally modified
    void Delete();

  };

#endif
