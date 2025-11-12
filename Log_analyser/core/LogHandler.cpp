#include "LogHandler.h"

LogHandler::LogHandler(std::string dirname) {
    for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
        if (entry.is_regular_file()) {
            File ff(entry.path().string());
            files_.push_back(ff);
        }
    }
    flag_stat_ = false;
    flag_filter_ = false;
    file_output_ = false;
}

void LogHandler::SortByTime() {
    std::sort(files_.begin(), files_.end());
}

void LogHandler::ApplyArgs(int argc, char** argv) {
    CliArgsParser args(argc, argv);

    if (args.IsFlagExist(kFlagOut)) {
        file_output_ = true;
        output_.open(args.GetValueFlag(kFlagOut));
    }
    if (args.IsFlagExist(kFlagStat)) {
        flag_stat_ = true;
    }

    if (args.IsFlagExist(kFlagModule)) {
        EachFileFilterModule(args.GetValueFlag(kFlagModule));
    }
    if (args.IsFlagExist(kFlagStr)) {
        EachFileFilterStr(args.GetValueFlag(kFlagStr));
    }
    if (args.IsFlagExist(kFlagType)) {
        std::vector<CodesMessages> codes;
        for (char c : args.GetValueFlag(kFlagType)) {
            codes.push_back(static_cast<CodesMessages>(c - '0'));
        }
        EachFileFilterType(codes);
    }
    if (args.IsFlagExist(kFlagMaxTime) && args.IsFlagExist(kFlagMinTime)) {
        std::string start_str = args.GetValueFlag(kFlagMinTime);
        std::string end_str = args.GetValueFlag(kFlagMaxTime);
        std::tm start_time = {};
        std::tm end_time = {};
        if (ParseTime(start_str, start_time) && ParseTime(end_str, end_time)) {
            EachFileFilterTime(start_time, end_time);
        }
        else {
            throw std::underflow_error("Error in time format\n");
        }
    }
    if (args.IsFlagExist(kFlagMaxTime) ^ args.IsFlagExist(kFlagMinTime)) {
        throw std::runtime_error("Error: not found " +
            (args.IsFlagExist(kFlagMaxTime) ? kFlagMinTime : kFlagMaxTime));
    }
}

void LogHandler::PrintResult() {
    std::stringstream result;
    if (flag_stat_) {
        for (size_t i = 0; i < files_.size(); i++) {
            result << files_[i].GetBadStat() << std::endl;
        }
    }
    if (flag_filter_) {
        for (size_t i = 0; i < files_.size(); i++) {
            result << files_[i].GetMessages() << std::endl;
        }
    }

    if (file_output_) {
        output_ << result.str();
    }
    else {
        std::cout << result.str();
    }
}

void LogHandler::EachFileFilterModule(const std::string& module_name) {
    flag_filter_ = true;
    for (File& file : files_) {
        file.FilterModule(module_name);
    }
}

void LogHandler::EachFileFilterTime(const std::tm& time_start, const std::tm& time_end) {
    flag_filter_ = true;
    for (File& file : files_) {
        file.FilterTime(time_start, time_end);
    }
}

void LogHandler::EachFileFilterStr(const std::string& str) {
    flag_filter_ = true;
    for (File& file : files_) {
        file.FilterString(str);
    }
}

void LogHandler::EachFileFilterType(const std::vector<CodesMessages>& codes) {
    flag_filter_ = true;
    for (File& file : files_) {
        file.FilterType(codes);
    }
}