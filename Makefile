# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = soheaderscancompile all clean run build

CC = g++.exe

LINKERFLAG = -lm

CFLAGS = -std=c++17 -Wall -Werror -Wextra -pedantic -O1
FLAGS = -DSFML_STATIC -IC:\\Users\\rick2\\OneDrive\\Code\\SFML\\SFML-2.5.1\\include -LC:\\Users\\rick2\\OneDrive\\Code\\SFML\\SFML-2.5.1\\lib -L -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-network-s -lsfml-audio-s -static-libgcc -static-libstdc++ -static -lws2_32 -lfreetype -lwinpthread -lopengl32 -lgdi32 -lwinmm -lgdi32 -lstdc++fs
RELEASE =

SRCS := $(wildcard c/*.cpp)
SRCS += $(wildcard c/*/*.cpp)
OBJECTS := $(SRCS:c/%.cpp=o/%.o)

all: VeX

build: VeX

run: VeX
	VeX.exe

VeX: soheaderscancompile $(OBJECTS) 
	@echo "Linking.."
	${CC} $(CFLAGS) ${LINKERFLAG} $(OBJECTS) -o $@ $(FLAGS) $(RELEASE)

o/%.o: c/%.cpp
	@echo "Creating object.."
	${CC} $(CFLAGS) -c $< -o $@ $(FLAGS)

soheaderscancompile:
	del "o\VeX.o"

clean:
	@echo "Cleaning up..."
	del "o\*.o" 
	del "o\ui\*.o" 
	del "o\demo\*.o" 
	del "o\verlet\*.o" 
# the 'del' probably needs to be changed for linux users. This was made for a windows system.