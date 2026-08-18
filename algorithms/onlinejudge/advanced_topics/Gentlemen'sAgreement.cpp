/*
───────────────────────────────────────────────────────────────
🧳 UVa 11065 AGentlemen’s Agreement, https://onlinejudge.org/external/110/11065.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 

using vi = std::vector<uint64_t>;


int V, E;

void backtrack(int u, uint64_t used, int depth, const vi& adj_matrix, int& num_of_is, int& mis) {
  
  if(__builtin_popcountll(used) == V) {
   num_of_is++;
   mis = std::max(mis, depth);
   return;
  }

  for(int v = u; v < V; ++v) {
    if(!(used & (1ULL << v))) {
      backtrack(v + 1, used | adj_matrix[v], depth + 1, adj_matrix, num_of_is, mis);
    }
  }
}


namespace algorithms::onlinejudge::advanced_topics::gentlemen_s_agreement
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
        
        int t_cases;
        std::cin >> t_cases;
        while(t_cases--) {
          std::cin >> V >> E;
          vi adj_matrix(V);
          for(int v = 0; v < V; ++v) {
            adj_matrix[v] = (1ULL << v);
          }
          int from, to;
          for(int e = 0; e < E; ++e) {
            std::cin >> from >> to;
            adj_matrix[from] |= (1ULL << to);
            adj_matrix[to] |= (1ULL << from);
          }


          int num_of_is = 0;
          int mis = 0;
          backtrack(0, 0ULL, 0, adj_matrix, num_of_is, mis);
          printf("%d\n%d\n", num_of_is, mis);
        }
    }
}
