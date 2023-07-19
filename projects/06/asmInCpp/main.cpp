#include <string>
#include <iostream>
#include <cctype>
#include <bitset>

#include "code.h"
#include "parser.h"
#include "symbolTable.h"

using namespace std;

void symbolic2machineLanguage(SymbolTable::SymbolTable &table, Code::Code code, Parser::Parser &parser, ofstream &ofstrm);
void writeSymbolTable(SymbolTable::SymbolTable &table, Parser::Parser &parser);

int main(){
    string filename = "../max/Max.asm";
    string outputFile = "../max/Max.hack";
    ofstream ofstrm(outputFile);
    Parser::Parser parserForSymbolTable(filename);
    Parser::Parser parserForMachineLanguage(filename);
    Code::Code code;
    SymbolTable::SymbolTable table;
    //由于在使用COMMAND_L时，允许先使用再定义，需要先进行一次遍历，来缓存每个(xx)标签对应的命令地址
    writeSymbolTable(table, parserForSymbolTable);
    symbolic2machineLanguage(table, code, parserForMachineLanguage, ofstrm);
    
}

void writeSymbolTable(SymbolTable::SymbolTable &table, Parser::Parser &parser){
    int instructionIdx = 0;
    while(parser.hasMoreCommands()){
        parser.advance();
        if (parser.commandType() == L_COMMAND){
            table.addInstructionEntry(parser.symbol(), instructionIdx);
        }
        if (parser.commandType() != L_COMMAND) instructionIdx++;
    }
}

void symbolic2machineLanguage(SymbolTable::SymbolTable &table, Code::Code code, Parser::Parser &parser, ofstream &ofstrm){
    while(parser.hasMoreCommands()){
        parser.advance();
        if (parser.commandType() == A_COMMAND){
            string symbol = parser.symbol();
            if (isdigit(symbol[0])){
                ofstrm << code.aCommand(symbol) << endl;;
            } else {
                if (!table.contains(parser.symbol())){
                    table.addVarEntry(symbol);    // A命令中的自定义变量在第一次遍历中并没有加入缓存；
                } 
                ofstrm << std::bitset<16>(table.GetAddress(symbol)).to_string() << endl;
            }
        } else if (parser.commandType() == C_COMMAND){
            ofstrm  << "111"
                    << code.comp(parser.comp()) 
                    << code.dest(parser.dest())
                    << code.jump(parser.jump()) << endl;
        }
    }
}
