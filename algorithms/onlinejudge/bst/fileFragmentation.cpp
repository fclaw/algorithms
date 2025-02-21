#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>


typedef std::unordered_map<std::string, int> msi; 
typedef std::vector<std::string> vs;

namespace algorithms::onlinejudge::bst::file
{
    /** https://onlinejudge.org/external/102/10226.pdf 
     * N = number of fragments, B = total bits of
     * all fragments divided by N / 2; try all 2 × N ^ 2 concatenations of two fragments
     * that have length B; report the one with highest frequency; use map */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
          int tc;
          scanf("%d\n\n",&tc);
          while(tc--)
          {
              std::string fragment;
              vs fragments;
              while(std::getline(std::cin, fragment), 
                    !fragment.empty())
                fragments.push_back(fragment);

              msi files;  
              // pair all conceivable fragments O(N^2)
              for(int i = 0; i < fragments.size(); i++)
                for(int j = i + 1; j < fragments.size(); j++)
                  ++files[fragments[i] + fragments[j]],
                  ++files[fragments[j] + fragments[i]];
              
              int max_freq = INT32_MIN;
              std::string file;
              for(auto it : files)
                if(it.second > max_freq)
                { max_freq = it.second; file = it.first; }

              std::cout << file << std::endl;
              if(tc) std::cout << std::endl;
          }
    }
}