#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>


typedef std::vector<int> vi;

namespace algorithms::onlinejudge::complete_search::closest_sums
{
    /** https://onlinejudge.org/external/104/10487.pdf, sort and then do O(n ^ 2) pairings  */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int c = 1;
        int N;
        while(std::cin >> N && N)
        {
            vi nums(N);
            for(int i = 0; i < N; i++)
              scanf("%d\n", &nums[i]);
            
            vi sums;
            for(int i = 0; i < N; i++)
              for(int j = i + 1; j < N; j++)
                if(!used.count(nums[i] + nums[j]))
                  sums.push_back(nums[i] + nums[j]);
            std::sort(sums.begin(), sums.end());

            printf("Case %d:\n", c++);
            int q, v;
            std::cin >> q;
            while(q--)
            {
                scanf("%d\n", &v);
                auto it = std::lower_bound(sums.begin(), sums.end(), v);
                int ans;
            
                if (it == sums.begin()) {
                    ans = *it;
                } else if (it == sums.end()) {
                    ans = *(it - 1);
                } else {
                    int a = *it;
                    int b = *(it - 1);
                    ans = (std::abs(a - v) < std::abs(b - v)) ? a : b;
                }
                printf("Closest sum to %d is %d.\n", v, ans);
            }
        }
    }
}