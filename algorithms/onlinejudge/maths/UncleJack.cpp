/*
───────────────────────────────────────────────────────────────
🧳 UVa 11115 Uncle Jack, https://onlinejudge.org/external/111/11115.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>


namespace bg = algorithms::onlinejudge::maths::utility::big_integer;


using ull = unsigned long long;
using vi = std::vector<int>;



/*
 * This function uses a backtracking approach to solve the classic combinatorial problem:
 * "How many ways can you distribute 'n_cds' distinct items to 'n_nephews' distinct bins?"
 *
 * The problem can be modeled as a decision tree:
 * - DEPTH: The tree has a depth of 'n_cds'. Each level 'curr_cd' represents the
 *   decision for the 'curr_cd'-th CD.
 *
 * - BRANCHING FACTOR: At each node (for each CD), there are 'n_nephews' possible
 *   choices (branches), one for each nephew who could receive that CD.
 *
 * - LEAVES: A complete path from the root to a leaf represents one full, valid
 *   distribution of all CDs. The function returns 1 for each leaf found. The sum
 *   of these returns is the total number of possible distributions.
 *
 * - FINAL FORMULA: Since each of the 'n_cds' CDs can be independently given to any
 *   of the 'n_nephews', the total number of ways is simply n_nephews ^ n_cds.
 *   This backtracking function serves as an exhaustive search to compute that same value.
 *
 * NOTE ON IMPLEMENTATION:
 * The `curr_share` bitmask is used to track assignments. In this specific recursive
 * structure, the check `if(!(curr_share[i] & (1 << curr_cd)))` is redundant,
 * as the 'curr_cd'-th bit for any nephew will never be set when the function is
 * called for that CD. It's a defensive check.
 * distribute_cds(..., nephews=2, cds=1) -> returns 2
 * distribute_cds(..., nephews=2, cds=2) -> returns 4
 * distribute_cds(..., nephews=2, cds=3) -> returns 8
 * distribute_cds(..., nephews=3, cds=1) -> returns 3
 * distribute_cds(..., nephews=3, cds=2) -> returns 9
 */
ull distribute_cds(int curr_cd, int n_nephews, int n_cds, vi& curr_share) {
  if(curr_cd == n_cds) return 1;

  ull ways = 0;
  for(int i = 0; i < n_nephews; i++) {
    if(!(curr_share[i] & (1 << curr_cd))) {
      curr_share[i] |= (1 << curr_cd);
      ways += distribute_cds(curr_cd + 1, n_nephews, n_cds, curr_share);
    }
  }
  return ways;
}

namespace algorithms::onlinejudge::maths::uncle_jack
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

        int nephews, cds;
        while(scanf("%d %d", &nephews, &cds) == 2 && 
              !(nephews == 0 && cds == 0)) {
          // vi curr_share(nephews);
          // printf("%llu\n", distribute_cds(0, nephews, cds, curr_share));
          bg::bigint nephews_big(nephews);
          bg::bigint cds_big(cds);
          printf("%s\n", bg::big_pow(nephews_big, cds_big).getRawRep().c_str());
        }
    }
}