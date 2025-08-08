 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa  10129 Play on Words, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




constexpr int MAX_LETTERS = 26;

using vi = std::vector<int>;
using vvi = std::vector<vi>;


bool check_degrees(const vi& in_degree, const vi& out_degree, int& start_node) {
    int start_candidates = 0;
    int end_candidates = 0;
    start_node = -1; // Initialize to an invalid state

    for (int i = 0; i < MAX_LETTERS; ++i) {
        // --- Find a potential start node for the connectivity check ---
        // This can be any node that is part of the graph.
        if (start_node == -1 && (in_degree[i] > 0 || out_degree[i] > 0)) {
            start_node = i;
        }

        // --- Check the Eulerian path/circuit conditions ---
        if (in_degree[i] == out_degree[i]) {
            // This is a valid "intermediate" node. Continue.
            continue;
        } 
        else if (out_degree[i] == in_degree[i] + 1) {
            // This could be the start of an Eulerian path.
            start_candidates++;
        } 
        else if (in_degree[i] == out_degree[i] + 1) {
            // This could be the end of an Eulerian path.
            end_candidates++;
        } 
        else {
            // The degrees are unbalanced in a way that is never allowed.
            return false;
        }
    }

    // --- Final Verdict ---
    // A. Condition for an Eulerian Circuit: all nodes are balanced.
    if (start_candidates == 0 && end_candidates == 0) {
        return true; 
    }

    // B. Condition for an Eulerian Path: exactly one start and one end.
    if (start_candidates == 1 && end_candidates == 1) {
        // For a path, we MUST start the traversal at the unique start node.
        // We need to find it and update our start_node parameter.
        for (int i = 0; i < MAX_LETTERS; ++i) {
            if (out_degree[i] == in_degree[i] + 1) {
                start_node = i;
                break;
            }
        }
        return true;
    }

    // If neither condition is met, the configuration is invalid.
    return false;
}

bool is_connected(int source, int active_nodes, const vvi& graph) {
  
   uint64_t visited = 0;
   std::function<void(int)> do_dfs =
     [&](int node) {
      visited |= (1LL << node);      
       for(int neigh : graph[node]) {
         if(!(visited & (1LL << neigh)))
           do_dfs(neigh);
       }
     };
   do_dfs(source);
   return __builtin_popcountll(visited) == active_nodes;
}


namespace algorithms::onlinejudge::graph::play_on_words
{
    /** https://onlinejudge.org/external/101/10129.pdf */
    int t_cases, plates_n;
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
        while(t_cases--) {
          while_read(plates_n);
          vi in_degree(MAX_LETTERS);
          vi out_degree(MAX_LETTERS);
          vvi graph(MAX_LETTERS);
          for(int plate_id = 0; plate_id < plates_n; ++plate_id) {
            std::string plate;
            while_read(plate);
            int from = plate.front() - 'a';
            int to = plate.back() - 'a';
            graph[from].push_back(to);
            in_degree[to]++;
            out_degree[from]++;
          }

          int active_nodes = 0;
          for(int i = 0; i < MAX_LETTERS; ++i) {
            if(!in_degree[i] && !out_degree[i]) continue;
            active_nodes++;
          }

          int source = -1;
          bool is_eulerian = 
            check_degrees(in_degree, out_degree, source) && 
            is_connected(source, active_nodes, graph);
          printf(is_eulerian ? "Ordering is possible.\n" : "The door cannot be opened.\n");
        }
    }
}