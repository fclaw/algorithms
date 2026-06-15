/*
───────────────────────────────────────────────────────────────
🧳 UVa 11258 String Partition, https://onlinejudge.org/external/112/11258.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * DP TRANSITION LOGIC & THE "FULL PREFIX" BASE CASE
 * ============================================================================
 * 
 * THE MATHEMATICAL MODEL:
 * Let dp[i] be the maximum sum obtainable from the substring str[0...i].
 * To find dp[i], we split the substring at an index 'k'. 
 * The left part is the previously solved problem: dp[k].
 * The right part is the new number: str[k+1...i].
 * 
 * Formula: dp[i] = max_{0 <= k < i} ( dp[k] + number(k+1, i) )
 * 
 * THE 0-BASED INDEXING TRAP:
 * If we strictly follow the formula above with a 0-based index loop:
 *    for (k = 0; k < i; ++k) { ... dp[k] + num(k+1, i) ... }
 * 
 * We encounter a fatal logic gap! The right part (the new number) ALWAYS 
 * begins at index `k+1`. Because the lowest possible `k` is 0, the new number 
 * can never start at index 0. 
 * 
 * Example: str = "123"
 *   k=0 -> dp[0] ("1") + num("23")
 *   k=1 -> dp[1] ("12") + num("3")
 * The algorithm forces a split and NEVER evaluates the possibility that the 
 * entire string "123" is just a single valid number.
 * 
 * THE TWO SOLUTIONS:
 * ------------------
 * Option 1 (Explicit Base Case): 
 * Explicitly evaluate `num(0, i)` outside the inner loop to ensure the 
 * "un-split" scenario is considered for every prefix.
 * 
 * Option 2 (1-Based DP Table - Recommended):
 * Shift the meaning of the DP table. Let dp[i] mean "the max sum of the 
 * first i characters." We introduce a dummy state: dp[0] = 0.
 * Now, the loop can cleanly evaluate the entire string in one go:
 *    k=0 -> dp[0] (0) + num(0, i-1) 
 * This treats the "un-split" string as being "split" from an empty prefix, 
 * unifying the math and removing the need for special edge-case checks!
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<long long>;



// Parses str[i...j] (inclusive) into a 32-bit integer
// Returns -1 if it overflows INT_MAX
long long stringToInt32(const std::string& str, int i, int j) {

  // Check for leading zero rule: "0" is fine, "05" is illegal
  if (str[i] == '0' && i != j) return -1;
    
  long long res = 0;
  long long limit = INT_MAX / 10;        // 214748364
  long long limit_digit = INT_MAX % 10;  // 7

  // Loop strictly from index i to index j
  for (int k = i; k <= j; ++k) {
    char c = str[k];
    int digit = c - '0';

    // --- THE OVERFLOW PRE-CHECK ---
    if (res > limit || 
        (res == limit && 
         digit > limit_digit)) {
      return -1; // Exceeds max
    }

    // Safe to accumulate
    res = res * 10 + digit;
  }
  return res;
}


long long max_sum(const std::string& str) {
  vi dp(str.size(), 0);
  for(int i = 0; i < (int)str.size(); ++i) {

    // Base Case Check: Can the entire string from 0 to i be ONE number?
    // (Only bother checking if the length is <= 10)
    if (i < 10) {
      long long full_num = stringToInt32(str, 0, i);
      if (full_num != -1) {
        dp[i] = full_num;
      }
    }
    
    for(int k = 0; k < i; ++k) {
      long long num = stringToInt32(str, k + 1, i);
      if(num == -1) continue;
      dp[i] = std::max(dp[i], dp[k] + num);
    }
  }

  return dp[str.size() - 1];
}


namespace algorithms::onlinejudge::strings::string_partition
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

        int t_cases;
        std::cin >> t_cases;
        std::cin.ignore();
        while(t_cases--) {
          std::string str;
          std::getline(std::cin, str);
          std::cout << max_sum(str) << std::endl;
        }
    }
}