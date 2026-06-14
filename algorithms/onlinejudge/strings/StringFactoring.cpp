/*
───────────────────────────────────────────────────────────────
🧳 UVa 11022 String Factoring, https://onlinejudge.org/external/110/11022.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;


bool is_perfect_repeat(const std::string& s, int start, int end, int L) {
  // We check if every character matches the character 'L' steps behind it
  for (int k = start + L; k <= end; ++k) {
    if (s[k] != s[k - L]) {
      return false;
    }
  }
  return true;
}


int get_max_factoring(const std::string& str, int i, int j, vvi& memo) {
  
  if(i >= j) {
    return 1;
  }

  if(~memo[i][j]) {
    return memo[i][j];
  }

  int compress_min = INT_MAX;
  int len = j - i + 1;

  // Try all possible prefix lengths 'L' that could repeat to form the string
  for(int L = 1; L <= len / 2; ++L) {
    if (len % L == 0) { // L must evenly divide the length
      if(is_perfect_repeat(str, i, j, L)) {
        // If it repeats, the weight of the whole string is just 
        // the optimal weight of that one repeating block!
        compress_min = std::min(compress_min, get_max_factoring(str, i, i + L - 1, memo));
      }
    }
  }


  int split_min = INT_MAX;
  for(int k = i; k < j; ++k) {
    int left_rec = get_max_factoring(str, i, k, memo);
    int right_rec = get_max_factoring(str, k + 1, j, memo);
    int local_split = left_rec + right_rec;
    split_min = std::min(split_min, local_split);
  }
  return memo[i][j] = std::min(compress_min, split_min);
}


namespace algorithms::onlinejudge::strings::string_factoring
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
        while(std::cin >> str && str != "*") {
          vvi memo(str.size(), vi(str.size(), -1));
          printf("%d\n", get_max_factoring(str, 0, str.size() - 1, memo)); 
        }
    }
}