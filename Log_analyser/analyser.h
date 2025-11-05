#pragma once 
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

enum codes_messages
{
	INFO, DEBUG, WARNING, ERROR, FATAL
};

class Message
{
private:
	std::tm time;
	codes_messages code;
	std::string nameModule;
	std::string data;

	std::string raw_line;
	
	void parse_time();
	void parse_code();
	void parse_modulename();
	void parse_data();
	

public:
	Message() = delete;
	Message(const std::string& lineofLog);
	~Message() {};

	std::tm get_time()const { return time; };
	codes_messages get_code()const { return code; };
	std::string get_namemodule()const { return nameModule; };
	std::string get_data()const { return data; };
	std::string get_rawdata()const { return raw_line; };
};


class File
{
private:
	std::vector<Message> msgs;
	std::string filename;

public:
	
	File() = delete;
	File(const std::string& filename);
	~File() {};

	std::string get_badstat()const;
	std::string get_findtime(const std::tm& timestart, const std::tm& timeend)const;
	std::string get_findstr(const std::string& str)const;
	std::string get_findmodule(const std::string& str)const;
	std::string get_findtype(codes_messages code)const;




};


class LogHandler
{
private:
	std::vector<File> files;
	std::string DirName;
	
public:
	LogHandler() = delete;
	LogHandler(std::string dirname) {};
	~LogHandler() {};

	void get_stat() {};
	void find_time(std::tm time) {};
	void find_str(std::string str) {};
	void write_last_result(std::string filename) {};

};