#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>



typedef std::vector<std::pair<int, int>> vpii;
typedef std::vector<int> vi;
typedef std::unordered_set<int> si;


namespace algorithms::onlinejudge::complete_search::pizza
{
 

    /** https://onlinejudge.org/external/5/565.pdf, backtracking with lots of pruning */
    std::string ans;
    bool isSatisfied(const std::pair<int, int>& pref, int toppings) 
    {
        if (toppings & pref.first)
          return true;  // at least one liked topping is present
        if (!(toppings & pref.second))
          return true;  // no likes, but also no disliked topping present
        return false;     // either some dislikes present, or no likes at all
    }
    // recursive function to count set bits
    void backtrack(int i, const vi& xs, const vpii& prefs, int curr_tops)
    {
        // std::cout << curr_tops << "\n";
        // ❌ Base case: nothing more to try
        if (i == xs.size()) return;
   
        bool satisfied = true;
        for(const auto& p : prefs)
          if(!isSatisfied(p, curr_tops))
          { satisfied = false; break; }

        if(satisfied)
        {
            std::string local;
            for(int x : xs)
              if((curr_tops & (1 << x)))
                local += (x + 'A');    
            if (ans.empty() ||
                local.size() > ans.size() || 
                (local.size() == ans.size() && local > ans))
              ans = local;
              std::sort(ans.begin(), ans.end());
        }

        // Try with xs[i]
        backtrack(i + 1, xs, prefs, curr_tops | (1 << xs[i]));
        // Try without xs[i]
        backtrack(i + 1, xs, prefs, curr_tops);
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        std::string l;
        vpii prefs;
        si tmp;
        vi tops;
        while(std::getline(std::cin, l))
        {
            if(l == ".")
            {
                ans = {};
                tops.assign(tmp.begin(), tmp.end());
                backtrack(0, tops, prefs, 0);
                if(!ans.empty()) std::cout << "Toppings: " << ans << std::endl;
                else printf("No pizza can satisfy these requests.\n");
                prefs.clear();
                tmp.clear();
            }
            else
            {
                l.pop_back();
                int likes = 0, dislikes = 0;
                for(int i = 0; i < l.size(); i += 2)
                {
                    int top = (l[i + 1] - 'A');
                    tmp.insert(top);
                    if(l[i] == '+') likes |= (1 << top);
                    else dislikes |= (1 << top);
                }
                prefs.push_back({likes, dislikes});
            }
        }
    }
}