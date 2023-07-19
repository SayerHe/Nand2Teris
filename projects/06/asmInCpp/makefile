build/main: build/main.o build/parser.o build/code.o build/symbolTable.o
	g++ build/main.o build/parser.o build/code.o build/symbolTable.o -o build/main 

build/parser.o: parser.cpp
	g++ -c parser.cpp -o build/parser.o 
build/symbolTable.o: symbolTable.cpp
	g++ -c symbolTable.cpp -o build/symbolTable.o 
build/code.o: code.cpp
	g++ -c code.cpp -o build/code.o
build/main.o: main.cpp
	g++ -c main.cpp -o build/main.o 

clean:
	rm -rf ./build/*

# makefile写的跟shit一样；；；；；；；