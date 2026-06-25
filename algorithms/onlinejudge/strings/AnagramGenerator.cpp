/*
───────────────────────────────────────────────────────────────
🧳 UVa 195 Anagram, https://onlinejudge.org/external/1/195.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>
#include <cctype>





namespace algorithms::onlinejudge::strings::anagram_generator
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
          std::string word;
          std::cin >> word;

          auto cmp = [](char lhs, char rhs) {
            if(std::tolower(lhs) == std::tolower(rhs)) {
              return lhs < rhs;
            }
            return std::tolower(lhs) < std::tolower(rhs);
          };
          std::sort(word.begin(), word.end(), cmp);
          do {
            std::cout << word << std::endl;
          } while(std::next_permutation(word.begin(), word.end()));
        }
    }
}