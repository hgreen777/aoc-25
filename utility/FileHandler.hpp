#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <stdio.h>
#include <iostream>

#define DEBUG 0

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

    static std::vector<std::string> readCSV(const std::string& filename)
    {
        std::ifstream file(filename);
        std::vector<std::string> values;
        std::string line;
        std::string value;

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open input file: " + filename);
        }

        while (std::getline(file, line))
        {
            while (line.find(',') != std::string::npos)
            {
                int pos = line.find(',');

                if (DEBUG)
                {
                    std::cout << pos << ": ";
                }
                values.push_back(line.substr(0,pos));

                if (DEBUG)
                {
                    std::cout << line.substr(0,pos) << "\n";
                }

                line = line.substr(pos + 1);

                if (DEBUG)
                {
                    std::cout << line << "\n";
                }
            }

            values.push_back(line);
        }
        if (DEBUG)
        {
            std::cout << std::endl;
        }
        return values;

    }

    static std::vector<std::vector<std::string>> readLinesCSV(const std::string& filename)
    {
        std::ifstream file(filename);
        std::vector<std::vector<std::string>> values;
        std::vector<std::string> lineVals;
        std::string line;

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open input file: " + filename);
        }

        while (std::getline(file, line))
        {
            while (line.find(',') != std::string::npos)
            {
                int pos = line.find(',');

                if (DEBUG)
                {
                    std::cout << pos << ": ";
                }
                lineVals.push_back(line.substr(0,pos));

                if (DEBUG)
                {
                    std::cout << line.substr(0,pos) << "\n";
                }

                line = line.substr(pos + 1);

                if (DEBUG)
                {
                    std::cout << line << "\n";
                }
            }

            lineVals.push_back(line);
            values.push_back(lineVals);
            lineVals.clear();
        }
        if (DEBUG)
        {
            std::cout << std::endl;
        }
        return values;

    }

};