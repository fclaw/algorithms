/*
───────────────────────────────────────────────────────────────
🧳 UVa 12527 Different Digits, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



bool has_repeated_digits(int n) {
  std::string num_s = std::to_string(n);
  std::unordered_set<char> digits;
  for(char digit : num_s) {
    if(digits.find(digit) != digits.end()) 
      return true;
    digits.insert(digit);
  }
  return false;
}


namespace algorithms::onlinejudge::maths::different_digits
{
    /** https://onlinejudge.org/external/125/12527.pdf */
    int left, right;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
       
        while(while_read(left, right)) {
          int count = 0;
          for(int num = left; num <= right; ++num) {
            if(!has_repeated_digits(num)) ++count;
          }
          printf("%d\n", count);
        }  
    }
}