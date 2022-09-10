COMPILER=g++
LIB=$(wildcard ./lib/*.cpp)
INCLUDE=$(wildcard ./include/*.h)
ELF=$(patsubst ./lib/%.cpp, ./build/%.o, $(LIB))
FLAGS=`sdl2-config --cflags --libs` -lSDL2_image

ALL: main

main: build/main.o $(ELF)
	$(COMPILER) $^ $(FLAGS) -o $@

build/main.o: main.cpp $(INCLUDE)
	$(COMPILER) -c $< -o $@

build/%.o: lib/%.cpp include/%.h
	$(COMPILER) -c $< -o $@

clean:
	rm -rf main build/*