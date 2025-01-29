#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>

namespace algorithms::onlinejudge::dp
{
    bool canLuggageBeFairlyDivided(std::vector<int>& luggage, int target)
    {
        std::vector<bool> dp(target + 1);
        dp[0] = true;

        for(auto x : luggage)
          for(int i = target; i >= x; i--)
              dp[i] = dp[i] || dp[i - x];

        return dp[target];
    }

    void submit_10664()
    {
        int TC;
        scanf("%d", &TC);
        std::string s;
        std::stringstream ss;
        std::getline(std::cin,s);
        while(TC-- > 0)
        {
            std::vector<int> luggage;
            std::getline(std::cin,s);
            ss.clear();
            ss << s;
            int x;
            int sum = 0;
            while(ss >> x)
            {
               luggage.push_back(x);
               sum += x;
            }
            if((sum & 1) == 0) 
            {
                bool ans = canLuggageBeFairlyDivided(luggage, sum / 2);
                printf("%s\n", ans ? "YES" : "NO");
            } else printf("NO\n");
        }
    }
}