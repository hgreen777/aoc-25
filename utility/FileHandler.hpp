#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <stdio.h>

class FileReader {
public:
    static std::vector<std::string> readLines(const std::string& filename)
    {
        std::ifstream file(filename);
        std::vector<std::string> lines;
        std::string line;

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open input file: " + filename);
        }

        while (std::getline(file, line))
        {
            lines.push_back(line);
        }

        return lines;

    }

};