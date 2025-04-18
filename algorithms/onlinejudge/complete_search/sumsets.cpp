#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>




typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::sumsets
{
    /** https://onlinejudge.org/external/101/10125.pdf, sort; 4 nested loops; plus binary search  */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int N;
        while(std::cin >> N && N)
        {
            vi nums(N);
            for(int i = 0; i < N; i++)
              std::cin >> nums[i];
            
            std::sort(nums.begin(), nums.end());

            int pos = -1;
            for(int i = 0; i < N; i++)
              for(int j = i + 1; j < N; j++)
                for(int k = j + 1; k < N; k++)
                {
                    int sum = nums[i] + nums[j] + nums[k];
                    bool isOk = std::binary_search(nums.begin(), nums.end(), sum);
                    auto it = std::lower_bound(nums.begin(), nums.end(), sum);
                    if(isOk) { pos = std::max(pos, (int)(it - nums.begin())); }
                }  
            std::cout << (pos != -1 ? std::to_string(nums[pos]) : "no solution") << std::endl;
        }  
    }
}