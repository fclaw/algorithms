#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>




typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::complete_search::graph_colouring
{
   
    /** https://onlinejudge.org/external/1/193.pdf, Max Independent Set, input is small */
    const size_t MAX = 101;
    vvi solution;
    void dfs(const vvi& graph, int u, vb& visited, vi& nodes)
    {
        visited[u] = true;
        for(int v : graph[u])
          if(!visited[v])
            nodes.push_back(v),
            dfs(graph, v, visited, nodes);
    }
    void backtrack(const vvi& graph, int i, const vi& nodes, vi blacks, vi& best)
    {
        // Base case: all nodes processed
        if (i == nodes.size())
        {
            // Found a better independent set
            if (blacks.size() > best.size())
              best = blacks;
            return;
        }
    
        int node = nodes[i];
        // Option 1: Skip the node (don't color it black)
        backtrack(graph, i + 1, nodes, blacks, best);
        // Option 2: Try adding node as black, if valid
        bool can_add = true;
        for(int neigh : graph[node])
          if (std::find(blacks.begin(), blacks.end(), neigh) != blacks.end()) 
          { can_add = false; break; }
    
        if (can_add)
          blacks.push_back(node),
          backtrack(graph, i + 1, nodes, blacks, best);
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            solution.clear();
            int V, E;
            std::cin >> V >> E;
            vvi graph(V);
            int u, v;
            for(int i = 0; i < E; i++)
            {
                std::cin >> u >> v;
                --u; --v;
                graph[u].push_back(v);
                graph[v].push_back(u);
            }

            vvi components;
            vb visited(V, false);
            for(int v = 0; v < V; v++)
              if(!visited[v])
              {
                  vi nodes;
                  nodes.push_back(v);
                  dfs(graph, v, visited, nodes);
                  components.push_back(nodes);
              }

            for(auto nodes : components)
            {
                vi best;
                backtrack(graph, 0, nodes, {}, best);
                solution.push_back(best);
            }

            int size = 0;
            std::string s;
            vi tmp;
            for(auto set : solution)
            {
                size += set.size();
                for(int v : set)
                  tmp.push_back(v + 1);
            }
            std::sort(tmp.begin(), tmp.end());
            for(int x : tmp) s += std::to_string(x) + " ";
            s.pop_back(); 
            std::cout << size << std::endl << s << std::endl;
            std::cin.ignore();
        }
    }
}