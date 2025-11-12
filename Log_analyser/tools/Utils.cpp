#include "Utils.h"

bool ParseTime(const std::string& datetime_str, std::tm& time_struct) {
    std::istringstream ss(datetime_str);
    ss >> std::get_time(&time_struct, "%H:%M:%S");
    return !ss.fail();
}

int StrChrBetter(const std::string& str, char chr, int n) {
    size_t counter = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == chr) counter++;
        if (counter == n) return i;
    }
    return -1;
}

int FTmToSec(const std::tm& t) {
    return t.tm_hour * 3600 + t.tm_min * 60 + t.tm_sec;
}

bool IsInDuration(const std::tm& start, const std::tm& end, const std::tm& point) {
    auto start_sec = FTmToSec(start);
    auto end_sec = FTmToSec(end);
    auto point_sec = FTmToSec(point);

    if (start_sec <= end_sec) {
        return point_sec >= start_sec && point_sec <= end_sec;
    }
    else {
        return point_sec >= start_sec || point_sec <= end_sec;
    }
}

time_t ParseDateToTimeT(const std::string& date_str) {
    std::tm time_struct = {};
    std::istringstream ss(date_str);
    ss >> std::get_time(&time_struct, "%Y:%m:%d");

    if (ss.fail()) {
        throw std::invalid_argument("Invalid date format. Expected YYYY:MM:DD");
    }

    time_struct.tm_hour = 0;
    time_struct.tm_min = 0;
    time_struct.tm_sec = 0;
    time_struct.tm_isdst = -1;

    return std::mktime(&time_struct);
}