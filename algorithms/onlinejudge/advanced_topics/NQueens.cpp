/*
───────────────────────────────────────────────────────────────
🧳 UVa 11195 Another n-Queen Problem, https://onlinejudge.org/external/111/11195.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


#define LSOne(S) ((S) & (-S))

typedef long long ll;

int n, mask[32];

ll bf(int row, int col, int left_diagonal, int right_diagonal) {
  if (row == n) return 1; // done, 1 way found
  // bit = all possible column positions
  int bit = mask[row] | col | left_diagonal | right_diagonal; // list of forbidden column
  bit = ~bit; // after negation, list of allowed columns, but it turns on more bits than necessary
  bit &= (1<<n) - 1; // (1<<n) - 1, turn on n bits only, we want to concentrate on these n bits only
  ll total = 0; // now recursively count the ways
  while (bit) { // try each bit that is turned on
    int t = LSOne(bit); // the first bit that is on
    // for future iterations, forbid column t and left_diagonal/right diagonal that has t
    total += bf(row + 1, col | t, (left_diagonal|t) >> 1, (right_diagonal|t) << 1);
    bit -= t; // remove that bit t from 'bit'
  }
  return total;
}

namespace algorithms::onlinejudge::advanced_topics::n_queens
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

        int t_case = 1;
        char M[32];
        while(scanf("%d ", &n), n) {
          for(int i = 0; i < n; i++) {
            scanf("%s", &M);
            mask[i] = 0;
            for(int j = 0; j < n; j++)
              if(M[j] == '*')
                mask[i] |= (1<<j); // mark out the bad squares
          }
          printf("Case %d: %lld\n", t_case++, bf(0, 0, 0, 0));
        }
    }
}