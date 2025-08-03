
 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 11419 SAM I AM, MVC Konig theorem, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/mcbm.cpp"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;

using vi = std::vector<int>;
using vb = std::vector<bool>;
using vvb = std::vector<vb>;


namespace algorithms::onlinejudge::graph::serious_sam_i_am
{
    /** https://onlinejudge.org/external/114/11419.pdf */
    int rows_n, cols_n, enemies_n;
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
        
        while(while_read(rows_n, cols_n, enemies_n)) {
          if(rows_n == 0 && cols_n == 0 && enemies_n == 0) break;

          vi row_enemies(rows_n);
          vi col_enemies(cols_n);

          vvb enemies(rows_n, vb(cols_n));
          for(int i = 0; i < enemies_n; ++i) {
            int r, c;
            while_read(r, c);
            --r, --c;
            enemies[r][c] = true;
            ++row_enemies[r];
            ++col_enemies[c];
          }

          int L_SIZE = rows_n;
          int R_SIZE = cols_n;
          mcmb::vvi graph(L_SIZE);
          for(int row_id = 0; row_id < L_SIZE; ++row_id) {
            for(int col_id = 0; col_id < R_SIZE; ++col_id) {
              if(enemies[row_id][col_id]) {
                graph[row_id].push_back(col_id);
              }
            }
          }

          mcmb::kuhn kuhn_s(R_SIZE);
          for(int row_id = 0; row_id < L_SIZE; ++row_id) {
            kuhn_s.visited.assign(L_SIZE, false);
            mcmb::try_kuhn(row_id, graph, kuhn_s);
          }

          int min_shots = 0;
          // Step 1: Find unmatched left-side vertices (rows)
          vb is_row_matched(L_SIZE, false);
          for(int row_id : kuhn_s.match) {
            if(row_id != mcmb::sentinel) {
              ++min_shots;
              is_row_matched[row_id] = true;
             }
          }

          // Step 2: Traverse from all unmatched rows
          vb visited_L(L_SIZE, false);
          vb visited_R(R_SIZE, false);
          std::function<void(int)> dfs = [&](int u) {
            visited_L[u] = true;
            for(int v : graph[u]) { 
              // Edges not in matching
              // We know (u,v) is not a matched edge from the way the search is structured
              // because we started from an unmatched 'u'.
              // The edge we care about is the reverse one.
              if(kuhn_s.match[v] != u && 
                 !visited_R[v]) { // subtle point
                visited_R[v] = true;
                int u_prime = kuhn_s.match[v];
                if (u_prime != mcmb::sentinel && 
                    !visited_L[u_prime]) {
                  dfs(u_prime);
                }
              }
            }
          };


          for(int row_id = 0; row_id < L_SIZE; ++row_id) {
            if(!is_row_matched[row_id]) dfs(row_id);
          }

          // Step 3: Construct the MVC set
          std::vector<std::string> shots;
          // Add all unvisited rows 
          for(int r = 0; r < L_SIZE; ++r) {
            if(!visited_L[r]) {
              shots.push_back("r" + std::to_string(r + 1));
            }
          }
          // Add all visited columns
          for(int c = 0; c < R_SIZE; ++c) {
            if(visited_R[c]) {
              shots.push_back("c" + std::to_string(c + 1));
            }
          }

          std::string shots_str;
          for(const auto& shot : shots) {
            shots_str += shot + " ";
          }
          shots_str.pop_back();
          std::cout << min_shots <<  " " << shots_str << std::endl;
        }
    }
}