#include <algorithm>
#include <iostream>

#include "parser.h"

namespace Parser
{
    Parser::Parser(std::string file): fstrm(file){}

    //为了防止最后有空行或者注释，每次调用hasMoreCommand时，fstrm会继续向后读取；
    //读取的string会存在current里，并更新openFlag，advance根据openFlag的状态更新instruction
    bool Parser::hasMoreCommands(){
        if (openFlag == -1 && fstrm.fail()) return false;
        auto uselessInstruction = [](std::string instruction)->bool{
            if (instruction.substr(0, 2) == "//") return true;
            while(instruction.size() && isspace(instruction.back())) instruction.pop_back();
            return instruction.size() == 0;
        };
        while (std::getline(fstrm, currentLine) && uselessInstruction(currentLine));
        openFlag = !fstrm.eof();
        return openFlag;
    }

    void Parser::advance(){
        if(openFlag){
            instruction = currentLine;
            lineId ++;
        }
    }
    int Parser::commandType(){
        if (instruction[0] == '@') return A_COMMAND;
        else if (instruction[0] == '(') return L_COMMAND;
        else return C_COMMAND;
    }
    std::string Parser::symbol(){
        return commandType() == 0 ? instruction.substr(1, instruction.size()-1) : "";
    }
    // A = A+D; JMP
    std::string Parser::dest(){
        auto eqIdx = find(instruction.begin(), instruction.end(), '=');
        if (eqIdx == instruction.end()) return "";
        else return commandType() == 1 ? std::string(instruction.begin(), eqIdx) : "";
    }
    std::string Parser::comp(){
        auto eqIdx = find(instruction.begin(), instruction.end(), '=');
        auto questionIdx = find(instruction.begin(), instruction.end(), ';');
        if (eqIdx == instruction.end()) return std::string(instruction.begin(), questionIdx);
        else return std::string(eqIdx+1, questionIdx);
    }
    std::string Parser::jump(){
        auto questionIdx = find(instruction.begin(), instruction.end(), ';') == instruction.end()\
                        ? instruction.end(): find(instruction.begin(), instruction.end(), ';')+1;
        return commandType() == 1 ? std::string(questionIdx, instruction.end()) : "";
    }
} // namespace Parser

 

