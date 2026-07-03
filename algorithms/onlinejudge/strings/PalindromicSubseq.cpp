/*
───────────────────────────────────────────────────────────────
🧳 UVa 11404 Palindromic Subsequence, https://onlinejudge.org/external/114/11404.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



struct PalindromicSubseq {
  int length;
  std::string subseq;
  bool operator<(const PalindromicSubseq& other) const {
    if(length != other.length) 
      return length < other.length;
    return subseq > other.subseq; // For lexicographically smallest, we reverse the comparison
  }
};


PalindromicSubseq longestPalindromicSubsequence(const std::string& str) {
  int s = (int)str.size();
  std::vector<std::vector<PalindromicSubseq>> dp(s, std::vector<PalindromicSubseq>(s));

  for(int i = 0; i < s; ++i) {
    dp[i][i] = {1, std::string(1, str[i])};
  }

  for(int l = 2; l <= s; ++l) {
    for(int i = 0; i < s - l + 1; ++i) {
      int j = i + l - 1;
      if(str[i] == str[j]) {
        dp[i][j].length = 2 + dp[i + 1][j - 1].length;
        dp[i][j].subseq = str[i] + dp[i + 1][j - 1].subseq + str[j];
      } else {
        if(dp[i + 1][j] < dp[i][j - 1]) {
          dp[i][j] = dp[i][j - 1];
        } else {
          dp[i][j] = dp[i + 1][j];
        }
      }
    }
  }

  return dp[0][s - 1];
}


namespace algorithms::onlinejudge::strings::palindromic_subseq
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
        while(std::getline(std::cin, str)) {
          std::cout << longestPalindromicSubsequence(str).subseq << std::endl;
        }
      }
    }