#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>





typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::bars
{
    /** https://onlinejudge.org/external/124/12455.pdf, bit manipulation, all subset (2 ^ n)  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int length, N;
            scanf("%d\n%d", &length, &N);
            vi bars(N);
            for(int i = 0; i < N; i++)
              std::cin >> bars[i];
           
            bool isOk = false;
            // s = 0, empty set is equal to 0 length
            for(int s = 0; s < (1 << N); s++)
            {
                int l = 0;
                for(int i = 0; i < N; i++)
                  if((s & (1 << i)))
                    l += bars[i]; 
                if(length == l)
                { isOk = true; break; }    
            }
            isOk ? printf("YES\n") : printf("NO\n");
        }
    }
}