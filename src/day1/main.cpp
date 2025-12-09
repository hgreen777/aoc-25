

#include <iostream>
#include <string>
#include <vector>

#include "FileHandler.hpp"

int main()
{
    std::vector<std::string> f = FileReader::readLines("./src/day1/input.txt");

    if (f.empty()) {
        std::cout << "The file is empty or could not be read." << std::endl;
    } 

    int x = 50;
    int pass = 0;

    std::cout << x << "\n";;

    for (int i = 0; i < f.size(); i++)
    {
        char dir = f[i][0];
        int amount = std::stoi(f[i].substr(1));

        

        if (dir == 'L')
        {
            x -= amount;
        }
        else if (dir == 'R')
        {
            x += amount;
        }

        while (x < 0 || x > 99)
        {
            if (x < 0)
            {
                x = 100 + x; 
            }
            else if (x > 99)
            {
                x = 0 + (x - 100);
            }
        }

        if (x == 0)
        {
            pass++;
        }

        std::cout << f[i] << " points at: " << x << "\n";;
    }


    std::cout << pass;
    std::cout << std::endl;
}