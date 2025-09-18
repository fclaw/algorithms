/*
───────────────────────────────────────────────────────────────
🧳 UVa 10338 Mischievous Children, https://onlinejudge.org/external/103/10338.pdf, s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;

ll do_factorial(ll n) {
  ll fac = 1;
  for(ll i = 1; i <= n; ++i)
    fac *= i;
  return fac;  
}


namespace algorithms::onlinejudge::maths::mischievous_children
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

        int t_cases, t_case = 1;
        scanf("%d", &t_cases);
        while(t_cases--) {
          std::string s;
          std::unordered_map<char, int> freq;
          std::cin >> s;
          for(char c : s) freq[c]++;
          ll over_count = 1;
          for(auto& p : freq) 
            over_count *= do_factorial(p.second);
          ll unique_arr = do_factorial(s.size()) / over_count;
          printf("Data set %d: %lld\n", t_case++, unique_arr);  
        }
    }
}