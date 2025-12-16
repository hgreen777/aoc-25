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
    std::cout << "Hello World";
    std::vector<std::string> f = FileReader::readLines("src/day6/input.txt");

    int operation = 0;
    int eq[MAX_OPERANDS] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int cursor = 0, nextCursor = 0;
    long long eqTotal = 0;
    long long total = 0;

    // Handle, the final line. Get the index of starting then 
    std::cout << f.size()-1 << "\n";
    for (int i = 0; i < f[0].size(); i++)
    {
        //std::cout << f[0].size() << " " << i << " " << f[f.size()-1].size() - 1 << "\n";

        // Find next cursor 
        for (int k = i+1; k <= f[f.size()-1].size(); k++)
        {
            //std::cout << "Inspecting character at position " << k << ": " << ((k < f[f.size()-1].size()) ? f[f.size()-1][k] : ' ') << "\n";

            if (k == f[f.size()-1].size())
            {
                nextCursor = f[f.size()-1].size();
                //std::cout << "Reached end of line. Setting nextCursor to " << nextCursor << "\n";
            }
            else if (f[f.size()-1][k] != ' ')
            {
                nextCursor = k;
                //std::cout << "Found non-space character at position " << k << ". Setting nextCursor to " << nextCursor << "\n";
                break;
            }
        }

        // Until Bottom line: Read number into eq array.
        for (int line = 0; line < f.size() - 1; line++)
        {
            //f[line][cursor]: cursor_*{1-9}*_nextCursor_*{1-9}*..  

            std::string sNum = f[line].substr(cursor,nextCursor);

            int t = std::stoi(StringUtility::strip(sNum));
            eq[line] = t; 
        }

        // handle f[line][cursor] (set operation)
        //std::cout << "EQ Operation: " << f[f.size()-1][cursor] << ": ";
        if (f[f.size()-1][cursor] == '+')
        {
            operation = ADD;
        }
        else
        {
            operation = MULTI;
            eqTotal = 1;
        }

        for (int idx = 0; idx < MAX_OPERANDS; idx++)
        {
            if (eq[idx] == -1)
            {
                break;
            }
            else
            {
                switch (operation)
                {
                    case ADD:
                        eqTotal += eq[idx];
                        break;
                    case MULTI:
                        eqTotal *= eq[idx];
                        break;
                    default:
                        std::cout << "Error: Operation not recognised" << "\n";
                        break;
                }
                std::cout << ((operation == ADD) ? " +" : " *") << " " << eq[idx];
            }
        }

        total += eqTotal;

        std::cout << " = " << eqTotal << ". Bringing the total to: " << total << ". Next Operation ("<< f[f.size()-1][nextCursor] <<") at: " << nextCursor << "\n";

        cursor = nextCursor;
        eqTotal = 0;
        for (int x = 0; x < MAX_OPERANDS; x++)
        {
            eq[x] = -1;
        }
        if (i == f[f.size()-1].size())
        {
            i = f[0].size();
            std::cout << "EOS";
        }
        else
        {
            i = cursor;
        } 
    }
    std::cout << "Part 1 Total: " << total;
    std::cout << std::endl;
}