#pragma once

#include "LogMessage.h"

class File {
private:
    std::vector<Message> messages_;
    std::string filename_;
    time_t time_;

    void CalcTime();

public:
    bool operator<(const File& other) const {
        return time_ < other.time_;
    }

    File(const std::string& filename);
    ~File() = default;

    void FilterModule(const std::string& module_name);
    void FilterTime(const std::tm& time_start, const std::tm& time_end);
    void FilterString(const std::string& str);
    void FilterType(const std::vector<CodesMessages>& codes);

    std::string GetBadStat() const;
    std::string GetMessages() const;

    time_t get_time() const { return time_; }
    std::vector<Message>& get_vec_msg() { return messages_; }
};