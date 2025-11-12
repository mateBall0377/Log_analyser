#pragma once

#include "../tools/Utils.h"
#include "LogConstants.h"

class Message {
private:
	std::tm time_;	
	CodesMessages code_;
	std::string name_module_;
	std::string data_;
	std::string raw_line_;

	void ParseTime();
	void ParseCode();
	void ParseModuleName();
	void ParseData();

public:
	Message() = delete;
	Message(const std::string& line_of_log);
	~Message() = default;

	std::tm get_time() const { return time_; }
	CodesMessages get_code() const { return code_; }
	std::string get_name_module() const { return name_module_; }
	std::string get_data() const { return data_; }
	std::string get_raw_data() const { return raw_line_; }
};