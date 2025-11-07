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

static bool is_endbiggerstart(const std::tm& timestart, const std::tm& timeend)
{
	if (timestart.tm_hour < timeend.tm_hour)return true;
	if (timestart.tm_hour > timeend.tm_hour)return false;
	if (timestart.tm_min < timeend.tm_min)return true;
	if (timestart.tm_min > timeend.tm_min)return false;
	if (timestart.tm_sec < timeend.tm_sec)return true;
	if (timestart.tm_sec > timeend.tm_sec)return false;
	return false;
}


static bool is_in_duration(std::tm timestart, std::tm timeend, const std::tm& time_point)
{

	bool flag = false;
	bool flag_in_dur = false;
	if (!is_endbiggerstart(timestart, timeend))
	{
		flag = true;
		std::tm temp = timeend;
		timeend = timestart;
		timestart = temp;
	}

	if (is_endbiggerstart(timestart, time_point) && is_endbiggerstart(time_point, timeend))flag_in_dur = true;
	//if (flag_in_dur && !flag)return true;
	//if (!flag_in_dur && flag)return true;
	//return false;
	return flag_in_dur ^ flag;
}

std::string File::get_findtime(const std::tm& timestart, const std::tm& timeend)const
{

	std::stringstream stat;
	stat << "In file " << filename << std::endl;
	for (int i = 0; i < msgs.size(); i++)
	{
		std::tm tmp = msgs[i].get_time();
		if (is_in_duration(timestart,timeend,tmp))
		{
			stat << msgs[i].get_rawdata()<<std::endl;
		}

	}
	return stat.str();

}


std::string File::get_findstr(const std::string& str)const
{
	std::stringstream stat;
	stat << "In file " << filename << std::endl;
	for (int i = 0; i < msgs.size(); i++)
	{
		std::string tmp = msgs[i].get_data();
		if (tmp.find(str)!=std::string::npos) {
			stat << msgs[i].get_rawdata() << std::endl;
		}
	}
	return stat.str();
}

std::string File::get_findtype(codes_messages code)const
{
	std::stringstream stat;
	stat << "In file " << filename << std::endl;
	for (int i = 0; i < msgs.size(); i++)
	{
		codes_messages tmp = msgs[i].get_code();
		if (tmp == code) {
			stat << msgs[i].get_rawdata() << std::endl;
		}
	}
	return stat.str();
}

std::string File::get_findmodule(const std::string& str)const
{
	std::stringstream stat;
	stat << "In file " << filename << std::endl;
	for (int i = 0; i < msgs.size(); i++)
	{
		std::string tmp = msgs[i].get_namemodule();
		if (tmp == str) {
			stat << msgs[i].get_rawdata() << std::endl;
		}
	}
	return stat.str();
}


LogHandler::LogHandler(std::string dirname)
{
	for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
		if (entry.is_regular_file())
		{
			File ff(entry.path().string());
			files.push_back(ff);
		}
	}
}

void LogHandler::get_stat()
{
	std::stringstream ss;
	for (int i = 0; i < files.size(); i++)
	{
		ss << files[i].get_badstat() << std::endl;
	}
	LastResult = ss.str();
	std::cout << ss.str();
}



void LogHandler::findbytime(const std::tm& timestart, const std::tm& timeend)
{
	std::stringstream ss;
	for (int i = 0; i < files.size(); i++)
	{
		ss << files[i].get_findtime(timestart,timeend) << std::endl;
	}
	LastResult = ss.str();
	std::cout << ss.str();
}


void LogHandler::findbystr(const std::string& str)
{
	std::stringstream ss;
	for (int i = 0; i < files.size(); i++)
	{
		ss << files[i].get_findstr(str) << std::endl;
	}
	LastResult = ss.str();
	std::cout << ss.str();
}


void LogHandler::findbymodule(const std::string& str)
{
	std::stringstream ss;
	for (int i = 0; i < files.size(); i++)
	{
		ss << files[i].get_findmodule(str) << std::endl;
	}
	LastResult = ss.str();
	std::cout << ss.str();
}


void LogHandler::findbytype(codes_messages code)
{
	std::stringstream ss;
	for (int i = 0; i < files.size(); i++)
	{
		ss << files[i].get_findtype(code) << std::endl;
	}
	LastResult = ss.str();
	std::cout << ss.str();
}


void LogHandler::write_last_result(std::string filename)
{
	std::ofstream fs(filename);
	fs << LastResult;
	fs.close();
}