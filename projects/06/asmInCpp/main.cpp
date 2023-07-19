#include <string>
#include <iostream>
#include "parser.h"


int main(){
    std::string filename = "../add/add.asm";
    Parser::Parser parser(filename);
    while(parser.hasMoreCommands()){
        std::cout << parser.dest() << parser.comp() << parser.jump() << std::endl;
    }
}