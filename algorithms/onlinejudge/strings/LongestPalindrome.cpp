/*
───────────────────────────────────────────────────────────────
🧳 UVa 11151 Longest Palindrome, https://onlinejudge.org/external/111/11151.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;



namespace algorithms::onlinejudge::strings::longest_palindrome
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
          int s = (int)str.length();

          if(s == 0) {
            std::cout << 0 << std::endl;
            continue;
          }

          vvi dp(s, vi(s, 0));
          // init 
          for(int i = 0; i < s; ++i) {
            dp[i][i] = 1;
          }
            
          for(int l = 2; l <= s; ++l) {
            for(int i = 0; i < s - l + 1; ++i) {
              int j = i + l - 1;
              if(str[i] == str[j]) {
                dp[i][j] = 2 + dp[i + 1][j - 1];
              } else {
                dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
              }
            }
          }

          std::cout << dp[0][s - 1] << std::endl;
        }
    }
}