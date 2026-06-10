/*
───────────────────────────────────────────────────────────────
🧳 UVa 257 Palinwords, https://onlinejudge.org/external/2/257.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>





using vb = std::vector<bool>;
using vvb = std::vector<vb>;



bool is_palinwords(const std::string& s) {
  std::set<std::string> s_palindroms;
  int n = s.length();

  vvb dp = vvb(n, vb(n, false));
  
  for(int i = 0; i < n; ++i) {
    dp[i][i] = true;
  }

  for(int l = 2; l <= n; ++l) {
    for(int i = 0; i < n - l + 1; ++i) {
      int j = i + l - 1;
      if(s[i] == s[j] && (l == 2 || dp[i + 1][j - 1])) {
        dp[i][j] = true;
        if(l > 2) s_palindroms.insert(s.substr(i, l));
      }
    }
  }

  
  std::vector<std::string> v_palindroms(s_palindroms.begin(), s_palindroms.end());
  auto cmp = [](const std::string& a, const std::string& b) 
             { return a.length() > b.length(); };
  std::sort(v_palindroms.begin(), v_palindroms.end(), cmp);

  int cnt = 0;
  for(int i = 0; i < (int)v_palindroms.size(); ++i) {
    bool is_valid = true;
    auto curr_word = v_palindroms[i];
    for(int j = i + 1; j < (int)v_palindroms.size(); ++j) {
      if(curr_word.find(v_palindroms[j]) != std::string::npos) {
        is_valid = false;
        break;
      }
    }
    if(is_valid) {
      cnt++;
      if (cnt >= 2) return true; // Stop immediately once we win!
    }
  }

  return cnt >= 2;
}


namespace algorithms::onlinejudge::strings::palinwords
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

        std::string line;
        while(std::getline(std::cin, line)) {
          std::stringstream ss(line);
          std::string word;
          while(ss >> word) {
            if(is_palinwords(word)) {
              std::cout << word << std::endl;
            }
          }
        }
    }
}