/*
───────────────────────────────────────────────────────────────
🧳 UVa 787 Maximum Sub-sequence Product, https://onlinejudge.org/external/7/787.pdf, rt: s
───────────────────────────────────────────────────────────────
*/


#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

#include "../maths/utility/fast_bigint.cpp"


namespace bigint = algorithms::onlinejudge::maths::utility::fast_bigint;

using vi = std::vector<int>;

constexpr int end = -999999;

bigint::SignedBigInt max_product_subarray(const vi& nums) {
  bigint::SignedBigInt global_max(nums[0]);
  bigint::SignedBigInt cur_max(nums[0]);
  bigint::SignedBigInt cur_min(nums[0]);

  for (size_t i = 1; i < nums.size(); ++i) {
    bigint::SignedBigInt x(nums[i]);

    // Multiplying by a negative number flips max into min and min into max!
    if (x < 0) {
      std::swap(cur_max, cur_min);
    }

    // At each step, either extend the previous product or start fresh at x:
    cur_max = std::max(x, cur_max * x);
    cur_min = std::min(x, cur_min * x);

    global_max = std::max(global_max, cur_max);
  }

  return global_max;
}


namespace algorithms::onlinejudge::complete_search::max_sub_seq_product
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
          vi nums;
          int number;
          std::stringstream ss(line);
          while(ss >> number && 
                number != end) {
            nums.push_back(number);
          }
                    
          std::cout << max_product_subarray(nums) << std::endl;
        }
    }
}