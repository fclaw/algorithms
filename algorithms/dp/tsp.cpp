#include <vector>
#include <iostream>

namespace algorithms::dp
{
    /*
        Problem: Given n cities and their pairwise distances in the form of a matrix dist of size n × n, 
        compute the cost of making a tour18 that starts from any city s, 
        goes through all the other n − 1 cities exactly once, and finally returns to the starting city s.
    */
    int tsp(std::vector<std::vector<int>> cities, int s, int visited)
    {
        int n = cities.size();
        if(visited == std::pow(2, n) - 1)
          return cities[s][0];

        int dist = INT32_MAX;
        for (int next = 0; next < n; next++)
          if(!(visited & (1 << next)))
              dist = std::min(dist, cities[s][next] + tsp(cities, next, visited | (1 << next)));

        return dist;
    } 

    int minCostToVisitAllCities(std::vector<std::vector<int>> cities) { return tsp(cities, 0, 1); }
}