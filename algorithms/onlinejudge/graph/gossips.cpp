/*
───────────────────────────────────────────────────────────────
🧳 UVa 924 Spreading the News, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/bfs.cpp"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>


namespace tools = algorithms::onlinejudge::graph::tools;



namespace algorithms::onlinejudge::graph::gossips
{
    /** https://onlinejudge.org/external/9/924.pdf */
    int V, Q;
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
         
        while(while_read(V)) {
          tools::Graph<> graph(V);
          loop(V, [&] (int fn) {
            int N, num;
            while_read(N);
            loop(N, [&] (int _) {
              while_read(num);
              auto tn = tools::mkDefNode(num);      
              graph[fn].push_back(tn);
            });
          });

          while_read(Q);
          while(Q--) {
            int source;
            while_read(source);
            tools::Node<> start = tools::mkDefNode(source);
            tools::vi counter(V, 0);
            tools::Bfs<> bfs_s(V, start);
            bfs_s.check =
              [&](const tools::Node<>& node)
                  -> tools::BfsCheck 
              { 
                counter[bfs_s.dist[node.node]]++;
                return tools::GoOn; 
              };
            tools::bfs(graph, bfs_s);
            int max_boom = 0, boom_day = 0;
            for(int d = 1; d < (int)counter.size(); ++d) {
              if(counter[d] > max_boom) {
                max_boom = counter[d];
                boom_day = d;
              }
            }
            if(!max_boom) std::cout << 0 << std::endl;
            else printf("%d %d\n", max_boom, boom_day);
          }
        }  
    }
}