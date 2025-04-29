#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>





typedef long long ll;
typedef std::vector<int> vi;


vi generateTriangularNumbers() 
{
    vi nums;
    for (int n = 1;; ++n) 
    {
        long long tri = 1LL * n * (n + 1) / 2;
        if (tri > INT32_MAX) break;
        nums.push_back((int)tri);
    }
    return nums;
}

namespace algorithms::onlinejudge::divide_conquer::num_sequence
{
    /** https://onlinejudge.org/external/107/10706.pdf, binary search + some mathematical insights, triangular numbers */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
       
        vi nums = generateTriangularNumbers();
        int tc, n;
        std::cin >> tc;
        while(tc--)
        {
            std::cin >> n;
            auto it = std::lower_bound(nums.begin(), nums.end(), n);
            int cnt = it - nums.begin() + 1;
            dbg(*(it - 1) + 1, n, *it, cnt);
        }  
    }
}