// Day 4
// Part 1: 1547
// Part 2: 8948

#include <iostream>
#include <string>
#include <vector>

#include "FileHandler.hpp"

int main()
{
    std::vector<std::string> f = FileReader::readLines("src/day4/input.txt");
    std::vector<std::string> fPrime(f.begin(), f.end());

    int total = 0;
    int difference = -1;
    int currentCount = 0;
    int checkX,checkY;

    while (difference != 0)
    {
        difference = 0;
        for (int y = 0; y < f.size(); y++)
        {
            for (int x = 0; x < f[0].size(); x++)
            {
                if (f[y][x] == '.')
                {
                    continue;
                }

                currentCount = 0;


                // For each square apply kernal, check bounds. 
                for (int kernelY = -1; kernelY < 2; kernelY++)
                {
                    for (int kernelX = -1; kernelX < 2; kernelX++)
                    {
                        // Dont include current position
                        if (kernelX == 0 && kernelY == 0)
                        {
                            continue;
                        }

                        checkX = x + kernelX;
                        checkY = y + kernelY;

                        // Bounds check
                        if (checkY >= 0 && checkY < f.size() && checkX >= 0 && checkX < f[0].size())
                        {
                            if (f[checkY][checkX] == '@')
                            {
                                currentCount++;
                            }

                        }
                    }
                }

                if (currentCount < 4)
                {
                    fPrime[y][x] = '.';
                    difference++;
                    std::cout << "Current Count: " << currentCount << ". For (" << x << ", " << y << ")" << "\n";
                }
            }
        }

        f = std::vector<std::string>(fPrime.begin(), fPrime.end());
        total += difference;
    }

    std::cout << total << "\n";

    std::cout << std::endl;
}