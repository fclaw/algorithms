/*
───────────────────────────────────────────────────────────────
🧳 UVa 12805 Raiders of the Lost Sign, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 1000000;

enum Sign { PLUS, MINUS };

Sign combine(Sign lhs, Sign rhs) {
  if(lhs == MINUS && rhs == MINUS) return PLUS;
  if(lhs == MINUS || rhs == MINUS) return MINUS;
  return PLUS;
}

Sign detect_sign(ll term) {
  if(term == 2) return PLUS;
  else if(!((term + 1) % 4)) {
    return PLUS;
  } else return MINUS;
}


namespace algorithms::onlinejudge::maths::raiders_of_lost_sign
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        primes::sieve(MAX);

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

        ll term;
        int t_cases;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%lld", &term);
          Sign sign = PLUS;
          bool is_term_prime = primes::isPrime(term);
          if(is_term_prime) {
            sign = detect_sign(term);
          } else {
            vll factors = primes::primeFactors(term);
            for(ll fac : factors) {
              sign = combine(sign, detect_sign(fac));
            }
          }
          printf("%s\n", sign == PLUS ? "+" : "-");
        }
    }
}