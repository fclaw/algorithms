#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>





typedef std::vector<char> vc;
typedef std::vector<std::string> vs;


namespace algorithms::onlinejudge::complete_search::knuth
{
    /** https://onlinejudge.org/external/100/10063.pdf */
    void backtrack(const vc& letters, int i, vs xs, vs& ans)
    {
        if(i == letters.size()) 
        { ans = xs; return; }

        vs new_xs;
        if(xs.empty())
          new_xs.push_back(std::string(1, letters[i])); // Start with first letter
        else 
        {
            for(const auto& x : xs)
              for(int k = 0; k <= x.size(); k++) 
              {
                  std::string left = x.substr(0, k);
                  std::string right = x.substr(k, x.size() - k); // Fixing substring length
                  new_xs.push_back(left + letters[i] + right);
              }
        }
        backtrack(letters, i + 1, new_xs, ans);

    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        std::string l;
        bool notfirst = false;
        while(std::getline(std::cin, l))
        {
            if(notfirst) std::cout << std::endl;
            notfirst = true;            
            vc letters;
            for(auto c : l) 
              letters.push_back(c);
            vs ans;
            backtrack(letters, 0, {}, ans);
            for(auto a : ans) std::cout << a << std::endl;
        } 
    }
}