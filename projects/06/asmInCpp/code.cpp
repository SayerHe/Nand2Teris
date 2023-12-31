#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <bitset>

#include "code.h"
namespace Code
{
    std::string Code::dest(std::string str){
        std::string ret = "";
        if (str.empty()) return "000";
        if (find(str.begin(), str.end(), 'A') == str.end()) ret += '0';
        else ret += '1';
        if (find(str.begin(), str.end(), 'D') == str.end()) ret += '0';
        else ret += '1';
        if (find(str.begin(), str.end(), 'M') == str.end()) ret += '0';
        else ret += '1';
        return ret;
    }
    std::string Code::comp(std::string str){
        if (str == "0") return "0101010";
        else if (str == "1") return "0111111";
        else if (str == "-1") return "0111010";
        else if (str == "D") return "0001100";
        else if (str == "!D") return "0001101";
        else if (str == "-D") return "0001111";
        else if (str == "D+1") return "0011111";
        else if (str == "D-1") return "0001110";
        else if (str == "A") return "0110000";
        else if (str == "M") return "1110000";
        else if (str == "!A") return "0110001";
        else if (str == "!M") return "1110001";
        else if (str == "-A") return "0110011";
        else if (str == "-M") return "1110011";
        else if (str == "A+1") return "0110111";
        else if (str == "M+1") return "1110111";
        else if (str == "A-1") return "0110010";
        else if (str == "M-1") return "1110010";
        else if (str == "D+A") return "0000010";
        else if (str == "D+M") return "1000010";
        else if (str == "D-A") return "0010011";
        else if (str == "D-M") return "1010011";
        else if (str == "A-D") return "0000111";
        else if (str == "M-D") return "1000111";
        else if (str == "D&A") return "0000000";
        else if (str == "D&M") return "1000000";
        else if (str == "D|A") return "0010101";
        else if (str == "D|M") return "1010101";
        else {
            std::cout << str << std::endl;
            return "-1";
        }
    }
    std::string Code::jump(std::string str){
        if (str.empty()) return "000";
        else if (str == "JGT") return "001";
        else if (str == "JEQ") return "010";
        else if (str == "JGE") return "011";
        else if (str == "JLT") return "100";
        else if (str == "JNE") return "101";
        else if (str == "JLE") return "110";
        else if (str == "JMP") return "111";
        else return "-1";
    }
    std::string Code::aCommand(std::string str){
        std::stringstream ss(str);
        int address;
        ss >> address;
        return std::bitset<16>(address).to_string();
    }
} // namespace Code
