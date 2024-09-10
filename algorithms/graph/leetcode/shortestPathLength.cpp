#include <vector>
#include <queue>
#include <unordered_map>

namespace algorithms::graph::leetcode::sp_all_nodes
{

using graph = std::vector<std::vector<int>>;
using vi = std::vector<bool>;
using dist = std::vector<int>;
using memo = std::unordered_map<int, std::unordered_map<int, int>>;
using sp = std::vector<std::vector<int>>;

    /** 
     * https://leetcode.com/problems/shortest-path-visiting-all-nodes
     * You have an undirected, connected graph of n nodes labeled from 0 to n - 1. 
     * You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.
     * Return the length of the shortest path that visits every node. 
     * You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
     */
    const int inf = 5 * 1e+05;
    int V;
    sp adjMatrix;
    int calculateMinPath(const graph& g, int source, int mask, memo& mt)
    {
        if(mask == ((1 << V) - 1))
          return 0;

        if(auto it_f = mt.find(source); it_f != mt.end())
          if(auto it_s = (*it_f).second.find(mask); 
            it_s != (*it_f).second.end())
            return (*it_s).second;

        int path = INT32_MAX;
        for(int v = 0; v < V; v++)
        {
            if((mask & (1 << v)))
              continue;
            int res = adjMatrix[source][v];
            path = std::min(path, res + calculateMinPath(g, v, (mask | (1 << v)), mt));
        }
        return mt[source][mask] = path;
    }
    int shortestPathLength(const graph& g) 
    {
        V = g.size();
        int ans = INT32_MAX;
        
        adjMatrix = sp(V, std::vector<int>(V, inf));

        for(int u = 0; u < V; u++)
          for(auto v : g[u])
            adjMatrix[u][v] = 1;

        // Floyd Warshall’s algorithm
        for(int k = 0; k < V; k++)
          for(int i = 0; i < V; i++)
            for(int j = 0; j < V; j++)
              adjMatrix[i][j] = std::min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);

        memo mt;
        for(int v = 0; v < V; v++)
          ans = std::min(ans, calculateMinPath(g, v, (0 | (1 << v)), mt));
        return ans;  
    }
}