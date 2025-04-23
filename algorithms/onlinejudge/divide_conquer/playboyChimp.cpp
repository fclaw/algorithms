#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>





typedef std::vector<int> vi;

namespace algorithms::onlinejudge::divide_conquer::playboy_chimp
{
    /** https://onlinejudge.org/external/106/10611.pdf, binary search */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int N;
        while(std::cin >> N)
        {
            vi heights(N);
            for(int i = 0; i < N; i++)
              std::cin >> heights[i];
           
            int q, t;
            std::cin >> q;
            while(q--)
            {
                std::cin >> t;
                auto t_it = std::upper_bound(heights.begin(), heights.end(), t);
                auto s_it = std::lower_bound(heights.begin(), heights.end(), t);
                int tallest = t_it != heights.end() ? *t_it : -1;
                int shortest =  s_it > heights.begin() && *(s_it - 1) < t ? *(s_it - 1) : -1;
                std::string s = shortest != -1 ? std::to_string(shortest) : "X";
                s += " ";
                s += tallest != -1 ? std::to_string(tallest) : "X";
                std::cout << s << std::endl;
            }  
        }  
    }
}