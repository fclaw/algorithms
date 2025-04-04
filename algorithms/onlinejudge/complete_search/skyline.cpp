#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <string>




typedef std::vector<int> vi;
typedef std::vector<std::tuple<int, int, int>> vtiii;

namespace algorithms::onlinejudge::complete_search::skyline
{
    /** https://onlinejudge.org/external/1/105.pdf, height map, sweep left-right
        Skyline Problem (UVa 105)
        Approach:
        ---------
        1. **Height Map Construction**:
        - Allocate an array `height[10000]` to represent the maximum height at each x-coordinate.
        - For each building given by (L, H, R), update height[x] for all x in [L, R):
            This marks the height contributed by the building over its horizontal extent.

        2. **Sweeping Line**:
        - Traverse the height array from left (x = 0) to right.
        - Whenever the current height differs from the previous height, output a key point:
            - This marks the start of a new segment in the skyline.
            - Print x and the new height.
        - This effectively captures the transitions in height that define the skyline.

        3. **Efficiency**:
        - The problem guarantees all coordinates are < 10,000, so a fixed-size array works efficiently.
        - Time complexity is linear in the number of coordinates (O(N + 10000)), where N is number of buildings.

        Notes:
        - This algorithm avoids any complex data structures or sorting.
        - It exploits the fixed range of coordinates and is highly efficient for the given constraints.
    */
    const int MAX = static_cast<int>(1e4); // 10000
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int l, h, r;
        vtiii buildings;
        vi heights(MAX, INT32_MIN);
        while(std::cin >> l >> h >> r)
          buildings.push_back({l, h, r});

        int last = INT32_MIN;
        for(auto& [l, h, r] : buildings)
          for(int s = l; s < r; s++)
            heights[s] = std::max(heights[s], h),
            last = std::max(last, r);
        
        vi ans;
        int curr;    
        for(int i = 0; i < heights.size(); i++)
        {
            if(heights[i] == INT32_MIN || 
               heights[i] == curr)
              continue;
            curr = heights[i];
            ans.push_back(i);
            ans.push_back(heights[i]);
        }
        ans.push_back(last);
        ans.push_back(0);

        std::string s = {}; 
        for(int a : ans) s += std::to_string(a) + " ";
        s.pop_back();
        std::cout << s << std::endl;
    }
}