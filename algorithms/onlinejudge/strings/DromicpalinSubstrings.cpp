/*
───────────────────────────────────────────────────────────────
🧳 UVa 12718 Dromicpalin Substrings, https://onlinejudge.org/external/127/12718.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM: DROMICPALIN SUBSTRINGS (XOR Bitmask DP)
 * ============================================================================
 * A string is a "dromicpalin" if its letters can be rearranged to form a 
 * palindrome. Mathematically, this means AT MOST ONE character can have an 
 * odd frequency.
 * 
 * THE 3D DP ATTEMPT (Frequency Counting):
 * ---------------------------------------
 * We can maintain a 3D table `cache[i][j][26]` to store the exact frequencies 
 * of all 26 characters for every substring S[i...j].
 * - Time Complexity: O(N^2 * 26)
 * - Space Complexity: O(N^2 * 26) -> ~100MB of memory for N=1000.
 * 
 * THE ELITE "XOR BITMASK" REFACTOR (The O(1) State):
 * --------------------------------------------------
 * Since we only care about whether a character's frequency is ODD or EVEN, we 
 * can represent the entire 26-character frequency state as a single 32-bit 
 * integer (bitmask), where the c-th bit is 1 if character 'c' is odd.
 * 
 * 1. STATE TRANSITION:
 *    When extending the substring from S[i...j-1] to S[i...j] by adding S[j], 
 *    the odd/even state of character S[j] is toggled. In binary, we perform 
 *    this toggle using the XOR (^) operator in O(1) time:
 *         mask[i][j] = mask[i][j-1] ^ (1 << (S[j] - 'a'))
 * 
 * 2. THE CHUNK CHECK:
 *    A mask has at most one bit set to 1 if and only if:
 *         (mask & (mask - 1)) == 0
 *    This allows us to verify if a substring is a dromicpalin in O(1) time!
 * 
 * BENEFITS:
 * - Space Complexity: Drops from 100MB to 4MB (O(N^2) instead of O(N^2 * 26)).
 * - Time Complexity: Drops from 26 million operations to 1 million operations.
 * - This optimization completely avoids any loop over 'c' from 0 to 25!
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



int cache[1001][1001][26];

namespace algorithms::onlinejudge::strings::dromicpalin_substrings
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
        while(t_cases--) {
          std::string str;
          std::cin >> str;

          std::memset(cache, 0, sizeof(cache)); // Reset the cache for each test case

          for(int i = 0; i < (int)str.size(); ++i) {
            cache[i][i][str[i] - 'a'] = 1; // Initialize single character substrings
          }

          int s = (int)str.size();
          for(int l = 2; l <= s; ++l) {
            for(int i = 0; i <= s - l; ++i) {
              int j = i + l - 1;
              // Update the cache for the current substring
              for(int c = 0; c < 26; ++c) {
                cache[i][j][c] = cache[i][j - 1][c];
              }
              cache[i][j][str[j] - 'a']++;
            }
          }

          int dromicpalin_count = 0;
          for(int l = 1; l <= s; ++l) {
            for(int i = 0; i <= s - l; ++i) {
              int j = i + l - 1;
              bool is_dromicpalin = true;
              int odd_count = 0;
              for(int c = 0; c < 26; ++c) {
                if(cache[i][j][c] % 2 != 0) {
                  odd_count++;
                  if(odd_count > 1) {
                    is_dromicpalin = false;
                    break;
                  }
                }
              }
              if(is_dromicpalin) {
                dromicpalin_count++;
              }
            }
          }
          std::cout << "Case " << t_case++ << ": " << dromicpalin_count << "\n";
        }
    }
}