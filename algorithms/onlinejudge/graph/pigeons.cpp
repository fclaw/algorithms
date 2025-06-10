/*
───────────────────────────────────────────────────────────────
🧳 UVa 10765 Doves and Bombs, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dfs.cpp"

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
#include <set>



namespace tools = algorithms::onlinejudge::graph::tools;

struct Bomb
{
    int node;
    int pigeon_index;
};

std::ostream& operator << (std::ostream& os, const Bomb& bomb) 
{ return os << "{" << bomb.node << ", " << bomb.pigeon_index << "}"; }


bool operator < (const Bomb& lhs, const Bomb& rhs) 
{ return lhs.pigeon_index > rhs.pigeon_index || 
         (lhs.pigeon_index == rhs.pigeon_index && 
          lhs.node < rhs.node); 
}


namespace algorithms::onlinejudge::graph::pigeons
{
    /** https://onlinejudge.org/external/107/10765.pdf */
    int V, M;
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

        while(while_read(V, M) && V && M) {
          tools::vv_def_node railways(V);
          int from, to;
          while(while_read(from, to) && 
                from != -1 && 
                to != -1) {
            railways[from].push_back({to, {}});
            railways[to].push_back({from, {}});
          }
          
          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          tools::init_cut_points(V);

          dfs_s.on_discover = 
            [](tools::Node<>& u) 
            { tools::init_ancestor(u.node); };
          dfs_s.process_tree_edge = 
            [&dfs_s](const tools::Node<>& u, 
                     const tools::Node<>& v) -> bool {           
              tools::incr_tree_out_degree(u.node); 
              return true; 
            };
          dfs_s.process_back_edge = 
            [&dfs_s](const tools::Node<>& u, 
                     const tools::Node<>& v) { 
              tools::set_ancestor(u.node, v.node, dfs_s);
            };
          dfs_s.on_leaving = 
             [&dfs_s](tools::Node<>& u) 
             { tools::detect_cut_points(u.node, dfs_s); };

          for(int v = 0; v < V; ++v) {
            if(dfs_s.state[v] == tools::Unvisited) {
              tools::Node<> start_v = tools::def_node;
              start_v.node = v;
              tools::start_vertex = v;
              tools::dfs<>(railways, dfs_s, start_v);
            }
          }
          
          std::set<Bomb> bombs;
          for(int v = 0; v < V; ++v)
            bombs.insert({v, 1});

          for(int i = 0; i < V; ++i) {
            auto n = tools::cut_nodes[i];
            if(n.count(tools::Bridge) || 
               n.count(tools::Root) || 
               n.count(tools::Parent)) {
              tools::Dfs<> dfs_s = tools::init_dfs<>(V);
              int cc_n = 0;
              for(int v = 0; v < V; ++v) {
                if(dfs_s.state[v] == 
                   tools::Unvisited && 
                   v != i) {
                  dfs_s.process_tree_edge = 
                    [&dfs_s, i](const tools::Node<>& u, 
                             const tools::Node<>& v) -> bool
                    { return u.node != i && v.node != i; };
                  tools::Node<> start_v = tools::def_node;
                  start_v.node = v;
                  tools::start_vertex = v;
                  tools::dfs<>(railways, dfs_s, start_v);
                  cc_n++;
                }
              }
              
              auto cmp = [i](const Bomb& b) { return b.node == i; };
              auto it = std::find_if(bombs.begin(), bombs.end(), cmp);
              if (it != bombs.end()) {
                  Bomb updated = *it;
                  bombs.erase(it);
                  updated.pigeon_index = cc_n;
                  bombs.insert(updated);
              }
            }
          }
          int m = 0;
          for(auto b : bombs)
            if(++m <= M) std::cout << b.node << " " << b.pigeon_index << std::endl;
          std::cout << std::endl;  
        }
    }
}