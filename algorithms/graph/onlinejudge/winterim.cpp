#include <vector>
#include <cassert>
#include <optional>
#include <iostream>
#include <unordered_map>

namespace algorithms::graph::onlinejudge::winterim
{

typedef std::vector<int> vi;


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
     * an implicit dag (tree) of partial solutions
     * */
    void backtrack(const vi& camps, int p, int nights, int local_max, int& ans) 
    {
        int S = camps.size();
        if(p < S && nights < 0)
          return;

        if(p == S && nights < 0)
        {
            ans = std::min(ans, local_max);
            return;
        }

        int acc = 0;
        for(int i = p; i < S; i++)
        {
            acc += camps[i];
            backtrack(camps, i + 1, nights - 1, std::max(local_max, acc), ans);
        }
    }

    int deviseCampingStrategy(const vi& camps, int nights) 
    {
        int ans = INT32_MAX;
        backtrack(camps, 0, nights, 0, ans);
        return ans;
    }
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