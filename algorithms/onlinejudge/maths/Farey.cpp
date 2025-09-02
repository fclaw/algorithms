/*
───────────────────────────────────────────────────────────────
🧳 UVa 10408 Farey sequences, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



struct Fraction 
{
    int nominator;
    int denominator;
    bool operator < (const Fraction& other) const {
      return nominator * other.denominator < 
             other.nominator * denominator; 
    }
};

using v_fraction = std::vector<Fraction>;

int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}


namespace algorithms::onlinejudge::maths::Farey
{
    /** https://onlinejudge.org/external/104/10408.pdf */
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
        
        int n, k;
        while(scanf("%d %d", &n, &k) == 2) {
          v_fraction farey;
          for(int denom = 1; denom <= n; ++denom) {
            for(int nom = 1; nom < denom; ++nom) {
              if(gcd(nom, denom) == 1) {
                farey.push_back({nom, denom});
              }
            }
          }
          std::sort(farey.begin(), farey.end());
          k > (int)farey.size() ? printf("1/1\n") : printf("%d/%d\n", farey[k - 1].nominator, farey[k - 1].denominator);
        }  
    }
}