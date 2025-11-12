#pragma once

#include "LogFile.h"
#include "../tools/CmdParser.h"

class LogHandler {
private:
	std::vector<File> files_;
	std::string dir_name_;
	std::ofstream output_;
	bool file_output_;
	bool flag_stat_;
	bool flag_filter_;

	void EachFileFilterModule(const std::string& module_name);
	void EachFileFilterTime(const std::tm& time_start, const std::tm& time_end);
	void EachFileFilterStr(const std::string& str);
	void EachFileFilterType(const std::vector<CodesMessages>& codes);
	void SortByTime();
	void FilterByTime(time_t start_time, time_t end_time);

public:
	LogHandler() = delete;
	LogHandler(std::string dirname);
	~LogHandler() = default;

	void ApplyArgs(int argc, char** argv);
	void PrintResult();
};