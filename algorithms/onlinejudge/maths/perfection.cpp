/*
───────────────────────────────────────────────────────────────
🧳 UVa 382 Perfection, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;

enum Status { DEFICIENT, PERFECT, ABUNDANT};


Status check_factors_sum(int n) {
  if(n == 1) return DEFICIENT;
  int factors_sum = 1;
  for(int i = 2; i * i <= n; i++) {
    if(n % i == 0) {
      factors_sum += i;
      if(i != n / i) {
        factors_sum += n / i;
      }
    }
  }
  if(factors_sum > n) {
    return ABUNDANT;
  } else if(factors_sum < n) {
    return DEFICIENT;
  } else {
    return PERFECT;
  }
}

namespace algorithms::onlinejudge::maths::perfection
{
    /** https://onlinejudge.org/external/3/382.pdf */
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
        
        vi nums;
        int num;
        while(while_read(num) && num) 
          nums.push_back(num);
        
        printf("PERFECTION OUTPUT\n");  
        for(int n : nums) {
          Status status = check_factors_sum(n);
          std::string status_s;
          if(status == DEFICIENT) status_s = "DEFICIENT";
          else if(status == PERFECT) status_s = "PERFECT";
          else status_s = "ABUNDANT";
          printf("%5d  %s\n", n, status_s.c_str());
        }
        printf("END OF OUTPUT\n");
    }
}