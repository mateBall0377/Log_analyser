#pragma once

#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

bool ParseTime(const std::string& datetime_str, std::tm& time_struct);
int StrChrBetter(const std::string& str, char chr, int n);
bool IsInDuration(const std::tm& start, const std::tm& end, const std::tm& point);
int FTmToSec(const std::tm& t);
time_t ParseDateToTimeT(const std::string& date_str);