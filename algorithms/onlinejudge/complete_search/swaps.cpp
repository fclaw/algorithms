#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>




typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::swaps
{

  
    /** https://onlinejudge.org/external/3/331.pdf, n ≤ 5 */
    int ways;
    bool isSorted(const vi& xs, int i)
    {
        if(i == 0 || i == 1)
          return xs[0] <= xs[1];
        return xs[i - 1] <= xs[i] && isSorted(xs, i - 1);   
    }
    void backtrack(vi& xs, bool isSwap, int& ways)
    {
        if(isSorted(xs, xs.size() - 1)) 
        { if(isSwap) ways++; return; }

        for (int i = 1; i < xs.size(); i++)    
          if (xs[i - 1] > xs[i])
          {  // Swap only when it helps
              std::swap(xs[i], xs[i - 1]);
              backtrack(xs, true, ways);
              std::swap(xs[i], xs[i - 1]);
          }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int c = 1;
        while(true)
        {  
            int N;
            std::cin >> N;
            if(!N) break;
            vi nums(N);
            for(int i = 0; i < N; i++)
              std:cin >> nums[i];

            int ways = 0;
            backtrack(nums, false, ways);
            printf("There are %d swap maps for input data set %d.\n", ways, c++);
        }
    }
}