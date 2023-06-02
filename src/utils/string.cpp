
#include <string>
#include <locale>
#include <codecvt>
#include "utils/string.h"

namespace utils
{
//convert string to wstring
std::wstring to_wide_string(const std::string& input)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
}

//convert wstring to string 
std::string to_byte_string(const std::wstring& input)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(input);
}

std::string TimeToString(time_t timeStamp)
{
    struct tm* timeinfo = nullptr;
    char buffer[80];
    timeinfo = localtime(&timeStamp);
    strftime(buffer, 80, "%Y-%m-%d %H:%M", timeinfo);
    return std::string(buffer);
}

}
