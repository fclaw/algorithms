/*
───────────────────────────────────────────────────────────────
🧳 UVa 10722 Super Lucky Numbers, https://onlinejudge.org/external/107/10722.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "../maths/utility/fast_bigint.cpp"



namespace bi = algorithms::onlinejudge::maths::utility::fast_bigint;


bi::BigInt cache[129][2][101][2];


bool is_unlucky(bool is_one, int curr_digit) {
  return (is_one && curr_digit == 3);
}

bi::BigInt count_super_lucky_numbers(bool is_one, bool is_start, int base, int digits_left) {
 
  if(digits_left == 0) {
    return bi::BigInt(1);
  }    

  if(cache[base][is_one][digits_left][is_start] != bi::BigInt(-1)) {
    return cache[base][is_one][digits_left][is_start];
  }

  bi::BigInt count(0);
  for(int digit = 0; digit < base; ++digit) {
    if(is_start && digit == 0) continue;

    if(is_unlucky(is_one, digit)) {
      continue;
    }

    count = count + count_super_lucky_numbers(digit == 1, false, base, digits_left - 1);
  }

  return (cache[base][is_one][digits_left][is_start] = count);

}



namespace algorithms::onlinejudge::advanced_topics::super_lucky_number
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

        for(int i = 0; i < 129; ++i) {
          for(int j = 0; j < 2; ++j) {
            for(int k = 0; k < 101; ++k) {
              for(int l = 0; l < 2; ++l) {
                cache[i][j][k][l] = bi::BigInt(-1);
              }
            }
          }
        }

        int base, digits;
        while(stdin_read(base, digits) && 
              (base && digits)) {
          std::cout << count_super_lucky_numbers(false, true, base, digits) << "\n";  
        }
    }
}