#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <bitset>



namespace algorithms::onlinejudge::bits::splitting_numbers
{
    
    /** https://onlinejudge.org/external/119/11933.pdf, an exercise for bit manipulation */
    const size_t N = 32;
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        size_t n;
        while(true)
        {
            std::cin >> n;
            if(n == 0) break;
            std::bitset<N> number(n), odd(0), even(0);
            bool flag = true;
            for(int i = 0; i < N; i++)
            {
                if(flag && number.test(i)) { odd.set(i); flag = !flag; }
                else if(!flag && number.test(i)) { even.set(i); flag = !flag; }
            }

            std::cout << odd.to_ulong() << " " << even.to_ulong() << std::endl;
        }
    }
}