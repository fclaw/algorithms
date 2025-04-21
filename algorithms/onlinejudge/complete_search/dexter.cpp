#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cmath>




typedef long long ll;


std::string intToModifiedBinary(int num, int p) 
{
    std::string binary_str;
    // Generate a binary representation with p bits
    for (int i = p - 1; i >= 0; --i) 
    {
        // Extract the bit at position i
        int bit = (num >> i) & 1;
        // Replace 0 with '2' and 1 with '1'
        binary_str += (bit == 0 ? '2' : '1');
    }
    return binary_str;
}

ll modifiedBinaryToInt(const std::string& binary_str) 
{
    ll integer = 0;
    // Convert the binary string (with 0s and 2s) to int
    for(char c : binary_str)
      integer = integer * 10 + (c - '0');  // Construct integer from string
    return integer;
}


namespace algorithms::onlinejudge::complete_search::dexter
{
    /** https://onlinejudge.org/external/124/12406.pdf, try all 2 ^ p possible bitmasks, change ‘0’s to ‘2’s  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            int p, q;
            std::cin >> p >> q;
            int divisor = (int)std::pow(2, q);
            ll largest = INT64_MIN, smallest = INT64_MAX;
            for(int i = 0; i < (1 << p) - 1; i++)
            {
               auto binary_str = intToModifiedBinary(i, p);
               ll j = modifiedBinaryToInt(binary_str);
            //    dbg(j, divisor);
               if(!(j % divisor))
                 if(j > largest) largest = j;
                 else if(j < smallest) smallest = j;
            }
            
            if(largest != INT64_MIN ||
               smallest != INT64_MAX)
            {
                std::string s;
                if(smallest != INT64_MAX && largest == INT64_MIN) 
                  s += std::to_string(smallest);
                else if(largest != INT64_MIN && smallest == INT64_MAX) 
                  s += std::to_string(largest);
                else s += std::to_string(smallest) + " " + std::to_string(largest);
                printf("Case %d: %s\n", c++, s.c_str());
            }
            else printf("Case %d: impossible\n", c++);  
        } 
    }
}