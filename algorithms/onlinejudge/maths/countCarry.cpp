/*
───────────────────────────────────────────────────────────────
🧳 UVa 10035 Primary Arithmetic, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int MAX_PAD = 12;


std::vector<int> num_to_digits(long long number, int fixed_length) {
    // 1. Convert the number to a string.
    std::string s = std::to_string(number);

    // 2. Calculate how many leading zeros are needed for padding.
    //    Use std::max to handle cases where the number is already too long.
    int num_zeros = std::max(0, fixed_length - (int)s.length());

    // 3. Create the final vector.
    std::vector<int> digits;
    digits.reserve(fixed_length); // Pre-allocate memory for efficiency

    // 4. Add the leading zeros.
    for (int i = 0; i < num_zeros; ++i) {
        digits.push_back(0);
    }

    // 5. Add the actual digits from the string.
    for (char c : s) {
        digits.push_back(c - '0'); // Convert char '1' to int 1, etc.
    }

    return digits;
}

namespace algorithms::onlinejudge::maths::count_carry
{
    /** https://onlinejudge.org/external/100/10035.pdf */
    long long one, two;
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
        
        while(while_read(one, two)) {
          if(!one && !two) break;
          auto one_xs = num_to_digits(one, MAX_PAD);
          auto two_xs = num_to_digits(two, MAX_PAD);
          bool is_carry = false;
          int carry_count = 0;
          for(int i = MAX_PAD - 1; i >= 0; --i) {
            int sum = one_xs[i] + two_xs[i] + (is_carry ? 1 : 0);
            if(sum >= 10) {
              carry_count++;
              is_carry = true;
            } else is_carry = false;
          }
          if(carry_count == 0) printf("No carry operation.\n");
          else if(carry_count == 1) printf("1 carry operation.\n");
          else printf("%d carry operations.\n", carry_count);
        }
    }
}