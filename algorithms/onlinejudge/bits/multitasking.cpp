#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <bitset>
#include <algorithm>

namespace algorithms::onlinejudge::bits::multitasking
{
    
    /** https://onlinejudge.org/external/119/11926.pdf, use 1M bitset to check if a slot is free */
    const size_t N = 1e+06;
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int m, n;
        while(true)
        {
            std::cin >> m >> n;
            if(m == 0 && n == 0) break;
            std::bitset<N> calendar;
            bool isConflict = false;

            int s, e, r;
            while(m--)
            {
                std::cin >> s >> e;
                for(int i = s; i < e; i++)
                {
                    if(calendar.test(i))
                    { isConflict = true; break; }
                    calendar.set(i, true);
                }
            }

            while(n--)
            {
                std::cin >> s >> e >> r; 
                int length = e - s;
                while(s < N && !isConflict)
                {
                    for(int i = s; i < std::min(e, (int)N); i++)
                    {
                        if(calendar.test(i))
                        { isConflict = true; break; }
                        calendar.set(i, true);
                    }
                    s += r;
                    e = s + length;
                }
            }

            std::cout << (isConflict ? "CONFLICT" : "NO CONFLICT") << std::endl;
        }
    }
}