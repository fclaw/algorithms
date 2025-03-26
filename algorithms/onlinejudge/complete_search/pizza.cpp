#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>



typedef std::vector<std::pair<int, int>> vpii;
// typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::pizza
{
 

    /** https://onlinejudge.org/external/5/565.pdf, backtracking with lots of pruning */
    std::string ans;
    const int Max = 16;
    bool request_found;
    bool isSatisfied(const std::pair<int, int>& pref, int toppings) 
    {
        if(toppings & pref.first) 
          return true;
        if((~toppings & pref.second)) 
          return true;
        return false;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        std::string l;
        vpii prefs;
        while(std::getline(std::cin, l))
        {
            if(l == ".")
            {
                ans = {};
                request_found = false;
                // loop over all possible set from 1 to (1 << Max) - 1
                for(int tops = 0; tops <= ((1 << Max) - 1) && !request_found; tops++)
                {
                    request_found = true;
                    for(const auto& p : prefs)
                      if(!isSatisfied(p, tops))
                      { request_found = false; break; }
                    if(request_found)
                      for(int t = 0; t < Max; t++)
                        if(tops & (1 << t))
                          ans += (t + 'A');
                }
                if(request_found) std::cout << "Toppings: " << ans << std::endl;
                else printf("No pizza can satisfy these requests.\n");
                prefs.clear();
            }
            else
            {
                l.pop_back();
                int likes = 0, dislikes = 0;
                for(int i = 0; i < l.size(); i += 2)
                {
                    int top = (l[i + 1] - 'A');
                    if(l[i] == '+') likes |= (1 << top);
                    else dislikes |= (1 << top);
                }
                prefs.push_back({likes, dislikes});
            }
        }
    }
}