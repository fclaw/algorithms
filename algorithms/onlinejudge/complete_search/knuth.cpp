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
    void backtrack(const vc& letters, int i, vs tmp, vs& ans)
    {
        if(i == letters.size()) 
        { ans = tmp; return; }

        vs new_tmp;
        for(const auto& s : tmp)
        {
            // add at front
            std::string new_s_front = s;
            new_s_front.insert(0, 1, letters[i]); 
            new_tmp.push_back(new_s_front);

          for(int j = 1; j < s.size(); j++)
          {
              std::string new_s = s; 
              new_s.insert(j, 1, letters[i]);
              new_tmp.push_back(new_s);
          }

            // add at back
            std::string new_s_back = s;
            new_s_back.push_back(letters[i]);
            new_tmp.push_back(new_s_back);  
          }

        backtrack(letters, i + 1, new_tmp, ans);

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
            backtrack(letters, 1, {std::string(1, letters.front())}, ans);
            for(auto a : ans)
              std::cout << a << std::endl;
        } 
    }
}