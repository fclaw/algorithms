/*
───────────────────────────────────────────────────────────────
🧳 UVa 12747 Back to Edit Distance, https://onlinejudge.org/external/127/12747.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM: EDIT DISTANCE WITH INSERT/DELETE ONLY VIA LCS-to-LIS REDUCTION
 *            (Back to Edit Distance - UVa 12747)
 * ============================================================================
 * THE PROBLEM & THE REPLACEMENT CONSTRAINT:
 * We are given two permutations of the integers 1 to N (N <= 200,000). 
 * We must find the minimum number of edit operations to make them identical.
 * Crucially, only TWO operations are allowed: INSERT and DELETE. 
 * REPLACEMENT (Change) is strictly forbidden.
 * 
 * THE MATHEMATICAL DERIVATION:
 * 1. Let L be the length of the Longest Common Subsequence (LCS) of A and B.
 * 2. Since we cannot perform replacements, the characters in the LCS are 
 *    the "backbone" that remains completely untouched.
 * 3. Any character in A that is NOT in the LCS must be deleted:
 *         Deletions = N - L
 * 4. Any character in B that is NOT in the LCS must be inserted:
 *         Insertions = N - L
 * 
 * Therefore, the total minimum operations (Edit Distance) is exactly:
 *      Total Ops = Deletions + Insertions
 *                = (N - L) + (N - L)
 *                = 2 * (N - L)
 * 
 * THE $O(N \log N)$ REDUCTION:
 * Because both sequences are permutations of the exact same set of integers [1..N],
 * every element is guaranteed to be unique. This allows us to map the first 
 * permutation to its index sequence [1..N] using a Direct Addressing Table (DAT).
 * 
 * By mapping the second permutation into these indices, our LCS problem 
 * collapses into finding the Longest Increasing Subsequence (LIS).
 * 
 * Using C++'s std::lower_bound (active tails binary search), we can find 
 * the LIS in O(N log N) time, completely bypassing the O(N^2) LCS table.
 * 
 * COMPLEXITY:
 * - Time Complexity:  O(N log N) — processing 200,000 elements in ~0.2 seconds.
 * - Space Complexity: O(N) — requiring under 2MB of memory for the DAT.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;


// Returns the length of the Longest Increasing Subsequence in O(N log N)
int lis(const vi&  seq) {
  if (seq.empty()) 
    return 0;

  // tails[i] stores the smallest tail of all active increasing 
  // subsequences of length i+1 encountered so far.
  vi tails;

  for(int x : seq) {
    // Use binary search (O(log N)) to find the first element 
    // in 'tails' that is greater than or equal to 'x'
    auto it = std::lower_bound(tails.begin(), tails.end(), x);

    if (it == tails.end()) {
      // x is larger than any tail we've seen so far. 
      // This means we can extend the longest subsequence!
      tails.push_back(x);
    } else {
      // x can be used to make a shorter/better tail for an 
      // existing subsequence of some length. We overwrite it.
      *it = x;
    }
  }

  // The length of the 'tails' vector is the length of the LIS!
  return tails.size();
}


namespace algorithms::onlinejudge::strings::back_to_edit_distance
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

        int t_cases, t_case = 1;
        std::cin >> t_cases;
        std::cin.ignore();
        while(t_cases--) {
          int N, val;
          std::cin >> N;
          vi f_perm_val_to_index(N + 1);
          for(int idx = 1; idx <= N; ++idx) {
            std::cin >> val;
            f_perm_val_to_index[val] = idx;
          }

          vi f_perm_idx_order_in_s_perm;
          for(int i = 0; i < N; ++i) {
            std::cin >> val;
            int idx = f_perm_val_to_index[val];
            f_perm_idx_order_in_s_perm.push_back(idx);
          }
           
          int els_out_of_order = N - lis(f_perm_idx_order_in_s_perm);
        
          printf("Case %d: %d\n", t_case++, 2 * els_out_of_order);
        }
    }
}