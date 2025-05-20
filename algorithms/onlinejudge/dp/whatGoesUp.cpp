#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>




typedef std::vector<int> vi;


namespace algorithms::onlinejudge::dp::what_goes_up
{
    /** https://onlinejudge.org/external/4/481.pdf */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        vi nums;
        int n;
        while(while_read(n)) 
          nums.push_back(n);
          
        vi seq;
        for(int n : nums)
        {
            auto it = std::lower_bound(seq.begin(), seq.end(), n);
            if(it == seq.end()) seq.push_back(n);
            else
            {
                int pos = it - seq.begin();
                if(pos == 0 && seq.size() == 1 && seq[pos] > n)
                  seq[pos] = n;
                else if(pos != 0 && seq.size() > 1) seq[pos] = n;
            }
        }
        printf("%d\n-\n", (int)seq.size());
        for(int s : seq) std::cout << s << std::endl;
    }
}