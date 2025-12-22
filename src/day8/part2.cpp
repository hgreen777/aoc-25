// Day 8
// Part 2:  1474050600

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cmath> 
#include <limits>
#include <algorithm> 

#include "FileHandler.hpp"

#define JUNCTION_BOX_COUNT 1000

struct loc
{
    long long x = 0;
    long long y = 0;
    long long z = 0;
};

struct circuits
{
    int parent[JUNCTION_BOX_COUNT];
    int size[JUNCTION_BOX_COUNT];
};

double dist (loc &p1, loc &p2);
void initialiseCircuits(circuits &c);
int find (const int &x, circuits &c);
void unite (int u, int v, circuits &c); // Union
bool allConnected (circuits &c);

std::string printDist (loc &p1);

int main()
{
    std::cout << "Hello World!" << "\n";

    std::vector<std::vector<std::string>> f = FileReader::readLinesCSV("src/day8/input.txt");

    std::vector<loc> locations;
    std::vector<std::pair<std::pair<int, int>, double>> distances;
    circuits allCircuits; initialiseCircuits(allCircuits);
    long long total;

    // Read each location into all locations
    for (int i = 0; i < f.size(); i++)
    {
        loc t;
        t.x = std::stoi(f[i][0]);
        t.y = std::stoi(f[i][1]);
        t.z = std::stoi(f[i][2]); 
        locations.push_back(t);
    }

    // Process all distance pairs for locations
    std::pair<int, int> location;
    std::pair<std::pair<int, int>, double> distanceObj;
    for (int i = 0; i < locations.size(); i++)
    {
        for (int j = i+1; j < locations.size(); j++)
        {
            location.first =  i;
            location.second = j;

            distanceObj.first = location;
            distanceObj.second = dist(locations[location.first], locations[location.second]);

            distances.emplace_back(distanceObj);
        }
    }

    // Sort based of size of location.
    std::sort(distances.begin(), distances.end(), [](const std::pair<std::pair<int, int>, double> &a, const std::pair<std::pair<int, int>, double> &b) {
        return a.second < b.second;
    });

    std::cout << "Size of connections: " << distances.size() << "\n";

    for (int k = 0; k < distances.size(); k++)
    {    
        std::cout << "Processing " << k+1 << "th shortest circuit path." << "\n";

        std::cout << "Processing edges betweeen: " << printDist(locations[distances[k].first.first]) << " and " << printDist(locations[distances[k].first.second]) << ". With Dist: " << distances[k].second << "\n";
        
        if (find(distances[k].first.first, allCircuits) != find(distances[k].first.second, allCircuits))
        {
            unite(distances[k].first.first, distances[k].first.second, allCircuits);
        }

        // Check if this connection has caused all the nodes to be connected.
        if (allConnected(allCircuits)) {
            std::cout << "All nodes are now connected." << std::endl;
            std:: cout << locations[distances[k].first.first].x << ", " << locations[distances[k].first.second].x << "\n";
            
            total = locations[distances[k].first.first].x * locations[distances[k].first.second].x;
            
            break;
        }
    }


    
    std::cout << "Part 2 Total: " << total << "\n";

    std::cout << std::endl;
}

double dist (loc &p1, loc &p2)
{
    // Dist between 2 points is -p1 + p2 -> p2 - p1; dist = sqrt(x^2 + y^2 + z^2) 
    
    loc distVec;

    distVec.x = p2.x - p1.x; distVec.x *= distVec.x;
    distVec.y = p2.y - p1.y; distVec.y *= distVec.y;
    distVec.z = p2.z - p1.z; distVec.z *= distVec.z;

    return std::sqrt(distVec.x + distVec.y + distVec.z);
}

void initialiseCircuits(circuits &c)
{
    for (int i = 0; i < JUNCTION_BOX_COUNT; i++)
    {
        c.parent[i] = i;
        c.size[i] = 1;
    }
}

// Works on indexes into distances.
int find (const int &x, circuits &c)
{
    if (c.parent[x] != x)
    {
        c.parent[x] = find(c.parent[x], c);
    }
    return c.parent[x];
}

void unite (int u, int v, circuits &c)
{
    int rootU = find(u,c);
    int rootV = find(v,c);

    if (rootU == rootV)
    {
        return;
    }

    if (c.size[rootU] < c.size[rootV])
    {
        std::swap(rootU, rootV);
    }

    c.parent[rootV] = rootU;
    c.size[rootU] += c.size[rootV];
}


std::string printDist (loc &p1)
{
    std::string s = "(";
    s += std::to_string(p1.x);
    s += ", ";
    s += std::to_string(p1.y);
    s += ", ";
    s += std::to_string(p1.z);
    s += ")";
    return s;
}

bool allConnected (circuits &c)
{
    for (int i = 1; i < JUNCTION_BOX_COUNT; i++) {
        if (find(i, c) != find(0, c)) {
            return false;
        }
    }
    return true;
}
