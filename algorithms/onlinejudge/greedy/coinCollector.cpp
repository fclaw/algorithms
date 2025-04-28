#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_set>




typedef std::vector<int> vi;

namespace algorithms::onlinejudge::greedy::coin_collector
{
    /**  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int N;
            std::cin >> N;
            vi coins(N);
            for(int i = 0; i < N; i++)
              std::cin >> coins[i];
                          
            int cnt = 0;
            for(auto curr_it = coins.rbegin(); curr_it != coins.rend(); ++curr_it)
            {
                int init = *curr_it;
                auto prev_it = curr_it;
                while(++prev_it != coins.rend())
                  if(init - *prev_it >= 0)
                    init -= *prev_it;
                dbg(*curr_it, init);    
                if(init) cnt++;
            }
            std::cout << cnt << std::endl;
        }  
    }
}