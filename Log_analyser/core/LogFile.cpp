#include "LogFile.h"

void File::CalcTime() {
    std::string clear_filename = std::filesystem::path(filename_).filename().string();
    std::tm time_struct = {}; 

    int start_date = StrChrBetter(clear_filename, '_', 1) + 1;
    int end_date = StrChrBetter(clear_filename, '_', 2);
    int end_time = StrChrBetter(clear_filename, '.', 1);

    std::string date = clear_filename.substr(start_date, end_date - start_date);
    std::string time_f = clear_filename.substr(end_date + 1, end_time - end_date - 1);

    time_struct.tm_hour = std::stoi(time_f.substr(0, 2));
    time_struct.tm_min = std::stoi(time_f.substr(2, 2));
    time_struct.tm_sec = std::stoi(time_f.substr(4, 2));

    time_struct.tm_year = std::stoi(date.substr(0, 4)) - 1900;
    time_struct.tm_mon = std::stoi(date.substr(4, 2)) - 1;    
    time_struct.tm_mday = std::stoi(date.substr(6, 2));

    time_struct.tm_isdst = -1;
    time_ = mktime(&time_struct);
}

File::File(const std::string& filename) : filename_(filename) {
    std::ifstream file_stream(filename);

    if (!file_stream.is_open()) throw std::runtime_error("file_open error");

    std::string buffer;
    while (std::getline(file_stream, buffer)) {
        Message line(buffer);
        messages_.push_back(line);
    }
    CalcTime();
}

std::string File::GetBadStat() const {
    std::stringstream stat;
    int count_warnings = 0;
    int count_fatal = 0;
    int count_error = 0;

    for (size_t i = 0; i < messages_.size(); i++) {
        switch (messages_[i].get_code()) {
        case kWarning: count_warnings++; break;
        case kError: count_error++; break;
        case kFatal: count_fatal++; break;
        }
    }

    stat << "In file " << filename_ << std::endl
        << " WARNING: " << count_warnings << std::endl
        << " FATAL: " << count_fatal << std::endl
        << " ERROR: " << count_error << std::endl;
    return stat.str();
}

std::string File::GetMessages() const {
    std::stringstream ss;
    ss << "In file " << filename_ << std::endl;

    for (size_t i = 0; i < messages_.size(); i++) {
        ss << messages_[i].get_raw_data() << std::endl;
    }
    return ss.str();
}

void File::FilterModule(const std::string& module_name) {
    for (size_t i = 0; i < messages_.size(); i++) {
        if (messages_[i].get_name_module() != module_name) {
            messages_.erase(messages_.begin() + i);
            i--;
        }
    }
}

void File::FilterTime(const std::tm& time_start, const std::tm& time_end) {
    for (size_t i = 0; i < messages_.size(); i++) {
        std::tm tmp = messages_[i].get_time();
        if (!IsInDuration(time_start, time_end, tmp)) {
            messages_.erase(messages_.begin() + i);
            i--;
        }
    }
}

void File::FilterString(const std::string& str) {
    for (size_t i = 0; i < messages_.size(); i++) {
        std::string tmp = messages_[i].get_data();
        if (tmp.find(str) == std::string::npos) {
            messages_.erase(messages_.begin() + i);
            i--;
        }
    }
}

void File::FilterType(const std::vector<CodesMessages>& codes) {
    for (size_t i = 0; i < messages_.size(); ) {
        bool found = false;
        for (auto code : codes) {
            if (messages_[i].get_code() == code) {
                found = true;
                break;
            }
        }

        if (!found) {
            messages_.erase(messages_.begin() + i);
        }
        else {
            i++;
        }
    }
}