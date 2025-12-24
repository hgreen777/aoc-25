// Day 9
// Part 2: < 4743386600 == 4743386600

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include "FileHandler.hpp"

struct line
{
    long long x;
    long long y1;
    long long y2;

    line (long long x1, long long y11, long long y21)
    {
        x = x1;
        y1 = y11;
        y2 = y21;
    }

    bool operator< (const line &other) const
    {
        if (x < other.x)
        {
            return true;
        } 
        else if (x == other.x && y2 < other.y2)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
};

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
bool pointInPolygon (const loc &l1, const std::vector<line> &perimeter);
bool pointInPolygon (const loc &l1, const loc &l2, const std::vector<line> &perimeter);

std::string printLoc (const loc &l);

int main()
{
    std::vector<std::vector<std::string>> f = FileReader::readLinesCSV("src/day9/input.txt");

    std::vector<loc> locations; 
    std::vector<line> perimeter;
    std::vector<line> compressedLocations;
    std::vector<line> compressedPerimeter;


    // Read lines into locations
    loc l;

    for (int i = 0; i < f.size(); i++)
    {
        locations.emplace_back(std::stoll(f[i][0]), std::stoll(f[i][1]));

        //std::cout << printLoc(locations[i]) << "\n";
    }
    
    /*
        Produce Perimeter DS for ray tracing.
    */
    for (int i = 0; i < locations.size() - 1; i++)
    {
        loc p1,p2;

        p1 = locations[i]; p2 = locations[i+1];

        if (p1.x == p2.x)
        {
            perimeter.emplace_back(p1.x, std::min(p1.y, p2.y), std::max(p1.y, p2.y));
        }
    }

    // Check Wrap Case
    if (locations[0].x == locations[locations.size()-1].x)
    {
        perimeter.emplace_back(locations[0].x, std::min(locations[0].y, locations[locations.size()-1].y), std::max(locations[0].y, locations[locations.size()-1].y));
    }
    std::sort(perimeter.begin(), perimeter.end());
    std::cout << "Lines to check for: " << perimeter.size() << "\n";
    for (int i = 0; i < perimeter.size(); i++)
    {
        std::cout << "Perimeter Line " << i << ": " << perimeter[i].x << " in range: (" << perimeter[i].y1 << ", " << perimeter[i].y2 << ")\n";
    }


    // Compress points
    


    long long maxArea = 0;
    long long tempArea = 0;
    loc p1,p2,p3,p4; // Starting bottom left & Clockwise.
    long long minX, maxX, minY, maxY;


    // Loop over all pairs and see if it is bigger.
    for (int i = 0; i < locations.size(); i++)
    {
        std::cout<< "Location: " << i << " / " << locations.size()-1<< " - " << printLoc(locations[i]) << "\n";

        for (int j = i+1; j < locations.size(); j++)
        {
            // For every pair point:
                // Produce Cube
                // For each point test if inside/equal
                // if yes
                    // standard size testing.
                // else ignore

            //std::cout << "\t 2nd Location "<< j << " / " << locations.size()-1 << " - " << printLoc(locations[j]) << ": ";

            minX = std::min(locations[i].x, locations[j].x);
            maxX = std::max(locations[i].x, locations[j].x);

            minY = std::min(locations[i].y, locations[j].y);
            maxY = std::max(locations[i].y, locations[j].y);

            p1 = loc(minX, minY); if ( !pointInPolygon(p1, perimeter) ) continue;
            p2 = loc(minX, maxY); if ( !pointInPolygon(p2, perimeter) ) continue;
            p3 = loc(maxX, maxY); if ( !pointInPolygon(p3, perimeter) ) continue;
            p4 = loc(maxX, minY); if ( !pointInPolygon(p4, perimeter) ) continue;
            for (int k = minY; k <= maxY; k++)
            {
                if ( !pointInPolygon(loc(minX,k), perimeter) ) continue;
                if ( !pointInPolygon(loc(maxX,k), perimeter) ) continue;
                // Only Check overhangs not dips within cube X would require same logic applied to the y ray casts

                // ^^ NOT EFFICIENT, REQUIRE COMPRESSION OF ALL DATA POINTS 
            }

            tempArea = area(p1, p3);
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
    // Assumes l2 is higher and wider then l1.
    long long width, height, a;

    width = std::abs(l2.x - l1.x) + 1;
    height = std::abs(l2.y - l1.y) + 1;
    
    a = width * height;

    //std::cout << "Area for: " << printLoc(l1) << " & " << printLoc(l2) << ": " << width << " * " << height << " = " << a << "\n";
    return a;
}

int searchStart (const long long x, const std::vector<line> &perimeter)
{
    // Linear Search
    for (int i = 0; i < perimeter.size(); i++)
    {
        if (x <= perimeter[i].x)
        {
            return i;
        }
    }
    std::cout << "ERRRORRRRRRRR";
    return -1;
}

bool pointInPolygon (const loc &l1, const std::vector<line> &perimeter)
{
    //return true;
    // Ray Tracing 
    // Find the point search within perimeter (where to start - if same x l1 comes before)
    int startIdx = searchStart(l1.x, perimeter);
    int lineIntersectCtr = 0;

    // For the rest of count of perimeter, check y ranges and include coutner and return true if odd. 
    for (int i = startIdx; i < perimeter.size(); i++)
    {
        if (perimeter[i].y1 <= l1.y && l1.y <= perimeter[i].y2)
        {
            lineIntersectCtr++;
            if (perimeter[i].x == l1.x)
            {
                return true; // Early exit as lands on line.
            }
        }
    }

    if (lineIntersectCtr % 2 == 0)
    {
        //std::cout << "Cube not considered as :" << printLoc(l1) << " intersects with " << lineIntersectCtr << " lines\n";
        return false;
    }
    else
    {
        return true;
    }
}

bool pointInPolygon (const loc &l1, const loc &l2, const std::vector<line> &perimeter)
{
    //return true;
    // Ray Tracing 
    // Find the point search within perimeter (where to start - if same x l1 comes before)
    int startIdx = searchStart(l1.x, perimeter);
    int lineIntersectCtr = 0;

    // For the rest of count of perimeter, check y ranges and include coutner and return true if odd. 
    for (int i = startIdx; i < perimeter.size(); i++)
    {
        if (
            perimeter[i].y1 <= l1.y && l1.y <= perimeter[i].y2 && 
            perimeter[i].y1 <= l2.y && l2.y <= perimeter[i].y2 // Check second point to ensure no gap in perimeter.
            && perimeter[i].x == l1.x // Lands on line?
        )
        {
            return true;
        }
    }
    return false;

    if (lineIntersectCtr % 2 == 0)
    {
        //std::cout << "Cube not considered as :" << printLoc(l1) << " intersects with " << lineIntersectCtr << " lines\n";
        return false;
    }
    else
    {
        return true;
    }
}

std::string printLoc (const loc &l)
{
    return "(" + std::to_string(l.x) + ", " + std::to_string(l.y) + ")";
}

// Generate Perimeter
// Consider each pair:
    // Produce full cube
    // Test all 4 points inside
    //      Yes: produce area

        