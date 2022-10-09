COMPILER=g++
LIB=$(wildcard ./lib/*.cpp)
INCLUDE=$(wildcard ./include/*.h)
ELF=$(patsubst ./lib/%.cpp, ./build/%.o, $(LIB))
SDL_FLAGS=`sdl2-config --cflags --libs` -lSDL2_image
COMPILER_FLAGS=-Wall -Wextra -pedantic

ALL: main

main: build/main.o $(ELF)
	$(COMPILER) $^ $(SDL_FLAGS) -o $@

build/main.o: main.cpp $(INCLUDE)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

build/%.o: lib/%.cpp include/%.h
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

clean:
	rm -rf main build/*