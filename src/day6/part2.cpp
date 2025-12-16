// Day 6
// Part 1: 6378679666679
// Part 2:

#include <iostream>
#include <string>
#include <vector>

#include "FileHandler.hpp"
#include "StrUtility.hpp"

#define ADD 0
#define MULTI 1
#define MAX_OPERANDS 10

int main()
{

    std::vector<std::string> f = FileReader::readLines("src/day6/input.txt");

    int operation = 0;
    std::string sNum = "";
    bool newEQ = true;
    long long eqTotal = 0;
    long long total = 0;

    // Handle, the final line. Get the index of starting then 
    std::cout << f.size()-1 << "\n";
    for (int col = 0; col < f[0].size(); col++)
    {
        if (newEQ)
        {
            if (f[f.size()-1][col] == '+')
            {
                operation = ADD;
            }
            else
            {
                operation = MULTI;
                eqTotal = 1;
            }

            newEQ = false;
        }

        sNum = "";

        for (int line = 0; line < f.size() - 1; line++)
        {
            if (f[line][col] != ' ')
            {
                sNum.append(std::string(1, f[line][col]));
            }
        }
        if (sNum != "")
        {
            switch (operation)
            {
                case ADD:
                    eqTotal += std::stoi(sNum);
                    break;
                case MULTI:
                    eqTotal *= std::stoi(sNum);
                    break;
                default:
                    std::cout << "Error: Operation not recognised" << "\n";
                    break;
            }
            std::cout << ((operation == ADD) ? " +" : " *") << " " << std::stoi(sNum);

            sNum = "";
        }
        else
        {
            total += eqTotal; std::cout << " = " << eqTotal << ". Bringing the total to: " << total << ".\n";
            eqTotal = 0;
            newEQ = true;
        }

        if (col == f[0].size() -1) // Edge case for final eq.
        {
            total += eqTotal; std::cout << " = " << eqTotal << ". Bringing the total to: " << total << ". Final Equation\n";
            eqTotal = 0;
            newEQ = true;
        }

    }
    std::cout << "Part 2 Total: " << total;
    std::cout << std::endl;
}

// For each column. ]
    // if newEq
        // find new operand.
        // set newEq == false

    // sNum = ""
    // for every row (not including final)
        // if digit
            // Read the digit
            // Construct number (concat it on the end as going down )

    // if sNum==""
        // add to eqTotal using current operation
        // sNum = ""
    // else
        // reset eqTotal
        // set newEq
