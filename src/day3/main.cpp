// Day 3:
// Part 1: 17142
// Part 2: 169935154100102
#include <iostream>
#include <string>
#include <vector>

#include "FileHandler.hpp"

/*
814247773322911 -> 844777332291
*/
static int smallestIndex (std::string s);

int main()
{
    std::vector<std::string> f = FileReader::readLines("src/day3/input.txt");

    unsigned long long total = 0ULL;

    std::string line,highest = "0";
    char cCurrent;

    // For Each line.
    for (int i = 0; i < f.size(); i++)
    {
        std::cout << "Initial Number: " << f[i]<< "\n";
        line = f[i];

        //std::cout << line.size() << "\n"; // 15

        highest = line.substr(line.size() - 12);
        std::cout << "Initial Highest: " << highest << "\n";

        // Assume it is going to go from the edge of the current highest to start
        for (int j = line.size() - 13; j >= 0 ; j--)
        {

            cCurrent = line[j];
            //std::cout << "Current Letter: " << cCurrent << "\n";
            
            if (cCurrent >= highest[0])
            {
                // Shift all current highest along and omit the smalllest number in highest
                int iSmallest = smallestIndex(highest);
                
                // Shift up till that index (ie omitting it)
                highest = std::string(1, cCurrent) + highest.substr(0, iSmallest) + highest.substr(iSmallest + 1);
            }
            // Remove impurities within the string
            //std::cout << "Current Highest: " << highest << ". With current letter: " << cCurrent << "\n";
        }


        // Add final total joltage
        std::cout << "Final: " << highest << "\n";
        total += std::stoll(highest);
    }

    std::cout << total << "\n";

    std::cout << std::endl;
}

// Adapt to take the first smallest index before it rises -> removes impurities
static int smallestIndex (std::string s)
{
    // Input:: String s
    // Output: Index of where the smallest character number is 
    char smallest = s[0];
    int index = 0;

    for (int i = 1; i < s.size(); i++)
    {
        if (s[i] < smallest)
        {
            smallest = s[i];
            index = i;
        }
        else if (s[i] > smallest)
        {
            return index;
        }
    }

    return index;
}