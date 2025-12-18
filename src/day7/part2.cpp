// Day 7
// Part 1: 1581

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "FileHandler.hpp"
#include "StrUtility.hpp"

#define ADD 0
#define MULTI 1
#define MAX_OPERANDS 10

int main()
{
    std::cout << "Hello World";
    std::vector<std::string> f = FileReader::readLines("src/day7/input.txt");

    std::vector<int> currentRow;
    std::vector<int> nextRow;
    int splitTotal = 0;

    // Find Start
    for (int col = 0; col < f[0].size(); col++)
    {
        if (f[0][col] == 'S')
        {
            std::cout << "Starting Position: " << col << "\n";
            currentRow.emplace_back(col);
            break;
        }
    }

    for (int i = 0; i < f.size() - 1; i++)
    {
        for (int col : currentRow)
        {
            char next = f[i + 1][col]; 
            if (next == '.')
            {
                nextRow.emplace_back(col);
            }
            else
            {
                splitTotal++;
                std::cout << "Split at: (" << i+1 << ", " << col << "). Current Total Now: " << splitTotal << "\n";
                nextRow.emplace_back(col-1);
                nextRow.emplace_back(col+1);
            }
        }

        currentRow = std::move(nextRow);
        nextRow.clear();


        // Iterate current row
            // Check row + 1 same col
            // if '.' 
                // next row to include col
            // else
                // split
                // add -1 & +1 to next row
                // increase counter
    }


        
    std::cout << "Part 1 Total: " << splitTotal;
    std::cout << std::endl;
}