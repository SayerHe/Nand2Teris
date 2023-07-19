#include<string>
#include<fstream>

#define A_COMMAND 0
#define C_COMMAND 1
#define L_COMMAND 2

namespace Parser{
    class Parser{
        public:
            Parser() = default;
            Parser(std::string file);
            bool hasMoreCommands();
            void advance();
            int commandType();
            std::string symbol();
            std::string dest();
            std::string comp();
            std::string jump();

        private:
            std::fstream fstrm;
            int lineId = 0;
            std::string instruction;
};
}
