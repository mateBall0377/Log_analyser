#pragma once
#include "utils.h"
#include <string>
#include <vector>

class CliArgsParser {
public:
	CliArgsParser(int argc, char** argv);
	~CliArgsParser() = default;

	bool IsFlagExist(const std::string& flag) const;
	std::string GetValueFlag(const std::string& flag) const;

private:
	int argc_;
	char** argv_;
};