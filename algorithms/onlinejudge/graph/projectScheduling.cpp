/*
───────────────────────────────────────────────────────────────
🧳 UVa 452 Project Scheduling, rt: s
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
#include <set>




namespace tools = algorithms::onlinejudge::graph::tools;

using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vb = std::vector<bool>;
constexpr int V = 27;


namespace algorithms::onlinejudge::graph::project_scheduling
{
    /** https://onlinejudge.org/external/4/452.pdf */
    int t_cases;
    int uof_to_idx(char c) {
      // Optional: Add a check for robustness, though not always needed
      // in competitive programming if the input is guaranteed.
      if(c < 'A' || c > 'Z') {
        // Handle error: character is not an uppercase letter.
        // For example, throw an exception or return -1.
        throw std::out_of_range("Character is not an uppercase letter");
      } 
      return c - 'A';
    }
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

        while_read(t_cases);
        std::cin.ignore();
        std::cin.ignore();
        while(t_cases--) {
          std::string in;
          tools::Graph<> graph(V);
          vi times(V);
          vb is_in_degree_zero(V, true);
          vb is_active(V, false);
          while(std::getline(std::cin, in)) {
            if(in.empty()) break;
            std::stringstream ss(in);
            int tm;
            char unit_of_work;
            ss >> unit_of_work >> tm;
            int v = uof_to_idx(unit_of_work);
            times[v] = tm;
            is_active[v] = true;
            
            while(ss >> unit_of_work) {
              if(is_in_degree_zero[v]) 
                is_in_degree_zero[v] = false;
              if(!std::isupper(unit_of_work)) continue;
              int u = uof_to_idx(unit_of_work);
              graph[u].push_back(tools::mkDefNode(v));
            }
          }

          tools::TopSortKahn khan = tools::top_sort_kahn(V, graph);
          // Initialize the finish times for source nodes (those with no prerequisites)
          // In your graph model, these would be nodes with an in-degree of 0.
          vi finish_time(V, 0);
          for(int i = 0; i < V; ++i) {
            if(is_active[i] && is_in_degree_zero[i]) { // is_active checks if the task exists
              finish_time[i] = times[i];
            }
          }

          //Iterate through the nodes in the order given by the topological sort.
          for(int u : khan.top_sort) {   
            // For each neighbor v of u...
            for(const auto& neigh : graph[u]) {
              int v = neigh.node;
              // The start time for v must be after u finishes.
              // So, the finish time for v is the max of its current earliest start + its own time,
              // or u's finish time + v's own time.
              finish_time[v] = std::max(finish_time[v], finish_time[u] + times[v]);
            }
          }

          int max_time_to_complete = 0;
          for(int v = 0; v < V; ++v) {
            if(is_active[v])
              max_time_to_complete = std::max(max_time_to_complete, finish_time[v]);
          }

          std::cout << max_time_to_complete << std::endl;
          if(t_cases) std::cout << std::endl;
        }
    }
}