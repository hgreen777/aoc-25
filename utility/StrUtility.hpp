
#pragma once

#include <string>
#include <iostream>


class StringUtility {
public:
    static std::string strip(const std::string& str)
    {
        const std::string WHITESPACE = " \n\r\t\f\v";
        int start = str.find_first_not_of(WHITESPACE);
        if (start == std::string::npos) return "";
        size_t end = str.find_last_not_of(WHITESPACE);
        return str.substr(start, end - start + 1);
    }



};