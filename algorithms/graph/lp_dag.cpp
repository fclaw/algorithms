#pragma once
#include <vector>
#include <algorithm>
#include <optional>

namespace algorithms::graph::lp_dag
{

typedef std::vector<std::vector<int>> adj;
typedef std::vector<bool> vi;
typedef std::vector<int> table;
typedef std::vector<int> vs;

    void dfs(int v, const adj& g, vi& visited, vs& vertices)
    {
        for(int u : g[v])
          if(!visited[u])
            visited[u] = true,
            dfs(u, g, visited, vertices);
        vertices.push_back(v);    
    }

    vs topological_sort(int V, std::optional<int> start, const adj& graph)
    {
         vs vertices;
         vi visited = vi(V, false);
         if(start.has_value())
         {
            int s = start.value();
            visited[s] = true;
            dfs(s, graph, visited, vertices);
         }
         else
           for(int i = 0; i < V; i++)
             if(!visited[i]) dfs(i, graph, visited, vertices);
         std::reverse(vertices.begin(), vertices.end());
         return vertices;
    }
}