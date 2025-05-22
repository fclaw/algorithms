#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>




typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
typedef std::vector<bool> vb;


vi generate_primes(int upper_limit) 
{
    vb is_prime(upper_limit + 1, true);
    vi primes;
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p <= upper_limit; ++p)
      if(is_prime[p]) {
        primes.push_back(p);
        int comp = p * p;
        for(; comp <= upper_limit; comp += p)
          is_prime[comp] = false;
      }
    return primes;
}

namespace algorithms::onlinejudge::dp::sum_of_primes
{
    /** https://onlinejudge.org/external/12/1213.pdf */
    int n, k;
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

        while(while_read(n, k) && n && k)
        { 
            vi primes = generate_primes(n);
            int s = primes.size();
            vvvi dp(s + 1, vvi(n + 1, vi(k + 1)));
            dp[0][0][0] = 1;
            // f(i, rem_n, rem_k) = 
            //  f(i + 1, rem_n, rem_k)              Skip current prime
            //  + f(i + 1, rem_n - p[i], rem_k - 1) Take current prime (if it fits)
            for(int i = 0; i < s; ++i)
              for(int rem_n = 0; rem_n <= n; ++rem_n)
                for(int rem_k = 0; rem_k <= k; ++rem_k) {
                  dp[i + 1][rem_n][rem_k] += dp[i][rem_n][rem_k];
                  if(rem_n + primes[i] <= n && rem_k + 1 <= k)
                    dp[i + 1][rem_n + primes[i]][rem_k + 1] += dp[i][rem_n][rem_k];
                }
            std::cout << dp[s][n][k] << std::endl;
        }
    }
}