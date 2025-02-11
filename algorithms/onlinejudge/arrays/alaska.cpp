#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>

#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr);

typedef std::vector<int> vi;

namespace algorithms::onlinejudge::arrays::alaska
{
    // https://onlinejudge.org/external/118/11850.pdf
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        const int DEST = 1422;
        const int CHARGE = 200;
        int n;
        while(true)
        {
            std::cin >> n;
            if(n == 0) break;

            vi locations = vi(n + 1);
            int x;
            for(int i = 0; i < n; i++)
              std::cin >> x,
              locations[i] = x;
            locations[n] = DEST;  
            std::sort(locations.begin(), locations.end());

            bool canComplete = true;
            int tank = CHARGE;
            for(int j = 1; j < n + 1 && canComplete; j++)
            {
                int fuel_consumption = locations[j] - locations[j - 1];
                tank -= fuel_consumption;
                if(tank < 0) { canComplete = false; continue; }
                if(j != n) tank += std::abs(tank - CHARGE);
            }
            std::cout << (canComplete && (tank - (locations[n] - locations[n - 1]) >= 0) ? "POSSIBLE" : "IMPOSSIBLE") << std::endl;    
        }
    }
}