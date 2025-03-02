#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <bitset>



namespace algorithms::onlinejudge::complete_search::sum_it_up
{

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


    /** https://onlinejudge.org/external/5/574.pdf, 
     * print all solutions with backtracking */
    void backtrack(int ref, const vi& nums, int idx, vi& curr, vvi& combinations) 
    {
        if (ref == 0)
        { combinations.push_back(curr); return; }
    
        for (int i = idx; i < nums.size(); i++) 
        {
            if (i > idx && nums[i] == nums[i - 1]) 
              continue;  // Skip duplicates properly
            if (ref - nums[i] >= 0)
            {
              curr.push_back(nums[i]);
              backtrack(ref - nums[i], nums, i + 1, curr, combinations); // Move forward
              curr.pop_back();  // Undo choice
            }
        }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        while(true)
        {
            int ref, N, i = 0;
            std::cin >> ref >> N;
            if(!ref && !N) break;
            vi nums(N);
            while(i < N) std::cin >> nums[i++];

            vvi combinations;
            vi xs;
            backtrack(ref, nums, 0, xs, combinations);

            if(combinations.empty())
              printf("Sums of %d:\nNONE\n", ref);
            else
            {
                printf("Sums of %d:\n", ref);
                for(auto c : combinations)
                {
                    for(int i = 0; i < c.size(); i++)
                    { std::cout << c[i]; if(i != c.size() - 1) std::cout << "+"; }
                    std::cout << std::endl;
                }
            }
        }  
    }
}