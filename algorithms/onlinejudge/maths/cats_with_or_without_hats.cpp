/*
───────────────────────────────────────────────────────────────
🧳 UVa 10493 Cats, with or without Hats, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include <bits/stdc++.h>






namespace algorithms::onlinejudge::maths::cats_with_or_without_hats
{
    /** https://onlinejudge.org/external/104/10493.pdf */
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
        
        int branch_factor, leaves;
        while(scanf("%d %d", &branch_factor, &leaves) == 2 && branch_factor != 0 && leaves != 0) {
          if(branch_factor == 1 || leaves == 1) {
            printf("%d %d Multiple\n", branch_factor, leaves);
          } else if(((leaves - 1) % (branch_factor - 1)) == 0) {
            int total_nodes = leaves + (leaves - 1) / (branch_factor - 1);
            printf("%d %d %d\n", branch_factor, leaves, total_nodes);
          } else if ((leaves - 1) % (branch_factor - 1) == 1) {
            printf("%d %d impossible\n", branch_factor, leaves);
          }
        }
    }
}