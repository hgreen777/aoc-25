
#include "FileHandler.hpp"
#include <vector>
#include <string>
#include <iostream>
// less then 31000881098

int main()
{
    std::vector<std::string> f = FileReader::readCSV("src/day2/input.txt");

    long long total = 0;
    std::string first,last, current;
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
            // Check if first half of the string == second half.
            current = std::to_string(i);
            middle = current.size() / 2;

            if (current.substr(0, middle) == current.substr(middle))
            {
                std::cout << current << ", ";
                total += i;
            }


        }

        std::cout << "\n";
    }

    std::cout << total;


    std::cout << std::endl;
}