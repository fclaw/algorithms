/*
───────────────────────────────────────────────────────────────
🧳 UVa 12335 Lexicographic Order, https://onlinejudge.org/external/123/12335.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>


namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

using ull = unsigned long long;
using vull = std::vector<ull>;


// from 0 to 20
std::unordered_map<int, ull> factorials = 
  { {1, 1},
    {2, 2},
    {3, 6},
    {4, 24},
    {5, 120},
    {6, 720},
    {7, 5040},
    {8, 40320},
    {9, 362880},
    {10, 3628800},
    {11, 39916800},
    {12, 479001600},
    {13, 6227020800},
    {14, 87178291200},
    {15, 1307674368000},
    {16, 20922789888000},
    {17, 355687428096000},
    {18, 6402373705728000},
    {19, 121645100408832000},
    {20, 2432902008176640000}
  };


void restore_original_positions(const std::string& perm, ull pos_in_perm, std::unordered_map<char, double>& original_positions) {
}


namespace algorithms::onlinejudge::maths::lexicographic_order
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


        int n_cases, t_case = 1;
        ull pos_in_perm;
        std::string perm;
        scanf("%d", &n_cases);
        while(n_cases--) {
          while_read(perm, pos_in_perm);
          std::unordered_map<char, double> original_positions;
          restore_original_positions(perm, pos_in_perm, original_positions);
          std::string original_perm(perm.size(), ' ');
          for(auto& t : original_positions)
            original_perm[t.second] = t.first;
          printf("Case %d: %s\n", t_case++, original_perm.c_str());
        }
    }
}