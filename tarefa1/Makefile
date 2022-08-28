ALL: main

main: main.o pixels.o matrix.o
	g++ main.o pixels.o matrix.o `sdl2-config --cflags --libs` -o main

main.o: main.cpp
	g++ -c main.cpp -o main.o

pixels.o: pixels.cpp pixels.h
	g++ -c pixels.cpp -o pixels.o

matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp -o matrix.o

clean:
	rm -rf main *.o