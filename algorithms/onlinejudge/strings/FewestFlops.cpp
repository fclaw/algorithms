/*
───────────────────────────────────────────────────────────────
🧳 UVa 11552 Fewest Flops, https://onlinejudge.org/external/115/11552.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;



vvi get_chunks(const std::string& str, int k) {
  vvi chunks;
    
  // The number of blocks is exactly length / k
  int num_blocks = str.length() / k;
    
  for (int i = 0; i < num_blocks; ++i) {
    // Use a boolean array (or set) to find unique characters in this specific block
    std::vector<bool> present(26, false);
        
    for (int j = 0; j < k; ++j) {
      char c = str[i * k + j];
      present[c - 'a'] = true;
    }
        
    // Compile the unique characters into a list for this block
    vi current_chunk;
    for (int c = 0; c < 26; ++c) {
      if (present[c]) {
        current_chunk.push_back(c);
      }
    }
        
    chunks.push_back(current_chunk);
  }
    
  return chunks;
}


int get_min_chunks(const vvi& chunks) {

  vvi dp(chunks.size(), vi(26, INT_MAX));

  // init
  vi first_chunk = chunks[0];
  int s0 = first_chunk.size();
    
  for (int r = 0; r < s0; ++r) {
    for (int l = 0; l < s0; ++l) {
      // Rule: First and Last cannot be the same if > 1 unique char
      if (s0 > 1 && r == l) continue; 

      int right_c = first_chunk[r];
      dp[0][right_c] = s0; 
    }
  }
  
  for(int i = 1; i < (int)chunks.size(); ++i) {
    for(int c = 0; c < 26; ++c) {
      if(dp[i - 1][c] == INT_MAX) continue;
      vi curr_chunk = chunks[i];
      int curr_s = (int)curr_chunk.size();
      for(int r = 0; r < curr_s; ++r) {
        for(int l = 0; l < curr_s; ++l) {
          if(r == l && curr_s > 1) continue;
          int left_c = curr_chunk[l];
          int right_c = curr_chunk[r];
          int cost = dp[i - 1][c] + curr_s;
          if(left_c == c) {
            cost--;
          } 
          dp[i][right_c] = std::min(dp[i][right_c], cost);
        }
      }
    }
  }


  int min_chunks = INT_MAX;
  for(int c = 0; c < 26; ++c) {
    min_chunks = std::min(min_chunks, dp[chunks.size() - 1][c]);
  }

  return min_chunks;
}


namespace algorithms::onlinejudge::strings::fewest_flops
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
          int k;
          std::string str;
          std::cin >> k >> str;
          vvi chunks = get_chunks(str, k);
          std::cout << get_min_chunks(chunks) << std::endl; 
        }
    }
}