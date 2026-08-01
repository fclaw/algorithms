/*
────────────────────────────────────────────────────────────────────────────────
🧳 UVa 12841 - In Puzzleland (III)
   URL: https://onlinejudge.org/external/128/12841.pdf
   Verdict: Accepted | Runtime: ~ 0.510s
───────────────────────────────────────────────────────────────────────────────
*/


#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



struct Node
{
    int idx;
    char letter;
};

using v_node = std::vector<Node>;
using vv_node = std::vector<v_node>; 
using vi = std::vector<int>;

struct Ans
{
    bool is_cached;
    bool is_feasible;
    std::vector<char> path;
};

bool is_prev_lexicographically_smaller(const std::vector<char>& curr, const std::vector<char>& in) {
  if(curr.empty()) {
    return true;
  }
  return in < curr;
}


 int Nodes, Edges;


using v_ans = std::vector<Ans>;
using vv_ans = std::vector<v_ans>;

char find_letter(int u, const std::vector<std::pair<int, char>>& indices) {
  return std::find_if(indices.begin(), indices.end(), [u](const std::pair<int, char>& val) { return val.first == u; })->second;
}


Ans does_path_exist(int u, int sink, const vv_node& graph, int visited, vv_ans& cache, const std::vector<std::pair<int, char>>& indices) {
   
    if(u == sink) {
      if(__builtin_popcount(visited) == Nodes) {
         return (cache[u][visited] = {true, true, {find_letter(sink, indices)}});
      } else {
        return (cache[u][visited] = {true, false, {}});
      }
    }
    
    if(cache[u][visited].is_cached) {
      return cache[u][visited];
    }
     
    std::vector<char> tail = {};
    Ans ans = {true, false, {}};
    for(auto node : graph[u]) {
      int bit = (1 << node.idx);
      if(!(visited & bit)) {
        Ans prev = does_path_exist(node.idx, sink, graph, visited | bit, cache, indices);
        if(prev.is_feasible) {
           ans.is_feasible = true;
          if(is_prev_lexicographically_smaller(tail, prev.path)) {
            tail = prev.path;
          }
        }
      }
    }

    if(ans.is_feasible) {
      tail.insert(tail.begin(), find_letter(u, indices));
      ans.path = tail;
    }

    return (cache[u][visited] = ans);
}


int find_idx(char node, const std::vector<std::pair<int, char>>& indices) { 
  return std::find_if(indices.begin(), indices.end(), [node](const std::pair<int, char>& val) { return val.second == node; })->first; 
}

namespace algorithms::onlinejudge::dp::puzzle_land
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }


        int t_cases, t_case = 1;
        std::cin >> t_cases;
        while(t_cases--) {
          std::cin >> Nodes >> Edges;
          std::vector<std::pair<int, char>> indices;
          char node;
          for(int n = 0; n < Nodes; ++n) {
            std::cin >> node;
            indices.push_back({n, node});
          }
          vv_node graph(Nodes);
          char from, to;
          for(int e = 0; e < Edges; ++e) {
            std::cin >> from >> to;
            auto fidx = find_idx(from, indices);
            auto tidx = find_idx(to, indices);
            graph[fidx].push_back({tidx, to});
            graph[tidx].push_back({fidx, from});
          }
          vv_ans cache(Nodes + 1, v_ans((1 << Nodes) + 1, {false, false, {}}));
          int source = indices.front().first;
          int sink = indices.back().first;
          int visited = 0 | (1 << indices.front().first);
          Ans ans = does_path_exist(source, sink, graph, visited, cache, indices);
          std::string path;
          if(ans.is_feasible) {
            for(char n : ans.path) {
              path += n;
            }
          } else {
            path = "impossible";
          }
          printf("Case %d: %s\n", t_case++, path.c_str());
        }
    }
}