/*
───────────────────────────────────────────────────────────────
🧳 UVa 12916 Perfect Cyclic String, https://onlinejudge.org/external/129/12916.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;
using vll = std::vector<ll>;
using vvll = std::vector<vll>;

const int MAX_L = 200000;


// Finds all factors of n in O(sqrt(n)) time
vll get_factors(ll n) {
  vll factors;

  // We only need to iterate up to the square root of n
  for(ll f = 1; f * f <= n; ++f) {
    if (n % f == 0) {
      factors.push_back(f); // i is a factor
        
      // To prevent adding the same factor twice for perfect squares (e.g., 6*6 = 36)
      if (f * f != n) {
        factors.push_back(n / f); // n / i is the paired factor
      }
    }
  }    
  return factors;
}



vvll factors(MAX_L + 1);

void precompute_factors() {
  
  for(int n = 1; n <= MAX_L; ++n) {
    vll fs = get_factors(n);
    std::sort(fs.begin(), fs.end(), std::greater<ll>());
    factors[n] = fs;
  }
}


int find_min_period(const std::string& str) {

  ll S = (ll)str.size();
  vll periods = factors[S];

  int min_period = S;
  for(ll period : periods) {
    int start = 0;
    bool is_period = true;
    while(start + period < S) {
      for(int i = start; i < start + (int)period; ++i) {
        int next = i + period;
        if(str[i] != str[next]) {
          is_period = false;
          break;
        }
      }
      if(!is_period) {
        break;
      }
      start += period;
    }
    if(is_period) {
      min_period = std::min(min_period, (int)period);
    }
  }

  return min_period;
}


namespace algorithms::onlinejudge::strings::perfect_cyclic_string
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

        precompute_factors();
        int t_cases;
        std::cin >> t_cases;
        while(t_cases--) {
          std::string str;
          std::cin >> str;
          std::cout << find_min_period(str) << std::endl;
        }
    }
}