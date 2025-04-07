#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>



typedef std::vector<char> vc;

namespace algorithms::onlinejudge::complete_search::memory_overflow
{
    /** https://onlinejudge.org/external/125/12583.pdf, 2 nested loops; be careful of overcounting  */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

         
        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            int N, M;
            std::cin >> N >> M;
            vc names(N);
            for(int i = 0; i < N; i++)
              std::cin >> names[i];

            int ans = 0;
            for(int i = 0; i < N; i++)
              for(int j = i - 1; j >= 0 && j >= i - M; j--)
                if(names[i] == names[j]) 
                { ans++; break; }
            printf("Case %d: %d\n", c++, ans);
        }  
    }
}