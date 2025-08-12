/*
───────────────────────────────────────────────────────────────
🧳 UVa 834 Continued Fractions, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;


vi do_fraction(int n, int m) {
  vi ans;
  while (m != 0) {
    int quotient = n / m;
    int remainder = n % m;
    ans.push_back(quotient);
    n = m;
    m = remainder;
  }
  return ans;
}

namespace algorithms::onlinejudge::maths::continued_fractions
{
    /** https://onlinejudge.org/external/8/834.pdf */
    int n, m;
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
        
        while(while_read(n, m)) {
          vi cont_fractions = do_fraction(n, m);
          if(cont_fractions.size() == 1) printf("[%d]\n", cont_fractions.front());
          else {
            std::string cont_fractions_s;
            cont_fractions_s += "[" + std::to_string(cont_fractions.front()) + ";";
            for (int i = 1; i < (int)cont_fractions.size(); i++) {
              cont_fractions_s += (i > 1 ? ","  : "") + std::to_string(cont_fractions[i]);
            }
            cont_fractions_s += "]\n";
            printf("%s", cont_fractions_s.c_str());
          }
        }
    }
}