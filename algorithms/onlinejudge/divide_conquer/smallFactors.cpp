#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <functional>




typedef long long ll;
typedef std::vector<ll> vll;


const ll MAX = (ll)INT32_MAX + 1;

vll generateUpToIntMax() 
{
    vll nums;
    std::set<ll> seen;
    std::priority_queue<ll, vll, std::greater<ll>> pq;

    pq.push(1);
    seen.insert(1);

    while (!pq.empty()) 
    {
        ll curr = pq.top(); pq.pop();
        nums.push_back(curr);

        if (curr * 2 <= MAX) 
        {
            ll next2 = curr * 2;
            if(seen.insert(next2).second)
              pq.push(next2);
        }

        if(curr * 3 <= MAX) 
        {
            ll next3 = curr * 3;
            if(seen.insert(next3).second)
              pq.push(next3);
        }
    }

    return nums;
}

namespace algorithms::onlinejudge::divide_conquer::small_factors
{
    /** https://onlinejudge.org/external/116/11621.pdf, generate numbers with factor 2 and/or 3, sort, upper bound */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int m;
        vll nums = generateUpToIntMax();
        while(std::cin >> m && m)
        {
            auto it = std::upper_bound(nums.begin(), nums.end(), m);
            std::cout << (*(it - 1) != m ? *it : m) << std::endl;
        }
    }
}