#include<algorithm>

#include "parser.h"

namespace Parser
{
    Parser::Parser(std::string file): fstrm(file){}
    bool Parser::hasMoreCommands(){
        return fstrm.is_open();
    }
    void Parser::advance(){
        while(1){
            if (std::getline(fstrm, instruction)) {
                if (instruction.substr(0, 2) == "//") continue;
                int tmp = 0;
                while(instruction.size() && instruction.front() == ' ') ++tmp;
                if (tmp == instruction.size()) continue;
                else {
                    instruction = instruction.substr(tmp, instruction.size()-tmp);
                    lineId++;
                }
            } else {
                fstrm.close();
            }
        }
    }
    int Parser::commandType(){
        if (instruction[0] == '@') return A_COMMAND;
        else if (instruction[0] == '(') return L_COMMAND;
        else return C_COMMAND;
    }
    std::string Parser::symbol(){
        return instruction.substr(1, instruction.size()-1);
    }
    std::string Parser::dest(){
        auto eqIdx = find(instruction.begin(), instruction.end(), '=');
        return std::string(instruction.begin(), eqIdx);
    }
    std::string Parser::comp(){
        auto eqIdx = find(instruction.begin(), instruction.end(), '=');
        auto questionIdx = find(instruction.begin(), instruction.end(), '?');
        return std::string(eqIdx+1, questionIdx);
    }
    std::string Parser::jump(){
        auto questionIdx = find(instruction.begin(), instruction.end(), '?');
        return std::string(questionIdx, instruction.end());
    }
} // namespace Parser

 

