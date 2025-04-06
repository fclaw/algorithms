#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>



typedef std::vector<int> vi;

namespace algorithms::onlinejudge::complete_search::vito_family
{
    /** https://onlinejudge.org/external/100/10041.pdf, try all possible location of Vito’s House  */
    int optimalStreet(const vi& streets)
    {
        int ans = INT32_MAX;
        for(int i = 1; i <= streets.back(); i++)
        {
            int local = 0;
            for(int j = 0; j < streets.size(); j++)
              local += std::abs(i - streets[j]);
            ans = std::min(ans, local);
        }
        return ans;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int N;
            scanf("%d", &N);
            vi streets(N);
            for(int i = 0; i < N; i++)
              scanf("%d", &streets[i]);
            std::sort(streets.begin(), streets.end());
            std::cout << optimalStreet(streets) << std::endl;
        }  
    }
}