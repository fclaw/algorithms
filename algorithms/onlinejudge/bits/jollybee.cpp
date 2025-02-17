#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <bitset>
#include <cmath>



namespace algorithms::onlinejudge::bits::jollybee
{
    
    /** https://onlinejudge.org/external/12/1241.pdf */
    const size_t K = 1024;
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int rounds, n, k;
            scanf("%d %d", &rounds, &n);
            k = 1 << rounds; // 2 ^ rounds
            std::bitset<K> participants;
            participants.set();
            int c;
            for(int i = 0; i < n; i++)
            { std::cin >> c; participants.set(--c, false); }
            
            int pushover = 0;
            while(k != 1)
            {
                std::bitset<K> tmp;
                tmp.set();
                int idx = 0;
                for(int j = 0; j < k; j += 2)
                {
                    bool first = participants.test(j);
                    bool second = participants.test(j + 1);
                    if(first && !second || !first && second)
                      pushover++;
                    if(!first && !second) 
                    { tmp.set(idx, false); }
                    idx++;
                }
                k /= 2;
                participants = tmp;
            }
            std::cout << pushover << std::endl;
        }

    }
}