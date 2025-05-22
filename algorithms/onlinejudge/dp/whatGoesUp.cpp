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
    /** https://onlinejudge.org/external/4/481.pdf  */
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
        int n, i = 0;
        while(while_read(n))
          nums.push_back(n);
        
        int s = (int)nums.size();
        vi lis;
        vi parent(s, -1);

        for(int i = 0; i < s; ++i)
        {
            auto cmp = [&nums](int index, int val) { return nums[index] < val; };
            int pos = std::lower_bound(lis.begin(), lis.end(), nums[i], cmp) - lis.begin();
            if(pos == (int)lis.size())
              lis.push_back(i);
            else lis[pos] = i;
            if(pos > 0) parent[i] = lis[pos - 1];
        }
        // reconstruct
        vi real_lis;
        for(int i = lis.back(); i >= 0; i = parent[i])
          real_lis.push_back(nums[i]);

        std::cout << lis.size() << std::endl << "-" << std::endl;
        for(auto it = real_lis.rbegin(); it != real_lis.rend(); ++it) std::cout << *it << std::endl;
    }
}