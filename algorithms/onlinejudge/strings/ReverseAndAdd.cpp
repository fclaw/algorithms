/*
───────────────────────────────────────────────────────────────
🧳 UVa 10018 Reverse and Add, https://onlinejudge.org/external/100/10018.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



bool is_palindrome(const std::string& str) {
  int l = 0, r = str.size() - 1;
  while(l < r) {
    if(str[l] != str[r]) return false;
    ++l; --r;
  }
  return true;
}


namespace algorithms::onlinejudge::strings::reverse_and_add
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
          std::string s_num;
          std::cin >> s_num;
          int iterations = 0;
          do {
            std::string rev_num = s_num;
            std::reverse(rev_num.begin(), rev_num.end());
            long long num = std::stoll(s_num) + std::stoll(rev_num);
            s_num = std::to_string(num);
            ++iterations;
          } while(!is_palindrome(s_num));
          std::cout << iterations << " " << s_num << std::endl;
        }
    }
}