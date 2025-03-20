#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>




typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<vi> vvi;
typedef std::unordered_set<int> si;


namespace algorithms::onlinejudge::complete_search::graph
{
   
    bool solved = false;
    /** https://onlinejudge.org/external/1/193.pdf, Max Independent Set, input is small */
    void backtrack(const vvi& adjList, int v, vb& visited, si& blacks)
    {
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int V, E;
            std::cin >> V >> E;
            vvi adjList(V);
            int u, v;
            for(int i = 0; i < E; i++)
            {
                std::cin >> u >> v;
                --u; --v;
                adjList[u].push_back(v);
                adjList[v].push_back(u);
            }
        }
    }
}