//  Day 5
// Part 1: 520
// Part 2:

#include <string>
#include <iostream>
#include <vector>

#include "FileHandler.hpp"

int main()
{
    std::vector<std::string> f = FileReader::readLines("src/day5/input.txt");
    std::vector<std::pair< long long , long long >> ranges;

    
    // State 1: Reading ID Ranges
    // State 2: Checking current IDs
    bool isState2 = false;

    int total = 0;


    for (int i = 0; i < f.size(); i++)
    {
        if (f[i] == "")
        {
            isState2 = true;
            std::cout << "Switching states at line: " << i << "\n";
        }
        else
        {
            if (!isState2)
            {
                // State 1 : Read ranges
                int dashIndex = f[i].find('-');

                long long num1 = std::stoll(f[i].substr(0,dashIndex));
                long long num2 = std::stoll(f[i].substr(dashIndex + 1));

                std::cout << "Range being added: " << num1 << ", " << num2 << "\n";

                ranges.emplace_back(num1, num2);
                std::cout << "Range added: " << ranges[ranges.size() - 1].first << ", " << ranges[ranges.size() - 1].second << "\n";
            }
            else
            {
                for (int j = 0; j < ranges.size(); j++)
                {
                    long long currentNum = std::stoll(f[i]);
                    if (currentNum >= ranges[j].first && currentNum <= ranges[j].second)
                    {
                        total++;
                        std::cout << "Number: " << currentNum << ". In range: (" << ranges[j].first << ", " << ranges[j].second << ")." << "\n";
                        break;
                    }
                }
            }
        }

    }

    std::cout << "Total: " << total << "\n";

    std::cout << std::endl;
}