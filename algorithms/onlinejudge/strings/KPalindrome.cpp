/*
───────────────────────────────────────────────────────────────
🧳 UVa 1239 Greatest K-Palindrome Substring, https://onlinejudge.org/external/12/1239.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




namespace algorithms::onlinejudge::strings::k_palindrome
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
        while(t_cases--) {
          int k;
          std::string str;
          std::cin >> str >> k;
          int s = (int)str.size();
          
          int max_len = 1; // Any single character is a valid palindrome

          for (int i = 0; i < s; ++i) {
                
            // --- CASE 1: ODD-LENGTH PALINDROMES (Center is S[i]) ---
            // Example: "aba" -> L = i, R = i
            int L = i, R = i;
            int mismatches = 0;
            while (L >= 0 && R < s) {
              if (str[L] != str[R]) {
                mismatches++;
              }
              if (mismatches > k) break; // Exceeded budget, stop expanding!
                    
              max_len = std::max(max_len, R - L + 1);
              L--; R++;
            }

            // --- CASE 2: EVEN-LENGTH PALINDROMES (Center is between S[i] and S[i+1]) ---
            // Example: "abba" -> L = i, R = i + 1
            L = i; R = i + 1;
            mismatches = 0;
            while (L >= 0 && R < s) {
              if (str[L] != str[R]) {
                mismatches++;
              }
              if (mismatches > k) break; // Exceeded budget, stop expanding!
                    
              max_len = std::max(max_len, R - L + 1);
              L--; R++;
            }
          }

          std::cout << max_len << std::endl;
        }
    }
}