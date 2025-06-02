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

typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;


namespace algorithms::onlinejudge::dp::divisibility
{
    /** https://onlinejudge.org/external/100/10036.pdf */
    int tc, n, k;
    bool check_divisibility(const vi& nums, int i, int rem, vvi& memo)
    {
        if(i == n) return (rem == 0);

        if(~memo[i][rem]) return memo[i][rem];

        int new_rem_plus = (rem + nums[i]) % k;
        if(new_rem_plus < 0) new_rem_plus += k;
        bool rem_plus = check_divisibility(nums, i + 1, new_rem_plus, memo);

        int new_rem_minus = (rem - nums[i]) % k;
        if(new_rem_minus < 0) new_rem_minus += k;
        bool rem_minus = check_divisibility(nums, i + 1, new_rem_minus, memo);

        bool res = rem_plus | rem_minus;
        memo[i][rem] = (int)res;
        return res;
    }
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
        
        while_read(tc);
        while(tc--)
        {
            while_read(n, k);
            vi nums(n);
            loop(n, [&nums](int i) { while_read(nums[i]); });
            vvb dp(n + 1, vb(k, false));
            dp[0][0] = true;
            for(int i = 0; i < n; ++i)
              for(int r = 0; r < k; ++r) {
                int plus = ((r + nums[i]) % k + k) % k;
                int minus = ((r - nums[i]) % k + k) % k;
                dp[i + 1][r] = dp[i][plus] | dp[i][minus];
              }

            dp[n][0] ? printf("Divisible\n") : printf("Not divisible\n");
        }  
    }
}