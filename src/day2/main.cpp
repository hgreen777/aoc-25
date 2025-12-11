// Day 2:
#include "FileHandler.hpp"
#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::string> f = FileReader::readCSV("src/day2/tinput.txt");

    long long total = 0;
    std::string first,last, current, sub, remaining, checkSection;
    long long ifirst,ilast, middle;
    int dashPos;

    for (int i = 0; i < f.size(); i++)
    {
        // Handle logic for one range of IDs
        std::cout << f[i] << "\n";

        dashPos = f[i].find('-');

        first = f[i].substr(0,dashPos); ifirst = std::stoll(first);
        last = f[i].substr(dashPos + 1); ilast = std::stoll(last);

        for (long long i = ifirst; i <= ilast; i++)
        {
            current = std::to_string(i);
            middle = current.size() / 2;

            bool match = false;

            for (int subSize = 1; subSize < middle + 1; subSize++)
            {
                // State 1, Create the possible substri (due to spec will alwasys be the first part)
                sub = current.substr(0, subSize);

                if (current.size() % subSize == 0)
                {
                    // Build a string containing the substring repeated for full length of string.
                    std::string repeated = "";

                    for (int j = 0; j < current.size() / subSize; j++)
                    {
                        repeated += sub;
                    }

                    //std::cout << repeated << "\n";
                    
                    // Check if match.
                    if (repeated.compare(current) == 0)
                    {
                        match = true;
                        break;
                    }
                }
            }

            if (match)
            {
                // Success so add total
                total += i;
                std::cout << sub << ": " << current << "\n";
            }

        }

        std::cout << "\n";
    }

    std::cout << total;


    std::cout << std::endl;
}