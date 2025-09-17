/*
───────────────────────────────────────────────────────────────
🧳 UVa 11827 Maximum GCD, https://onlinejudge.org/external/118/11827.pdf, GCD of many numbers, small input, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>

namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;


using ull = unsigned long long;
using v_ull = std::vector<ull>;
auto ___gcd = arithmetics::__gcd<ull>;



namespace algorithms::onlinejudge::maths::max_GCD
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
        scanf("%d\n", &t_cases);
        while(t_cases--) {
          ull n;
          std::string s;
          std::getline(std::cin, s);
          std::stringstream ss(s);
          v_ull nums;
          while(ss >> n) 
            nums.push_back(n);

          ull max_gcd = 0;
          for(size_t i = 0; i < nums.size(); ++i)
            for(size_t j = i + 1; j < nums.size(); ++j)
              max_gcd = std::max(max_gcd, ___gcd(nums[i], nums[j]));
          printf("%llu\n", max_gcd);   
        }
    }
}