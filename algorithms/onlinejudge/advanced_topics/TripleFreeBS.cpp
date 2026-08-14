/*
───────────────────────────────────────────────────────────────
🧳 UVa 11127 Triple-Free Binary Strings, https://onlinejudge.org/external/111/11127.pdf, rt: s
───────────────────────────────────────────────────────────────
   Function: Suffix Triple-Pattern (AAA) Detection

   Algorithmic Summary & Design Principles:

   1. The Suffix-Only Invariant:
      In incremental backtracking, as we place a new bit at position 'len - 1', 
      the prefix of length 'len - 1' is ALREADY guaranteed to be triple-free 
      from previous recursive steps. 
      
      Therefore, any new forbidden AAA pattern created by placing the current bit 
      MUST include the current bit. That is, AAA MUST end at index 'len - 1' 
      (the suffix). We do NOT need to scan from the beginning of the string.

   2. Bitmask Alignment Trick (str >> (len - 3 * l)):
      For a candidate block size 'l', the total AAA pattern has length 3 * l.
      The pattern occupies bits (len - 3*l) ... (len - 1) in 'str'.
      
      By shifting 'str' right by (len - 3 * l), we move bit (len - 3*l) down to 
      bit 0. This places the 3*l tail bits at the lowest bit positions (0 ... 3*l - 1),
      allowing for simple mask extraction.

   3. In-Place Block Peeling (sub_str >>= l):
      Instead of using complex shift formulas for each block, we use in-place 
      right-shifts to peel off the 3 blocks of length 'l' from right to left:
        - s1: Rightmost block (A_3, bits 0 ... l-1)
        - s2: Middle block    (A_2, bits l ... 2l-1)
        - s3: Leftmost block  (A_1, bits 2l ... 3l-1)
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



bool has_triple_suffix(int str, int len) {
 // Maximum possible block size 'l' such that 3 * l <= len
 int max_block_len = len / 3;

 for(int l = 1; l <= max_block_len; ++l) {
        
    // 1. Shift right to align the 3*l suffix down to bit 0
    int sub_str = str >> (len - 3 * l);
        
    // 2. Create a bitmask of 'l' consecutive 1-bits
    int mask = (1 << l) - 1;

    // 3. Extract the 3 adjacent blocks of length 'l' from right to left
    int s1 = sub_str & mask; // Rightmost block (A_3)
    sub_str >>= l;           // Shift out s1
        
    int s2 = sub_str & mask; // Middle block (A_2)
    sub_str >>= l;           // Shift out s2
        
    int s3 = sub_str & mask; // Leftmost block (A_1)

    // 4. Equality Check: If A_1 == A_2 == A_3, AAA pattern is detected
    if (s1 == s2 && s2 == s3) {
      return true; // Forbidden AAA pattern found!
    }
  }

  return false; // String remains triple-free
}


void backtrack(int pos, const std::string& pattern, int mask, int& num_triple_free) {

  if(has_triple_suffix(mask, pos)) {
    return; // Prune immediately!
  }


  if(pos == (int)pattern.size()) {
    num_triple_free++;
    return;
  }


  int bit = (1 << pos);
  char c = pattern[pos];
  if(std::isdigit(c)) {
    int val = (int)(c - '0');
    if(val) mask |= bit;
    backtrack(pos + 1, pattern, mask, num_triple_free);
    return; 
  }

  backtrack(pos + 1, pattern, mask | bit, num_triple_free); // 1
  backtrack(pos + 1, pattern, mask, num_triple_free); // 0
}


int count_triple_free_strings(int N, const std::string& pattern) {
  int num_triple_free = 0;
  backtrack(0, pattern, 0, num_triple_free);
  return num_triple_free;
}


namespace algorithms::onlinejudge::advanced_topics::triple_free_bs
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

        int t_case = 1;
        std::string str;
        while(std::getline(std::cin, str)) {
          int N;
          std::string pattern;
          std::stringstream ss(str);
          ss >> N;
          if(N == 0) {
            break;
          }
          ss >> pattern;
          printf("Case %d: %d\n", t_case++, count_triple_free_strings(N, pattern));
        }

    }
}