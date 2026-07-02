/*
───────────────────────────────────────────────────────────────
🧳 UVa 11584 Partitioning by Palindromes, https://onlinejudge.org/external/115/11584.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;


int is_palindrome(const std::string& str, int l, int r, vvi& cache) {
  
    // 
    if(l == r) return 1;
    if(l + 1 == r) return str[l] == str[r];

     int &ans = cache[l][r];
     if(~ans) return ans;
     
     ans = 0;
     ans = str[l] == str[r] && is_palindrome(str, l + 1, r - 1, cache);
     return ans;
}

int count_palindromes(const std::string& str, int l, int r, vvi& check_cache, vvi& count_cache) {
     
    if(l >= r) {
      return 0;
    }

    if(~count_cache[l][r]) {
      return count_cache[l][r];
    }

    int ans = INT32_MAX;
    for(int k = l; k <= r; ++k) {
      if(is_palindrome(str, l, k, check_cache)) {
        ans = std::min(ans, 1 + count_palindromes(str, k + 1, r, check_cache, count_cache));
      }
    }

    return count_cache[l][r] = ans;
}



namespace algorithms::onlinejudge::strings::partitioning_by_palindromes
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
          std::string str;
          std::cin >> str;
          vvi check_cache(str.size() + 1, vi(str.size() + 1, -1));
          vvi count_cache(str.size() + 1, vi(str.size() + 1, -1));
          std::cout << count_palindromes(str, 0, str.size(), check_cache, count_cache) << std::endl;
        }
    }
}