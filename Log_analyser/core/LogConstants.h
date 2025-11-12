#pragma once

#include <string>

enum CodesMessages {
	kInfo,
	kDebug,
	kWarning,
	kError,
	kFatal
};

const std::string kFlagMinTime = "--min_time";
const std::string kFlagMaxTime = "--max_time";
const std::string kFlagModule = "--module";
const std::string kFlagType = "--type";
const std::string kFlagStr = "--str";
const std::string kFlagStat = "--stat";
const std::string kFlagOut = "--output";
const std::string kFlagMinDate = "--min_date";
const std::string kFlagMaxDate = "--max_date";