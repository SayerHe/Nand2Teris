#include <string>
#include <iostream>

#include "code.h"
#include "parser.h"

using namespace std;
int main(){
    string filename = "../add/Add.asm";
    string outputFile = "../add/Add.hack";
    ofstream ofstrm(outputFile);
    Parser::Parser parser(filename);
    Code::Code code;
    while(parser.hasMoreCommands()){
        parser.advance();
        if (parser.commandType() == 0){
            ofstrm << code.aCommand(parser.symbol()) << endl;;
        } else if (parser.commandType() == 1){
            ofstrm  << "111"
                    << code.comp(parser.comp()) 
                    << code.dest(parser.dest())
                    << code.jump(parser.jump()) << endl;
        }
    }
}