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



namespace algorithms::onlinejudge::dp::hashing
{
    /** https://onlinejudge.org/external/109/10912.pdf */
    int length, sum, t_case = 1;
    int memo[27][27][355];
    const int MAX_SUM = 351;
    int counter(const vi& alphabet, int c_c, int c_l, int c_s)
    {
        int remaining = length - c_l;
        if (remaining > 26 - c_c) return 0;

        int min_sum = (2 * (c_c + 1) + remaining - 1) * remaining / 2;
        int max_sum = (2 * 26 - remaining + 1) * remaining / 2;
        if (c_s + min_sum > sum || c_s + max_sum < sum) return 0;

        if(c_l > length || c_s > sum) return 0;

        if(c_l == length && c_s == sum) return 1;
        
        int& cnt = memo[c_c][c_l][c_s];
        if(~cnt) return cnt; 

        cnt = 0;
        for(int c = c_c + 1; c <= 26; ++c)
          cnt += counter(alphabet, c, c_l + 1, c_s + c);
        return cnt;
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
        
        vi alphabet(26);
        std::iota(alphabet.begin(), alphabet.end(), 1);
        while(while_read(length, sum) && length && sum)
        {
            std::memset(memo, -1, sizeof memo);
            printf("Case %d: %d\n", t_case++, sum > MAX_SUM ? 0 : counter(alphabet, 0, 0, 0));
        }  
    }
}