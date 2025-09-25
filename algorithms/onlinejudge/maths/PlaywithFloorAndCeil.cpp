/*
───────────────────────────────────────────────────────────────
🧳 UVa 10673 Play with Floor and Ceil, uses Extended Euclidean,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


using ll = long long;

// Integer ceil division (from our previous discussions)
ll ceil_div(ll a, ll b) {
  if(a >= 0) return (a + b - 1) / b;
  return a / b;
}


namespace algorithms::onlinejudge::maths::play_with_floor_and_ceil
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
       scanf("%d", &t_cases);
       while(t_cases--) {
         ll x, k;
         scanf("%lld %lld", &x, &k);
         
         if(x < k) {
          printf("0 %lld\n", std::min(x, k));
          continue;
         }

         ll a = (ll)(x / k);
         ll b = ceil_div(x, k);
         ll c = x;
         arith::Diophantine<> sol = arith::diophantine_equation<>(a, b, c);
         ll low = std::ceil((-sol.x * sol.gcd) / b);
         ll up = std::floor((sol.y * sol.gcd) / a);
         
         ll p = 0, q = 0;
         for(ll s = low; s <= up; ++s) {
          ll curr_p = sol.x + (s * b) / sol.gcd;
          ll curr_q = sol.y - (s * a) / sol.gcd;
          if(curr_p >= 0 && curr_q >= 0) {
            p = curr_p;
            q = curr_q;
            break;
          }
         }
         printf("%lld %lld\n", p, q);
       }
    }
}