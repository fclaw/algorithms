#include <vector>
#include <cassert>
#include <optional>
#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>

namespace algorithms::graph::onlinejudge::winterim
{


struct pair_hash 
{
    std::size_t operator () (const std::pair<int, int> &p) const 
    {
        auto first = std::hash<int>{}(p.first);
        auto second = std::hash<int>{}(p.second);
        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
       return first ^ (second + 0x9e3779b9 + (first << 6) + (first >> 2));
    }
};

// x - counter. s - start point, n - boundary 
#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<int> vi;
typedef std::pair<int, int> state;
typedef std::unordered_map<state, int, pair_hash> table; 

    /** https://onlinejudge.org/external/9/907.pdf. 
     * closely resemble  https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs
     * We have a list of all possible campsites that we can use along the way 
     * and we want to do this trip so that we only stop K nights to camp. 
     * We also know in advance the distance between consecutive campsites and 
     * we are only allowed to camp at a campsite. Our goal is to plan the trip 
     * so that we minimise the maximum amount of walking done in a single day. 
     * In other words, if our trip involves 2 nights (3 days of walking), 
     * and we walk 9, 10, 5 miles on each day respectively, 
     * the cost (maximum amount of walking done in one day) is 10.
     * Another schedule that involves walking 9, 6, 9 miles on each day has cost 9.
     * hints (Converting General Graph to DAG): state(pos, night left)
     * an implicit dag (tree) of partial solutions */
    int backtrack(const vi& camps, int p, int nights, table& memo)
    {
        int S = camps.size();
        if(p < S && nights < 0)
          return INT32_MAX;

        if(p == S && nights < 0)
            return 0;

        if(auto it = memo.find({p, nights}); 
           it != memo.end())
          return memo[{p, nights}];   

        int acc = 0;
        int ans = INT32_MAX;
        loop(i, p, S)
          acc += camps[i],
          ans = std::min(ans, std::max(acc, backtrack(camps, i + 1, nights - 1, memo)));
        return memo[{p, nights}] = ans;
    }

    int deviseCampingStrategy(const vi& camps, int nights)
    { table memo; return backtrack(camps, 0, nights, memo); }

    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int n, nights;
        while(std::cin >> n >> nights)
        {
            vi camps;
            int d;
            while(n-- >= 0)
              std::cin >> d,
              camps.push_back(d);
            printf("%d\n", deviseCampingStrategy(camps, nights));
        }
    }
}