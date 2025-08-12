/*
───────────────────────────────────────────────────────────────
🧳 UVa 12502 Three Families, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::three_families
{
    /** https://onlinejudge.org/external/125/12502.pdf */
    int t_cases, reward, family_a_tm, family_b_tm;
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
          while_read(family_a_tm, family_b_tm, reward);
          int total_tm = family_a_tm + family_b_tm;
          int family_a_sup_tm = 3 * family_a_tm - total_tm;
          int family_b_sup_tm = 3 * family_b_tm - total_tm;
          int family_a_share = reward * family_a_sup_tm / (family_b_sup_tm + family_a_sup_tm);
          std::cout << family_a_share << std::endl;
        }
    }
}