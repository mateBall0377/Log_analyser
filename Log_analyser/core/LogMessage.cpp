#include "LogMessage.h"

Message::Message(const std::string& line_of_log) : raw_line_(line_of_log) {
    ParseTime();
    ParseCode();
    ParseModuleName();
    ParseData();
}

void Message::ParseTime() {
    time_.tm_hour = std::stoi(raw_line_.substr(0, 2));
    time_.tm_min = std::stoi(raw_line_.substr(3, 2));
    time_.tm_sec = std::stoi(raw_line_.substr(6, 2));
}

void Message::ParseCode() {
    switch (raw_line_[10]) {
    case 'I': code_ = kInfo; break;
    case 'D': code_ = kDebug; break;
    case 'W': code_ = kWarning; break;
    case 'E': code_ = kError; break;
    case 'F': code_ = kFatal; break;
    }
}

void Message::ParseModuleName() {
    int start = StrChrBetter(raw_line_, '[', 2);
    int end = StrChrBetter(raw_line_, ']', 2);
    name_module_ = raw_line_.substr(start + 1, end - start - 1);
}

void Message::ParseData() {
    int end = StrChrBetter(raw_line_, ']', 2);
    data_ = raw_line_.substr(end + 2);
}