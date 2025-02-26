#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>


typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::complete_search::settlers
{
    /** https://onlinejudge.org/external/5/539.pdf, 
     * longest simple path in a small general graph  */
    int maxPath;
    int V;
    int E;
    void backtrack(const vvi& graph, vvi& mask, int node, int path)
    {
        for(auto n : graph[node])
        {
            if(mask[node][n] || mask[n][node])
              continue;
            
            mask[node][n] = true;
            mask[n][node] = true;
            backtrack(graph, mask, n, path + 1);
            mask[node][n] = false;
            mask[n][node] = false;
        }

        maxPath = std::max(maxPath, path);
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        while(std::cin >> V >> E)
        {
            if(!V && !E) break;

            maxPath = INT32_MIN;
            vvi adjList(V);
            int from, to;
            for(int i = 0; i < E; i++)
            {
                std::cin >> from >> to;
                adjList[from].push_back(to);
                adjList[to].push_back(from);
            }

            vvi mask(V, vi(V, false));
            for(int i = 0; i < V; i++)
              backtrack(adjList, mask, i, 0),
              std::fill(mask.begin(), mask.end(), vi(V, false)); // Reset without reallocation

            std::cout << maxPath << std::endl;
        }
    }
}