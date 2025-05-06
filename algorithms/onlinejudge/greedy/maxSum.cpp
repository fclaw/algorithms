#include "../debug.h"
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>






typedef long long ll;
typedef std::vector<int> vi;
template<typename F>
inline void loop(size_t n, F&& f)
{
    for (size_t i = 0; i < n; ++i)
      std::forward<F>(f)(i);
}


namespace algorithms::onlinejudge::greedy::max_sum
{
    /** https://onlinejudge.org/external/106/10656.pdf, In a sequence of non-negative integers, find a sub-sequence with the maximum sum. ​ */
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
        
        size_t N;
        while(std::cin >> N && N)
        {
            vi nums(N);
            loop(N, [&nums](size_t i) { std::cin >> nums[i]; });

            vi max_sum_vals;
            auto fill = 
              [nums, &max_sum_vals](size_t i) 
              {if(nums[i]) max_sum_vals.push_back(nums[i]);};
            loop(N, fill);
            if(max_sum_vals.empty()) 
              std::cout << 0 << std::endl;
            else 
            {
                std::string s;
                for(int v : max_sum_vals) s += std::to_string(v) + " ";
                s.pop_back();
                std::cout << s << std::endl;
            }
        }
    }
}