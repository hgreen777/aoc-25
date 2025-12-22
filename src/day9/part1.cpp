// Day 9
// Part 1: 4777816465

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include "FileHandler.hpp"

struct loc
{
    long long x = 0;
    long long y = 0;

    loc()
    {
        x = 0;
        y = 0;
    }

    loc(long long x1, long long y1)
    {
        x = x1;
        y = y1;
    }

    bool operator<(const loc &other) const
    {
        // Sort by x
        return x < other.x;
    }
};

long long area (const loc &l1, const loc &l2);

std::string printLoc (const loc &l);

int main()
{
    std::vector<std::vector<std::string>> f = FileReader::readLinesCSV("src/day9/input.txt");

    std::vector<loc> locations;

    // Read lines into locations
    loc l;
    for (int i = 0; i < f.size(); i++)
    {
        locations.emplace_back(std::stoll(f[i][0]), std::stoll(f[i][1]));

        //std::cout << printLoc(locations[i]) << "\n";
    }
    //std::sort(locations.begin(), locations.end());

    long long maxArea = 0;
    long long tempArea = 0;
    // Loop over all pairs and see if it is bigger.
    for (int i = 0; i < locations.size(); i++)
    {
        for (int j = i+1; j < locations.size(); j++)
        {
            tempArea = area(locations[i], locations[j]);
            //std::cout << "Area for: " << printLoc(locations[i]) << " & " << printLoc(locations[j]) << " = " << tempArea << "\n";
            if (tempArea > maxArea)
            {
                maxArea = tempArea;
            }
        }
    }

    std::cout << "Biggest Area: " << maxArea << "\n";

    std::cout << std::endl;
}


long long area (const loc &l1, const loc &l2)
{
    long long width, height, a;
    loc p1,p2;
    p1.x = std::min(l1.x, l2.x);
    p1.y = std::min(l1.y, l2.y);
    p2.x = std::max(l1.x, l2.x);
    p2.y = std::max(l1.y, l2.y);

    width = std::abs(p2.x - p1.x) + 1;
    height = std::abs(p2.y - p1.y) + 1;
    
    a = width * height;

    std::cout << "Area for: " << printLoc(l1) << " & " << printLoc(l2) << ": Comparing points for: " << printLoc(p1) << " & " << printLoc(p2) << ". "<< width << " * " << height << " = " << a << "\n";
    return a;
}

std::string printLoc (const loc &l)
{
    return "(" + std::to_string(l.x) + ", " + std::to_string(l.y) + ")";
}