#include "analyser.h"

static int strchrbetter(std::string str, char chr, int n)
{
	int counter = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == chr)counter++;
		if (counter == n)return i;
	}
	return -1;
}

Message::Message(const std::string& lineofLog):raw_line(lineofLog)
{
	parse_time();
	parse_code();
	parse_modulename();
	parse_data();
}

void Message::parse_time()
{
	time.tm_hour = std::stoi(raw_line.substr(0, 2));
	time.tm_min = std::stoi(raw_line.substr(3, 5));
	time.tm_sec = std::stoi(raw_line.substr(6, 8));
}

void Message::parse_code()
{
	if (raw_line[10] == 'I')code = INFO;
	if (raw_line[10] == 'D')code = DEBUG;
	if (raw_line[10] == 'W')code = WARNING;
	if (raw_line[10] == 'E')code = ERROR;
	if (raw_line[10] == 'F')code = FATAL;
}

void Message::parse_modulename()
{
	int start = strchrbetter(raw_line, '[', 2);
	int end = strchrbetter(raw_line, ']', 2);
	nameModule = raw_line.substr(start+1,end-start-1 );
}


void Message::parse_data()
{
	int end = strchrbetter(raw_line, ']', 2);
	data = raw_line.substr(end+2);
}


File::File(const std::string& filename):filename(filename)
{
	std::ifstream ff(filename);

	if (!ff.is_open())throw std::runtime_error("file_open error");
	std::string buffer;
	while (std::getline(ff, buffer))
	{
		
		Message line(buffer);
		msgs.push_back(line);
	}
}

std::string File::get_badstat()const
{
	std::stringstream stat;
	int countwarnings = 0;
	int countfatal = 0;
	int counterror = 0;
	for (int i= 0; i < msgs.size(); i++)
	{
		if (msgs[i].get_code() == WARNING) countwarnings++;
		if (msgs[i].get_code() == ERROR) counterror++;
		if (msgs[i].get_code() == FATAL) countfatal++;

	}

	stat << "In file " << filename << std::endl;
	stat << " WARNING: " << countwarnings << std::endl;
	stat << " FATAL: " << countfatal << std::endl;
	stat << " ERROR: " << counterror << std::endl;
	return stat.str();
}


std::string File::get_findtime(const std::tm& timestart, const std::tm& timeend)const
{

	std::stringstream stat;/*
	stat << "In file " << filename << std::endl;
	for (int i = 0; i < msgs.size(); i++)
	{
		std::tm tmp = msgs[i].get_time();
		if (tmp.tm_sec == time.tm_sec && tmp.tm_min == time.tm_min && tmp.tm_hour == time.tm_hour)
		{
			stat << msgs[i].get_rawdata()<<std::endl;
		}

	}*/
	return stat.str();

}


std::string File::get_findstr(const std::string& str)const
{

}