//  Day 5
// Part 1: 520
// Part 2: 347338785050515

#include <string>
#include <iostream>
#include <vector>
#include <set>

#include "FileHandler.hpp"

long long part2 (std::vector<std::pair< long long , long long >> *ranges);
void printRanges(std::vector<std::pair< long long , long long >> *ranges, std::set<int> ignore);

int main()
{
    std::vector<std::string> f = FileReader::readLines("src/day5/input.txt");
    std::vector<std::pair< long long , long long >> ranges;

    
    // State 1: Reading ID Ranges
    // State 2: Checking current IDs
    bool isState2 = false;

    int total = 0;
    long long total2 = 0;


    for (int i = 0; i < f.size(); i++)
    {
        if (f[i] == "")
        {
            isState2 = true;
            std::cout << "Switching states at line: " << i << "\n";
            total2 = part2(&ranges);
        }
        else
        {
            if (!isState2)
            {
                // State 1 : Read ranges
                int dashIndex = f[i].find('-');

                long long num1 = std::stoll(f[i].substr(0 , dashIndex));
                long long num2 = std::stoll(f[i].substr(dashIndex + 1));

                std::pair<long long, long long> t = {num1, num2};
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
                        //std::cout << "Number: " << currentNum << ". In range: (" << ranges[j].first << ", " << ranges[j].second << ")." << "\n";
                        break;
                    }
                }
            }
        }

    }

    std::cout << "Total: " << total << "\n";
    std::cout << "Part 2 Total: " << total2 << "\n";

    std::cout << std::endl;
}

long long part2 (std::vector<std::pair< long long , long long >> *ranges)
{
    // Need to for every pair of ranges, if there is overlap, collapse into 1 range.
    std::pair< long long , long long > r1,r2;
    std::set<int> ignore;
    bool merge = true;
    
    while (merge)
    {
        merge = false;

        for (int range1 = 0; range1 < ranges->size(); range1++)
        {
            if (ignore.count(range1) > 0) 
            {
                continue;
            }


            for (int range2 = range1 + 1; range2 < ranges->size(); range2++)
            {
                if (ignore.count(range2) > 0 || range1 == range2)
                {
                    continue;
                }

                r1 = ranges->at(range1);
                r2 = ranges->at(range2);

                std::cout << "Comparing range1 (" << r1.first << ", " << r1.second << ") with range2 (" << r2.first << ", " << r2.second << ").\n";

                // Check for Merge, Add to Ignore 
                if (r2.first <= r1.first && r2.second >= r1.second)
                {
                    //std::cout << "Case 1: range2 completely overlaps range1. Merging.\n";
                    r1.first = r2.first;
                    r1.second = r2.second;
                }
                else if (r2.first <= r1.first && r2.second >= r1.first && r2.second <= r1.second)
                {
                    //std::cout << "Case 2: range2 overlaps range1 on the left. Merging.\n";
                    r1.first = r2.first;
                }
                else if (r2.second >= r1.second && r2.first >= r1.first && r2.first <= r1.second)
                {
                    //std::cout << "Case 3: range2 overlaps range1 on the right. Merging.\n";
                    r1.second = r2.second;
                }
                else if (r2.first >= r1.first && r2.second <= r1.second)
                {
                    //std::cout << "Case 4: range2 is completely within range1. No merge needed.\n";
                }
                else
                {
                    //std::cout << "Case 5: range2 is disjoint from range1. No merge.\n";
                    continue;
                }

                std::cout << "Merging range2 index " << range2 << " into range1 index " << range1 << ". Adding range2 to ignore set.\n";
                ignore.emplace(range2);
                ranges->at(range2).first = 0;
                ranges->at(range2).second = 0;
                ranges->at(range1) = r1;
                merge = true;
            }
        }
        //printRanges(&ranges, ignore);
    }


    // Loop over all ranges 
    long long total = 0;
    for (int i = 0; i < ranges->size(); i++)
    {
        if (ignore.count(i) > 0)
        {
            continue;
        }
        std::cout << "Ranges: " << ranges->at(i).first << ", " << ranges->at(i).second <<". indes: " << i << "\n";
        if (ranges->at(i).second < ranges->at(i).first)
        {
            long long t = ranges->at(i).first;
            ranges->at(i).first = ranges->at(i).second;
            ranges->at(i).second = t;
        }
        total += ranges->at(i).second - ranges->at(i).first + 1;
    }

    return total;
}

void printRanges(std::vector<std::pair< long long , long long >> *ranges, std::set<int> ignore)
{
     for (int i = 0; i < ranges->size(); i++)
    {
        if (ignore.count(i) > 0)
        {
            continue;
        }
        std::cout << "Ranges: " << ranges->at(i).first << ", " << ranges->at(i).second <<". indes: " << i << "\n";
    }
}