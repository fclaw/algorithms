/*
───────────────────────────────────────────────────────────────
🧳 UVa 1056 Degrees of Separation, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int inf = 1e5;


using vi = std::vector<int>;
using vvi = std::vector<vi>;
using map_si = std::unordered_map<std::string, int>;


namespace algorithms::onlinejudge::graph::degrees_of_separation
{
    /** https://onlinejudge.org/external/10/1056.pdf */
    int p, r, t_cases = 1;
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

        while(while_read(p, r) && p && r) {
          int idx = 0;
          vvi relation_matrix(p, vi(p, inf));
          map_si name_to_idx;
          for (int i = 0; i < r; i++) {
            std::string name1, name2;
            while_read(name1, name2);
            auto end = name_to_idx.end();
            if(name_to_idx.find(name1) == end) {
              name_to_idx[name1] = idx++;
            }
            if(name_to_idx.find(name2) == end) {
              name_to_idx[name2] = idx++;
            }
            int idx1 = name_to_idx[name1];
            int idx2 = name_to_idx[name2];
            relation_matrix[idx1][idx2] = 1;
            relation_matrix[idx2][idx1] = 1;
          }

          for(int k = 0; k < p; ++k) {
            for(int i = 0; i < p; ++i) {
              for(int j = 0; j < p; ++j) {
                auto& d_ij = relation_matrix[i][j];
                auto d_ik = relation_matrix[i][k];
                auto d_kj = relation_matrix[k][j];
                if(d_ik == inf || d_kj == inf) continue;
                d_ij = std::min(d_ij, d_ik + d_kj);
              }
            }
          }

          int max_degree_of_separation = 0;
          bool is_possible = true;
          for(int i = 0; i < p; ++i) {
            for(int j = 0; j < p; ++j) {
              if(i == j) continue;
              if(relation_matrix[i][j] == inf) {
                is_possible = false;
                break;
              }
              max_degree_of_separation = std::max(max_degree_of_separation, relation_matrix[i][j]);
            }
          }
          if(is_possible)
            printf("Network %d: %d\n\n", t_cases++, max_degree_of_separation);
          else printf("Network %d: DISCONNECTED\n\n", t_cases++);
        }
    }
}