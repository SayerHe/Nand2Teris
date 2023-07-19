#include "symbolTable.h"

namespace SymbolTable
{
    void SymbolTable::addInstructionEntry(std::string symbol, int address){
        table[symbol] = address;
    }
    void SymbolTable::addVarEntry(std::string symbol){
        table[symbol] = nextVarAddr;
        nextVarAddr++;
    }
    bool SymbolTable::contains(std::string symbol){
        return !(table.find(symbol) == table.end());
    }
    int SymbolTable::GetAddress(std::string symbol){
        return table.at(symbol);
    }
} // namespace symbolTble
