#pragma once
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

bool parse_time(const std::string& datetime_str, std::tm& time_struct);
