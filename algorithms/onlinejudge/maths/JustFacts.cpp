/*
───────────────────────────────────────────────────────────────
🧳 UVa 11466 Largest Prime Divisor, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>



namespace bi = algorithms::onlinejudge::maths::utility::big_integer;



size_t find_last_none_zero(const std::string& s) {
  // Loop from the last index (s.length() - 1) down to 0.
 for(int i = s.length() - 1; i >= 0; --i) {
   if(s[i] != '0') {
     // Found it. Return the index.
     return i;
    }
  }
  // If the loop completes, the character was not found.
  return  std::string::npos; // Using -1 as a sentinel value, similar to string::npos.
}


namespace algorithms::onlinejudge::maths::just_facts
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

        int num;
        while(scanf("%d", &num) == 1) {
          bi::bigint fac(num);
          std::string fac_s  = fac._big_fact(fac).getRawRep();
          size_t pos = find_last_none_zero(fac_s);
          printf("%5d -> %c\n", num, pos != std::string::npos ? fac_s[pos] : fac_s.back());
        }
    }
}