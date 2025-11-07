#include "Log_analyser.h"



int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Need dir path";
        return 1;
    }
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string dirname = argv[1];

    try {
        LogHandler handler(dirname);
        if (argc == 2)interactive_mode(handler);
        else console_mode(handler, argc, argv);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}