#include <vector>


namespace algorithms::graph::atcoder::walk
{

using graph = std::vector<std::vector<int>>;

    /**
     * https://atcoder.jp/contests/dp/tasks/dp_r
     * There is a simple directed graph G with N vertices, numbered  1,2, .. ,N 
     * For each i and j (1 ≤ i, j ≤ N), you are given an integer a(i,j) 
     * that represents whether there is a directed edge from Vertex i to j.
     * If a(i,j) = 1, there is a directed edge from Vertex i to j; otherwise 0.
     * Find the number of different directed paths of length 
     * K in G, modulo 10(9) + 7. We will also count a path that traverses the same edge multiple times. */
    int pathsKLength(const graph& g, int k)
    {
        return 1;
    }   
}