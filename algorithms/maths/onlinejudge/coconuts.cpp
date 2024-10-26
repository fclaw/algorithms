#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>

namespace algorithms::maths::onlinejudge::coconuts
{

#define loop(x, s, n) for(int x = s; x < n; x++)

    /** https://onlinejudge.org/external/6/616.pdf, brute force up to √n, get pattern */
    bool count(int c, int castaways, int i) 
    {
        if(i == castaways) // morning division
          return c % castaways == 0;

        int pile = c / castaways;
        int monkey_share = c % castaways;
        if(monkey_share != 1) return false;
        return count(c - pile - monkey_share, castaways, i + 1);
    }
    std::optional<int> maxCastaways(int c)
    {
        int upper_bound = (int)std::sqrt(c);
        std::optional<int> castaways;
        loop(i, 1, upper_bound)
          if(count(c, i, 0))
            castaways = std::max(castaways, std::make_optional(i));
        return castaways;
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          std::freopen(file.value(), "r", stdin);
        
        int c;
        while(std::cin >> c)
        {
            if(c < 0) break;
            if(c == 3)
            {
                printf("3 coconuts, 2 people and 1 monkey\n");
                continue;
            }
            std::optional<int> castaways = maxCastaways(c);
            if(castaways.has_value())
              printf("%d coconuts, %d people and 1 monkey\n", c, castaways.value());
            else printf("%d coconuts, no solution\n", c);  
        }
    }
}