/*
───────────────────────────────────────────────────────────────
🧳 UVa 10305 OrderingTasks, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dfs.cpp"

#include <optional>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <cctype>




namespace algorithms::onlinejudge::graph::tasks_ordering
{
    /** https://onlinejudge.org/external/103/10305.pdf */
    int V, E;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        while(while_read(V, E) && (V || E)) {
          tools::vv_def_node tasks(V);
          loop(E, [&tasks](int _) {
            int from, to;
            while_read(from, to);
            --from, --to;
            auto n = tools::def_node;
            n.node = to;
            tasks[from].push_back(n);
          });

          tools::vi top_sort;
          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          dfs_s.on_leaving = 
            [&top_sort] (const tools::Node<>& n) 
            { top_sort.push_back(n.node); };
          
          for(int v = 0; v < V; ++v)
            if(dfs_s.state[v] == 
               tools::Unvisited) {
              tools::Node<> start_v = tools::def_node;
              start_v.node = v;
              tools::start_vertex = v;
              tools::dfs<>(tasks, dfs_s, start_v);
            }
          std::string ans;
          for(auto it = top_sort.rbegin(); it != top_sort.rend(); ++it)
            ans += std::to_string((*it + 1)) + ' ';
          ans.pop_back();
          std::cout << ans << std::endl;   
        }
    }
}