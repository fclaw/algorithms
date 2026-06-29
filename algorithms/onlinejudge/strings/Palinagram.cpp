
/*
───────────────────────────────────────────────────────────────
🧳 UVa 12770 Palinagram, https://onlinejudge.org/external/127/12770.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




namespace algorithms::onlinejudge::strings::palinagram
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        std::string partial_anagram;
        while(std::cin >> partial_anagram && 
              partial_anagram != "#") {
          std::vector<std::pair<char, int>> freq;
          for(char c : partial_anagram) {
            auto cmp = [&c](const std::pair<char, int>& p) 
                           { return c == p.first; };
            auto it = std::find_if(freq.begin(), freq.end(), cmp);
            if(it == freq.end()) {
              freq.push_back({c, 1});
            } else { it->second++; }
          }
          
          auto cmp = [](const std::pair<char, int>& lhs, 
                        const std::pair<char, int>& rhs) 
                     { return (lhs.first < rhs.first) || 
                              (lhs.first == rhs.first && 
                               lhs.second > rhs.second); 
                     };
          std::sort(freq.begin(), freq.end(), cmp);  

           std::string ans;
           for(auto& p : freq) {
              if((p.second % 2)) {
                ans.push_back(p.first);
              }
           }
           if(!ans.empty()) ans.pop_back();
           std::cout << ans << std::endl;
        }
    }
}