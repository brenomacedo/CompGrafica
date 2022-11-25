COMPILER=g++
LIB=$(wildcard ./lib/*.cpp)
INCLUDE=$(wildcard ./include/*.h)
ELF=$(patsubst ./lib/%.cpp, ./build/%.o, $(LIB))
SDL_FLAGS=-lSDL2main -lSDL2 -lSDL2_image
COMPILER_FLAGS=-Wall -Wextra -pedantic -Isrc/include -Lsrc/lib -lmingw32

ALL: main

main: build/main.o $(ELF)
	$(COMPILER) $^ $(COMPILER_FLAGS) $(SDL_FLAGS) -o $@

build/main.o: main.cpp $(INCLUDE)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

build/%.o: lib/%.cpp include/%.h
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

clean:
	rm -rf main build/*