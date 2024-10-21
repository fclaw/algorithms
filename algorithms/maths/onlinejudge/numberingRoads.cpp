#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>


namespace algorithms::maths::onlinejudge::numbering_roads
{
    // https://onlinejudge.org/external/117/11723.pdf
    const int max_suffix = 26;
    int minSuffixes(int roads, int nums)
    {
        if(roads <= nums) return 0;
        int r = !(bool)((roads - nums) % nums) ? (roads - nums) / nums : (roads - nums) / nums + 1;
        if(r <= max_suffix ) return r;
        else return -1;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int roads, nums, c = 0;
        while(std::cin >> roads >> nums)
        {
            if(roads == 0 && nums == 0) break;
            int s = minSuffixes(roads, nums);
            std::string ans = s != -1 ? std::to_string(s) : "impossible";
            printf("Case %d: %s\n", ++c, ans.c_str());
        }
    }
}