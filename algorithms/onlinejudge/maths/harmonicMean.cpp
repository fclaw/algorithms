/*
───────────────────────────────────────────────────────────────
🧳 UVa 12068 Harmonic Mean, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>




using ll = long long;
using vi = std::vector<int>;

namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;


namespace algorithms::onlinejudge::maths::harmonic_mean
{
    /** https://onlinejudge.org/external/120/12068.pdf */
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
         
        int t_cases, t_case = 1;
        scanf("%d", &t_cases);
        while(t_cases--) {
          int n;
          scanf("%d", &n);
          vi nums(n);
          for(int i = 0; i < n; ++i) 
            scanf("%d", &nums[i]);
          
          ll lcm = 1;
          for(int n : nums) 
            lcm = arithmetics::__lcm(lcm, n); 
          
          ll nom = n * lcm;  
          ll denom = 0;
          for(int n : nums) 
            denom += lcm / n;
          ll gcd = arithmetics::__gcd(std::max(denom, nom), std::min(denom, nom));
          printf("Case %d: %lld/%lld\n", t_case++, nom / gcd, denom / gcd);
        }
    }
}