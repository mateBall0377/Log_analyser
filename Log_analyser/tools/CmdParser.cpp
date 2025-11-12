#include "CmdParser.h"

CliArgsParser::CliArgsParser(int argc, char** argv)
    : argc_(argc), argv_(argv) {
}

bool CliArgsParser::IsFlagExist(const std::string& flag) const {
    for (int i = 1; i < argc_; i++) {
        if (std::string(argv_[i]) == flag) {
            return true;
        }
    }
    return false;
}

std::string CliArgsParser::GetValueFlag(const std::string& flag) const {
    for (int i = 1; i < argc_ - 1; i++) {
        if (std::string(argv_[i]) == flag) {
            return std::string(argv_[i + 1]);
        }
    }
    return "";
}