#include <vector>

namespace leetcode::graph
{

    /*
      As an example, consider the problem of calculating the number of paths from node a to node b. 
     Let paths(x) denote the number of paths from node a to node x. As a base case, paths(a) = 1. Then, 
     to calculate other values of paths(x), we can use the recursive formula
      paths(x) = paths(s1) + paths(s2) + ... + paths(sk),
      where s1, s2, . . . , sk are the nodes from which there is an edge to x. 
      Since the graph is acyclic, the values of paths can be calculated in the order of a topological sort
    */
    int countPathsFromXtoY( std::vector<std::vector<int>>& graph, int from, int to)
    {  
    }

    // https://leetcode.com/problems/number-of-ways-to-arrive-at-destination
    /*
    You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections. 
    The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.
    You are given an integer n and a 2D integer array roads where roads[i] = [u(i), v(i), time(i)] 
    means that there is a road between intersections u(i) and v(i) that takes time(i) minutes to travel. 
    You want to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.
    Return the number of ways you can arrive at your destination in the shortest amount of time. Since the answer may be large, return it modulo 109 + 7
    */
    int countPaths(int n, std::vector<std::vector<int>>& roads) { return 0; }
}