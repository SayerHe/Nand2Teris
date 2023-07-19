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
            // 去除行内注释和左右空格
            instruction = strip(std::string(currentLine.begin(), find(currentLine.begin(), currentLine.end(), '/')));
            lineId ++;
        }
    }
    int Parser::commandType(){
        if (instruction[0] == '@') return A_COMMAND;
        else if (instruction[0] == '(') return L_COMMAND;
        else return C_COMMAND;
    }
    std::string Parser::strip(std::string str){
        int left=0, right=str.size()-1;
        while(str[left] == ' ') ++left;
        while(str[right] == ' ') --right;
        return str.substr(left, right-left+1);
    }
    // 每个部分都可能含有冗余空格，需要去除
    std::string Parser::symbol(){
        if (commandType() == A_COMMAND){
            return strip(instruction.substr(1, instruction.size()-1));
        } else if (commandType() == L_COMMAND){
            return strip(instruction.substr(1, instruction.size()-2));
        } else return "";
    }
    // A = A+D; JMP
    std::string Parser::dest(){
        auto eqIdx = find(instruction.begin(), instruction.end(), '=');
        if (eqIdx == instruction.end()) return "";
        else return commandType() == C_COMMAND ? strip(std::string(instruction.begin(), eqIdx)) : "";
    }
    std::string Parser::comp(){
        auto eqIdx = find(instruction.begin(), instruction.end(), '=');
        auto questionIdx = find(instruction.begin(), instruction.end(), ';');
        if (eqIdx == instruction.end()) return strip(std::string(instruction.begin(), questionIdx));
        else return strip(std::string(eqIdx+1, questionIdx));
    }
    std::string Parser::jump(){
        auto questionIdx = find(instruction.begin(), instruction.end(), ';') == instruction.end()\
                        ? instruction.end(): find(instruction.begin(), instruction.end(), ';')+1;
        return commandType() == C_COMMAND ? strip(std::string(questionIdx, instruction.end())) : "";
    }
} // namespace Parser

 

