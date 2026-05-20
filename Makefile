CXX = clang++
CXXFLAGS = -Iheaders -I/opt/homebrew/include -Iexternal/glad -std=c++17
LDFLAGS = -L/opt/homebrew/opt/glfw/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

SOURCES = \
src/main.cpp \
src/shaderClass.cpp \
src/VAO.cpp src/VBO.cpp \
src/EBO.cpp \
src/camera.cpp \
external/glad/src/glad.c

TARGET = program

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
