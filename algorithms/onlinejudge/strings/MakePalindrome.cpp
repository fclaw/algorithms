/*
───────────────────────────────────────────────────────────────
🧳 UVa 10453 Make Palindrome, https://onlinejudge.org/external/104/10453.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;

using vb = std::vector<std::bitset<1001>>;
using vvb = std::vector<vb>;



std::string build_min_palindrome(const std::string& str, const std::bitset<1001>& in_lps_bitset) {
  // 1. Calculate the exact final length mathematically
  int final_length = str.length() + (str.length() - in_lps_bitset.count());

  // 2. Pre-allocate the result string with spaces
  std::string min_palindrome(final_length, ' ');

  // 3. Setup four pointers
  int i = 0;                  // Left pointer for the original string 's'
  int j = str.length() - 1;     // Right pointer for the original string 's'

  int L_ptr = 0;              // Left pointer for the new string 'min_palindrome'
  int R_ptr = final_length - 1; // Right pointer for the new string 'min_palindrome'

  // 4. Build from the outside inward
  while (i <= j) {
    if (in_lps_bitset[i] && in_lps_bitset[j]) {
      // Both are in the LPS skeleton. They match.
      // Place them in their respective mirrored slots.
      min_palindrome[L_ptr++] = str[i];
        
      // If they aren't the exact same middle character, place the right one too
      if (i != j) {
        min_palindrome[R_ptr--] = str[j];
      } else {
        // For odd-length LPS, L_ptr and R_ptr will meet at the same spot
        // The assignment res[L_ptr++] already handled it!
      }
      i++; 
      j--;
    }
    else if (!in_lps_bitset[j]) {
      // Character at 'j' is missing from the LPS.
      // It belongs on the right, so we must mirror it to the left!
      min_palindrome[L_ptr++] = str[j];
      min_palindrome[R_ptr--] = str[j];
      j--; // Move inward on the original string
    }
    else if (!in_lps_bitset[i]) {
      // Character at 'i' is missing from the LPS.
      // It belongs on the left, so we must mirror it to the right!
      min_palindrome[L_ptr++] = str[i];
      min_palindrome[R_ptr--] = str[i];
      i++; // Move inward on the original string
    }
  }

  return min_palindrome;
}


std::pair<int, std::string> makePalindrome(const std::string& str) {
  
  int s = (int)str.size();
  vvb indices_matrix(s, vb(s));
  
  vvi dp(s, vi(s, 0));
  // init 
  for(int i = 0; i < s; ++i) {
    dp[i][i] = 1;
    indices_matrix[i][i].set(i);
  }
  
  for(int l = 2; l <= s; ++l) {
    for(int i = 0; i < s - l + 1; ++i) {
      int j = i + l - 1;
      if(str[i] == str[j]) {
        dp[i][j] = 2 + dp[i + 1][j - 1];
        auto indices = indices_matrix[i + 1][j - 1];
        indices.set(i);
        indices.set(j);
        indices_matrix[i][j] = indices;
      } else {
        if (dp[i + 1][j] > dp[i][j - 1]) {
          dp[i][j] = dp[i + 1][j];
          indices_matrix[i][j] = indices_matrix[i + 1][j];
        } else {
          dp[i][j] = dp[i][j - 1];
          indices_matrix[i][j] = indices_matrix[i][j - 1];
        }
      }
    }
  }

  auto in_lps_bitset = indices_matrix[0][s - 1];
  std::string min_palindrome = build_min_palindrome(str, in_lps_bitset);

  return {s - dp[0][s - 1], min_palindrome};
}


namespace algorithms::onlinejudge::strings::make_palindrome
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

        std::string str;
        while(std::cin >> str) {
          std::pair<int, std::string> res = makePalindrome(str);
          printf("%d %s\n", res.first, res.second.c_str());
        }
    }
}