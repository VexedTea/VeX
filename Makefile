# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean run build

CC = g++.exe

LINKERFLAG = -lm

CFLAGS = -std=c++17 -Wall -Werror -Wextra -pedantic -O1
FLAGS = -DSFML_STATIC -IC:\\Users\\rick2\\OneDrive\\Code\\SFML\\SFML-2.5.1\\include -LC:\\Users\\rick2\\OneDrive\\Code\\SFML\\SFML-2.5.1\\lib -L -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-network-s -lsfml-audio-s -static-libgcc -static-libstdc++ -static -lws2_32 -lfreetype -lwinpthread -lopengl32 -lgdi32 -lwinmm -lgdi32 -lstdc++fs

SRCS := $(wildcard c/*.cpp)
OBJECTS := $(SRCS:c/%.cpp=o/%.o)

all: VeX

build: VeX

run: VeX
	VeX.exe

VeX: $(OBJECTS)
	@echo "Linking.."
	${CC} $(CFLAGS) ${LINKERFLAG} $(OBJECTS) -o $@ $(FLAGS)

o/%.o: c/%.cpp
	@echo "Creating object.."
	${CC} $(CFLAGS) -c $< -o $@ $(FLAGS)

clean:
	@echo "Cleaning up..."
	del "o\*.o" 
# the 'del' probably needs to be changed for linux users. This was made for a windows system.