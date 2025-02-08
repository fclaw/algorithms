#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>


namespace algorithms::onlinejudge::bits::gray_code
{
    // https://onlinejudge.org/external/111/11173.pdf,
    // Grey Codes with a one-liner bit manipulation expression for each
    // test case, i.e. find the k-th Gray code
    // a Gray Code for n bits is a sequence of 2 n different n-bit integers 
    // with the property that every two neighbouring integers differ in exactly one bit
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        scanf("%d", &tc);
        while(tc--)
        {
            
        }
    }
}