#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

  class EBO
  {
    public:
      // Reference ID of Element Buffer Object
      GLuint ID;
      // Constructor that creates an EBO and links it to vertices
      EBO(GLuint* indices, GLsizeiptr size);

    void Bind(); // Binds EBO
    void Unbind(); // Unbinds EBO so it can't be accidentally modified
    void Delete();

  };

#endif
