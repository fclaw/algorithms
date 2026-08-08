/*
───────────────────────────────────────────────────────────────
🧳 UVa 1052 Bit Compressor, https://onlinejudge.org/external/10/1052.pdf, rt: s
───────────────────────────────────────────────────────────────
Verdict: Accepted | Runtime: 0.020s (Pure Backtracking with Structural Pruning)

   Algorithmic Summary & Special Cases Analysis:

   1. Why Pure Backtracking Runs in ~0.020s (Without Memoization):
      While unconstrained string partitions take O(2^39) worst-case, two tight
      structural constraints collapse the search tree to < 50 active branches:
        a) Zero-Branching at '0': When C[pos] == '0', branching factor is 1.
        b) The Maximal Rule Skip: Decoding any 1s token consumes the following '0',
           advancing 'pos' by (len + 1) and skipping entire recursion levels.
        c) Numeric Target Pruning: Any branch exceeding L or N is cut off 
           within 2-3 stack frames.

   2. Special Case 1: Non-Shortening Literals (n = 1 and n = 2)
      - n = 1: Original "1" (len 1) -> Binary "1" (len 1). 1 < 1 is FALSE.
               Never compressed. Stays as literal '1'.
      - n = 2: Original "11" (len 2) -> Binary "10" (len 2). 2 < 2 is FALSE.
               Never compressed. Stays as literal "11".

   3. Special Case 2: Shortening Binary Tokens (n >= 3)
      - Binary value n >= 3 where len(binary(n)) < n.

   4. Exhaustive Transition Breakdown:

      - Transition 0 (Literal '0'):
        Consumes '0' at C[pos], adds 1 to length, 0 to ones.

      - Transition 1A (Literal '1', n = 1):
        - Middle: "10" -> consumes 2 chars in C, adds 2 to length, 1 to ones.
        - End:    "1"  -> consumes 1 char in C,  adds 1 to length, 1 to ones.

      - Transition 1B (Literal "11", n = 2):
        - Middle: "110" -> consumes 3 chars in C, adds 3 to length, 2 to ones.
        - End:    "11"  -> consumes 2 chars in C, adds 2 to length, 2 to ones.

      - Transition 2 (Binary Token n >= 3):
        Loops len from 2 to min(20, |C| - pos):
        If binary_val(n) > len:
          - Middle: C[pos ... pos+len-1] followed by '0' -> 
                    consumes len+1 chars, adds n+1 to length, n to ones.
          - End:    C[pos ... pos+len-1] at end of C -> 
                    consumes len chars, adds n to length, n to ones.
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;

const int MAX_COMPRESSED = 40;

enum RESULT { YES, NO, AMBIGUOUS };

std::string result_to_str(RESULT res) {
  if(res == YES) {
    return "YES";
  } else if(res == NO) {
    return "NO";
  } else {
    return "NOT UNIQUE";
  }
}



int backtrack(const std::string& compressed_data, int pos, ll curr_length, ll curr_ones, int origin_length, ll ones_in_origin) {

   int S = (int)compressed_data.size();
   // 1. Correct Base Case: Reached the end of compressed_data
    if (pos == S) {
      if(curr_length == origin_length && 
         curr_ones == ones_in_origin) {
        return 1;  
      } else {
        return 0;
      }
    }

    // 2. Pruning invalid branches
    if (curr_length > origin_length || 
        curr_ones > ones_in_origin) {
      return 0;
    }


  int ways = 0;
  if(compressed_data[pos] == '0') {
    ways += backtrack(compressed_data, pos + 1, curr_length + 1, curr_ones, origin_length, ones_in_origin); 
  } else if (compressed_data[pos] == '1') {

     // 1. Single literal '1' (n = 1) in the middle: "10"
    if (pos + 1 < S && compressed_data[pos + 1] == '0') {
        ways += backtrack(compressed_data, pos + 2, curr_length + 2, curr_ones + 1, origin_length, ones_in_origin);
    } 
    // 2. Single literal '1' (n = 1) at the very end of C
    else if (pos + 1 == S) {
        ways += backtrack(compressed_data, pos + 1, curr_length + 1, curr_ones + 1, origin_length, ones_in_origin);
    }

    // 3. Two literal '1's (n = 2) in the middle: "110"
    if (pos + 2 < S && compressed_data[pos + 1] == '1' && compressed_data[pos + 2] == '0') {
        ways += backtrack(compressed_data, pos + 3, curr_length + 3, curr_ones + 2, origin_length, ones_in_origin);
    } 
    // 4. Two literal '1's (n = 2) at the very end of C: "11"
    else if (pos + 2 == S && compressed_data[pos + 1] == '1') {
        ways += backtrack(compressed_data, pos + 2, curr_length + 2, curr_ones + 2, origin_length, ones_in_origin);
    }

    for(int len = 2; pos + len <= S; ++len) {
      auto substr = compressed_data.substr(pos, len);
      std::bitset<MAX_COMPRESSED> bits(substr);
      ll onces = bits.to_ulong();
      ll new_curr_ones = curr_ones + onces;
      ll new_curr_length = curr_length + onces;
      if(onces > len) { // whenever it shortens ...
        if(pos + len < S && compressed_data[pos + len] == '0') {
          ways += backtrack(compressed_data, pos + len + 1, new_curr_length + 1, new_curr_ones, origin_length, ones_in_origin);
        } else if (pos + len == S) {
          ways += backtrack(compressed_data, pos + len, new_curr_length, new_curr_ones, origin_length, ones_in_origin);
        }
      }
    }
  }

  return ways;
}



RESULT can_restored(int origin_length, int ones_in_origin, const std::string& compressed_data) {
 
  int ways = backtrack(compressed_data, 0, 0, 0, origin_length, ones_in_origin);
  if(ways == 1) {
    return YES;
  } else if(ways == 0) {
    return NO;
  } else {
    return AMBIGUOUS;
  }
}


namespace algorithms::onlinejudge::advanced_topics::bit_compressor
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
        ll origin_length, ones_in_origin;
        while(std::cin >> 
                origin_length >>
                ones_in_origin && 
              (origin_length || 
              ones_in_origin)) {
          std::string compressed_data;
          std::cin >> compressed_data;
          printf("Case #%d: %s\n", t_case++, result_to_str(can_restored(origin_length, ones_in_origin, compressed_data)).c_str());
        }

    }
}