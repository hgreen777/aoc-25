// Day 3:
// Part 1:
// Part 2: 
#include <iostream>
#include <string>
#include <vector>

#include "FileHandler.hpp"

int main()
{
    std::vector<std::string> f = FileReader::readLines("src/day3/tinput.txt");

    int total = 0;

    std::string line,highest = "0";
    char cCurrent;

    // For Each line.
    for (int i = 0; i < f.size(); i++)
    {
        std::cout << f[i]<< "\n";
        line = f[i];

        highest = "00";

        for (int j = 0; j < line.size() - 1; j++)
        {

            cCurrent = line[j];
            //std::cout << "Current Letter: " << cCurrent << "\n";
            
            // A change is required as it is higher then 1 or both of current.
            if (cCurrent > highest[0] || cCurrent > highest[1])
            {
                
                if (cCurrent > highest[0])
                {
                    // Case 1: Bigger then first -> will be bigger number.

                    if (j == (line.size() - 2))
                    {
                        // Edge case: to ensure final highest is valid
                        highest[1] = cCurrent;
                        std::cout << "Last Letter edge case" << "\n";
                    }
                    else
                    {
                        highest[0] = cCurrent;
                        highest[1] = '0';
                    }
                    
                    std::cout << "Case 1 or 2: " << highest << "\n";
                }
                else 
                {
                    // Case 3: Bigger then second.
                    highest[1] = cCurrent;
                    std::cout << "Case 3: " << highest << "\n";
                }
            }
            
        }


        // Add final total joltage
        std::cout << highest << "\n";
        total += std::stoi(highest);
    }

    std::cout << total << "\n";

    std::cout << std::endl;
}