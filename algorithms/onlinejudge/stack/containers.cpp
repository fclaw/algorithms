#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
#include <string>


typedef std::stack<int> si;
typedef std::vector<int> vi;

namespace algorithms::onlinejudge::stack::containers
{
    
    /** https://onlinejudge.org/external/10/1062.pdf, 
     * LA 3752, WorldFinals Tokyo07, simulation 
     * with stack; maximum answer is 26 stacks; O(n) solution exists
     */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        std::string containers;
        int c = 0;
        while(true)
        {
            std::cin >> containers;
            if(containers == "end") break;
            
            int ans = 0;
            printf("Case %d: %d\n", ++c, ans);
        }
    }
}