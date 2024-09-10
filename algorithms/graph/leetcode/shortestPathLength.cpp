#include <vector>
#include <queue>
#include <unordered_map>

namespace algorithms::graph::leetcode::sp_all_nodes
{

using graph = std::vector<std::vector<int>>;
using vi = std::vector<bool>;
using dist = std::vector<int>;
using memo = std::unordered_map<int, std::unordered_map<int, int>>;

    /** 
     * https://leetcode.com/problems/shortest-path-visiting-all-nodes
     * You have an undirected, connected graph of n nodes labeled from 0 to n - 1. 
     * You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.
     * Return the length of the shortest path that visits every node. 
     * You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
     */
    int V;
    int bfs(const graph& g, int source, int sink) 
    {
        vi visited = vi(V, false);
        dist distance = dist(V, -1);
        std::queue<int> q;
        visited[source] = true;
        distance[source] = 0;
        q.push(source);
        bool finished = false;
        while(!q.empty() && !finished) 
        {
            int v = q.front();
            q.pop();
            if(v == sink)
            {
                finished = true;
                break;
            }
            for(auto u : g[v])
              if(!visited[u])
              {
                  visited[u] = true;
                  distance[u] = distance[v] + 1;
                  q.push(u);
              }
        }
        return distance[sink];
    }
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
            int res = bfs(g, source, v);
            path = std::min(path, res + calculateMinPath(g, v, (mask | (1 << v)), mt));
        }
        return mt[source][mask] = path;
    }
    int shortestPathLength(const graph& g) 
    {
        V = g.size();
        int ans = INT32_MAX;
        memo mt;
        for(int v = 0; v < V; v++)
          ans = std::min(ans, calculateMinPath(g, v, (0 | (1 << v)), mt));
        return ans;  
    }
}