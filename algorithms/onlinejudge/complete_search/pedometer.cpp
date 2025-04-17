#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>
#include <cmath>
#include <unordered_set>






typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::pedometer
{
    /** https://onlinejudge.org/external/112/11205.pdf, try all 215 bitmask  */
    const size_t MAX = 15;
    bool validate(int off, const vi& digits)
    {
        std::unordered_set<int> digits_with_off;
        for(int d : digits)
        {
            int off_d = (d & ~off);
            if(digits_with_off.count(off_d))
              return false;
            digits_with_off.insert(off_d);
        }
        return true;  
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int leds, N, d;
            std::cin >> leds >> N;
            vi digits(N);
            for(int i = 0; i < N; i++)
            {
                std::bitset<MAX> tmp;   
                for(int j = leds - 1; j >= 0; j--)
                { std::cin >> d; if(d) tmp.set(j); }
                digits[i] = (int)tmp.to_ulong();
            }

            int min_leds_off = INT32_MAX;
            for(int off = 0; off < (1 << leds); off++)
              if(validate(off, digits))
              min_leds_off = std::min(min_leds_off, leds - __builtin_popcount(off));
            std::cout << min_leds_off << std::endl;  
        }
    }
}