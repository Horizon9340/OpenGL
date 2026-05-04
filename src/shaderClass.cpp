#include "shaderClass.h"

// Reads a text file and converts it into a single string
std::string get_file_contents(const char* filename)
{
  std::ifstream in(filename, std::ios::binary);
  if (in)
  {
    std::string contents;

    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);

    in.read(&contents[0], contents.size());
    in.close();

    return(contents);
  }
  throw(errno);
}

// Compiles the two source code files into a usable shader object
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
  // Read the text files and store the strings
  std::string vertexCode = get_file_contents(vertexFile);
  std::string fragmentCode = get_file_contents(fragmentFile);

  // Convert the strings into character arrays
  const char* vertexSource = vertexCode.c_str();
  const char* fragmentSource = fragmentCode.c_str();

  // Create vertex shader and get reference
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // Attach vertex shader source to the vertex shader object
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  // Compile into machine code
  glCompileShader(vertexShader);
  compileErrors(vertexShader, "VERTEX");

  // Create fragment shader object and get reference
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // Attach fragment shader source to the fragment shader object
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  // Compile into machine code
  glCompileShader(fragmentShader);
  compileErrors(fragmentShader, "FRAGMENT");

  // Create shader program and get its reference
  ID = glCreateProgram();
  // Attach the vertex and fragment shaders the shader program
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  // Link all the shaders together in the shader program
  glLinkProgram(ID);
  compileErrors(ID, "PROGRAM");

  // Delete the now useless shader objects
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
  glUseProgram(ID);
}

void Shader::Delete()
{
  glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
  GLint hasCompiled;
  char infoLog[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cerr << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
    }
  }
  else
  {
    glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cerr << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
    }
  }
}