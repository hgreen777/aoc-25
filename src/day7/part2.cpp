// Day 7
// Part 2: 73007003089792

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "FileHandler.hpp"
#include "StrUtility.hpp"

#define ADD 0
#define MULTI 1
#define MAX_OPERANDS 10

int main()
{
    std::cout << "Hello World";
    std::vector<std::string> f = FileReader::readLines("src/day7/input.txt");

    std::map<int, long long> currentRow;
    std::map<int, long long> nextRow;
    long long total = 0;

    // Find Start
    for (int col = 0; col < f[0].size(); col++)
    {
        if (f[0][col] == 'S')
        {
            std::cout << "Starting Position: " << col << "\n";
            currentRow[col] = 1L; // Sets it to 1 path to start pos.
            break;
        }
    }

    // Uses map to keep track of paths to that col.
    for (int i = 0; i < f.size() - 1; i++)
    {
        for (std::pair<int, long long> col : currentRow)
        {
            char next = f[i + 1][col.first]; 
            if (next == '.')
            {
                nextRow[col.first] += col.second;
            }
            else
            {
                std::cout << "Split at: (" << i+1 << ", " << col.first << "). Current Ways to get there: " << col.second << "\n";
                nextRow[col.first - 1] += col.second;
                nextRow[col.first + 1] += col.second;
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

    for (std::pair<int, long long> col : currentRow)
    {
        total += col.second;
    }

        
    std::cout << "Part 2 Total: " << total;
    std::cout << std::endl;
}