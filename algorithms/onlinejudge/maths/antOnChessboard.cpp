/*
───────────────────────────────────────────────────────────────
🧳 UVa 10161 Ant on a Chessboard, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;
using ld = long double;


namespace algorithms::onlinejudge::maths::ant_on_chessboard
{
    /** https://onlinejudge.org/external/101/10161.pdf */
    ll time;
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
        
        while(scanf("%lld", &time) == 1 && time > 0) {
          ld nd = std::sqrtl(time);

          ld dn;
          ld n_frac = std::modf(nd, &dn);

          if(time == 2) {
            printf("1 2\n");
          } else if(n_frac == 0) {
            ll n = (ll)dn;
            if(((ll)n % 2)) {
              printf("%lld %lld\n", (ll)1, (ll)n);
            } else printf("%lld %lld\n", (ll)n, (ll)1);
          } else {

            ll n = (ll)dn + 1;
            ll shift = (n * n) % time;
            if((n % 2)) {
              // start position (1, n)
              if(shift < n) {
                printf("%lld %lld\n", shift + 1, n);
              } else {
                printf("%lld %lld\n", n, n - (shift % n) - 1);
              }
            } else {
              // start position (n, 1)
              if(shift < n) {
                printf("%lld %lld\n", n, shift + 1);
              } else {
                printf("%lld %lld\n", n - (shift % n) - 1, n);
              }
            }
          }
        }
    }
}