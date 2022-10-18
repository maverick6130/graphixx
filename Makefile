OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib -L/opt/homebrew/lib
CPPFLAGS= -I/usr/local/include -I/opt/homebrew/include -I./src/include -w -std=c++17

BIN=bin/voxel_grid
SRCS=src/*.cpp
INCLUDES=src/include/*.h

all: $(BIN)


$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
