#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>







typedef std::vector<int> vi;
typedef std::unordered_map<char, vi> mcvi;


namespace algorithms::onlinejudge::divide_conquer::Fill_Bates
{
    /** https://onlinejudge.org/external/105/10567.pdf, store increasing indices of each char of ‘S’ in 52 vectors; 
     * for each query, binary search for the position of the char in the correct vector */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);    

        std::string s;
        while(std::cin >> s)
        {
            mcvi chars_dispositions;
            int order = 1;
            char c = s[0];
            for(int i = 0; i < s.size(); i++)
              chars_dispositions[s[i]].push_back(i);

            int queries;
            std::cin >> queries;
            std::string q;
            while(queries--)
            {
                std::cin >> q;
                int curr_pos = 0;
                bool nf = false;
                int start = -1, end = -1;
                for(char c : q)
                {
                    if(!chars_dispositions.count(c)) 
                    { nf = true; break; }
            
                    const vi &positions = chars_dispositions[c];
                    auto it = std::lower_bound(positions.begin(), positions.end(), curr_pos);
                    if (it == positions.end())
                    { nf = true; break; }
            
                    int matched_pos = *it;
                    if (start == -1) start = matched_pos;
                    end = matched_pos;
                    curr_pos = matched_pos + 1;
                }

                if(nf) printf("Not matched\n");
                else printf("Matched %d %d\n", start, end);
            }
        }
    }
}