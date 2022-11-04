OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)

LDFLAGS=-L/usr/local/lib -L/opt/homebrew/lib
INCFLAGS= -I/usr/local/include -I/opt/homebrew/include -I./include 
CPPFLAGS= -w -std=c++17

RIDER= bin/a2-model-rider
BIKE= bin/a2-model-bike
TRACK= bin/a2-model-track

SRCS= src/camera/*.cpp src/heirarchy/*.cpp src/primitives/*.cpp src/renderer/*.cpp src/utils/*.cpp
INCLUDES= include/camera/*.h include/heirarchy/*.h include/primitives/*.h include/renderer/*.h include/utils/*.h
SHADERS= shader/*.glsl

all: $(RIDER) $(BIKE) $(TRACK)

$(RIDER): $(SRCS) $(INCLUDES) $(SHADERS) src/rider.cpp src/main_rider.cpp
	g++ src/rider.cpp src/main_rider.cpp $(CPPFLAGS) $(SRCS) -o $(RIDER) $(INCFLAGS) $(LDFLAGS) $(LIBS)

$(BIKE): $(SRCS) $(INCLUDES) $(SHADERS) src/bike.cpp src/main_bike.cpp
	g++ src/bike.cpp src/main_bike.cpp $(CPPFLAGS) $(SRCS) -o $(BIKE) $(INCFLAGS) $(LDFLAGS) $(LIBS)

$(TRACK): $(SRCS) $(INCLUDES) $(SHADERS) src/rider.cpp src/bike.cpp src/track.cpp src/main_all.cpp
	g++ src/rider.cpp src/bike.cpp src/track.cpp src/main_all.cpp $(CPPFLAGS) $(SRCS) -o $(TRACK) $(INCFLAGS) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(RIDER) $(BIKE) $(TRACK)
