#include "common.h"


bool parse_time(const std::string& datetime_str, std::tm& time_struct)
{
    std::istringstream ss(datetime_str);
    ss >> std::get_time(&time_struct, "%H:%M:%S");
    return !ss.fail();
}
