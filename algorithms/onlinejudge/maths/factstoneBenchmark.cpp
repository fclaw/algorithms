/*
───────────────────────────────────────────────────────────────
🧳 UVa 10916 Factstone Benchmark, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;

constexpr int INIT_YEAR = 1960;
constexpr int MAX_INT = 10000000;


namespace algorithms::onlinejudge::maths::factstone_benchmark
{
    /** https://onlinejudge.org/external/109/10916.pdf */
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
         
        int year;
        while(scanf("%d", &year) == 1 && year != 0) {
          // 1960 -> 4 bits, 2
          // 1970 -> 8 bits, 3
          // 1980 -> 16 bits, 4
          // 1990 -> 32 bits ..
          // 2000 -> 64 bits
          // 2010 -> 128 bits
          // 2020 -> 256 bits
          // 2030 -> 512 bits
          int diff = (year - INIT_YEAR) / 10;
          ll bits = 1LL << (diff + 2); // 2^diff 
          // Calculate the target value in "log space".
          // We need to find the largest N such that log2(N!) <= B.
          // This is equivalent to ln(N!) <= B * ln(2).
          // Using long double for maximum precision.
          long double target_log_sum = bits * std::log10l(2.0L);

          int max_int = 0;
          double curr_log_sum = 0;
          for(int n = 1; n <= MAX_INT; ++n) {
            curr_log_sum += std::log10(n);
            if(curr_log_sum > target_log_sum) {
              max_int = n - 1;
              goto done;
            }
          }
          done: printf("%d\n", max_int);
        } 
    }
}