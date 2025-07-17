/*
───────────────────────────────────────────────────────────────
🧳 UVa 825 Walking on the Safe Side, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"

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




using pii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;


// For 4-directional movement (up, right, down)
const std::vector<pii> dirs_2 = { {0, 1}, {1, 0} };


namespace algorithms::onlinejudge::graph::walking_on_safe_side
{
    /** https://onlinejudge.org/external/102/10259.pdf */
    int t_cases, N, M;
    bool in_board(int r, int c) { return r >= 0 && r < N && c >= 0 && c < M; }
    int memo[101][101];
    int count_ways(int r, int c, const vvi& blocked) {

      if(r == N - 1 && c == M - 1) return 1;

      int& ways = memo[r][c];
      if(~memo[r][c]) return memo[r][c];

      ways = 0;
      for(const auto& d : dirs_2) {
        int nr = r + d.first;
        int nc = c + d.second;
        if(in_board(nr, nc) && 
           !((bool)blocked[nr][nc])) {
          ways += count_ways(nr, nc, blocked);
        }
      }
      return ways;
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

        bool first_case = true;  
        while_read(t_cases);
        while(t_cases--) {

          // --- THE FIX ---
          if(!first_case) {
            std::cout << std::endl; // Print the blank line separator BEFORE this case
          }
          first_case = false; // It's no longer the first case

          while_read(N, M);
          vvi blocked(N, vi(M, 0));
          std::string s;
          std::getline(std::cin, s);
          for(int i = 0; i < N; ++i) {
            std::getline(std::cin, s);
            std::stringstream ss(s);
            int p, q; ss >> p;
            --p;
            while(ss >> q) {
              blocked[p][--q] = 1;
            }
          }

          std::memset(memo, -1, sizeof memo);
          std::cout << count_ways(0, 0, blocked) << std::endl;
        }
    }
}