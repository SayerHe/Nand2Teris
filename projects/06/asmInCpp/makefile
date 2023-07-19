build/main: build/main.o build/parser.o
	g++ build/main.o build/parser.o -o build/main 

build/parser.o: parser.cpp
	g++ -c parser.cpp -o build/parser.o 
build/main.o: main.cpp
	g++ -c main.cpp -o build/main.o 

clean:
	rm -rf ./build/*