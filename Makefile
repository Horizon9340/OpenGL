CXX = clang++
CXXFLAGS = -Iglad -Iheaders -I/opt/homebrew/opt/glfw/include -std=c++17
LDFLAGS = -L/opt/homebrew/opt/glfw/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

SOURCES = \
src/main.cpp \
src/shaderClass.cpp \
src/VAO.cpp src/VBO.cpp \
src/EBO.cpp \
glad/src/glad.c

TARGET = program

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
