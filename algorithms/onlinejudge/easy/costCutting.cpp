#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>


namespace algorithms::onlinejudge::easy::cost_cutting
{
    // https://onlinejudge.org/external/117/11727.pdf
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc, k = 1;
        scanf("%d", &tc);
        while(tc--)
        {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            if((a <= b && b <= c) || 
                (c <= b && b <= a)) 
              printf("Case %d: %d\n", k++, b);
            else if((b <= a && a <= c) || 
                    (c <= a && a <= b)) 
              printf("Case %d: %d\n", k++, a);
            else printf("Case %d: %d\n", k++, c);           
        }
    }
}