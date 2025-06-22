/*
───────────────────────────────────────────────────────────────
🧳 UVa 10048, Audiophobia, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/mst.cpp"
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
#include <map>
#include <unordered_set>


namespace mst = algorithms::onlinejudge::graph::tools::mst;
namespace tools = algorithms::onlinejudge::graph::tools;

namespace algorithms::onlinejudge::graph::audiophobia
{
    /** https://onlinejudge.org/external/100/10048.pdf */
    int V, E, Q, c = 1;
    bool is_first = true;
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

        while(while_read(V, E, Q) && V && E && Q) {
          tools::vvi nn_w(V, tools::vi(V, INT32_MAX));
          mst::VEdge<> streets;
          loop(E, [&](int _) {
            int from, to, d;
            while_read(from, to, d);
            --from; --to;
            streets.push_back(mst::mkDefEdge(from, to, d));
            nn_w[from][to] = nn_w[to][from] = d; 
          });

          tools::vv_def_node sp(V);
          mst::Kruskal<> kruskal_s = mst::initKruskal(V, (int)streets.size(), 0);
          kruskal_s.on_adding_edge =
            [&sp] 
            (int _, const mst::Edge<int>& edge) {
              int from = edge.from;
              int to = edge.to;
              sp[from].push_back(tools::mkDefNode(to));
              sp[to].push_back(tools::mkDefNode(from));
            };
        
          mst::kruskal(streets, kruskal_s);


          if(!is_first) std::cout << std::endl;
          else is_first = false;
          printf("Case #%d\n", c++);
          while(Q--) {
            int source, sink;
            while_read(source, sink);
            --source, --sink;
            int min_decibels = 0;
            tools::Dfs<> dfs_s = tools::init_dfs<>(V);
            tools::vi path;
            dfs_s.on_discover = 
              [&path]
              (tools::Node<>& node) 
              { path.push_back(node.node); }; 
            dfs_s.process_tree_edge =
             [&dfs_s]
               (const tools::Node<>& u, 
                const tools::Node<>& v) -> bool {   
              return !dfs_s.is_finished;
            };

            dfs_s.on_leaving = 
              [&path, &min_decibels, sink, nn_w, &dfs_s]
              (tools::Node<>& node) {
              if(node.node == sink) {
                for(int i = 1; i < (int)path.size(); ++i) {
                  int from = path[i - 1];
                  int to = path[i];
                  int curr_decibels = nn_w[from][to];
                  min_decibels = std::max(min_decibels, curr_decibels);
                  dfs_s.is_finished = true;
                }
              }
              path.pop_back();   
            };
            
            tools::start_vertex = source;
            auto start = tools::mkDefNode(source);
            tools::dfs<>(sp, dfs_s, start);

            printf("%s\n", !min_decibels ? "no path" : std::to_string(min_decibels).c_str());
        }
      }
    }
}