#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>






typedef std::vector<std::string> vs;


int longestCommonSuffixPrefix(const std::string& a, const std::string& b) 
{
    int maxLen = 0;
    int lenA = a.length(), lenB = b.length();
    
    // Check all possible suffixes of 'a' and prefixes of 'b'
    for (int i = 1; i <= std::min(lenA, lenB); ++i)
      if(a.substr(lenA - i) == b.substr(0, i))
        maxLen = i;

    // Return the longest common substring
    return maxLen;
}


namespace algorithms::onlinejudge::complete_search::overlapping_scenes
{
    /** https://onlinejudge.org/external/122/12249.pdf, LA 4994, KualaLumpur10, try all permutations, a bit of string matching  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            int N;
            std::cin >> N;
            vs scenes(N);
            for(int i = 0; i < N; i++)
              std::cin >> scenes[i];

            std::sort(scenes.begin(), scenes.end());

            int min_length = INT32_MAX;
            do
            {
                std::string s = scenes[0];
                for(int i = 1; i < N; i++)
                {
                    int j = longestCommonSuffixPrefix(s, scenes[i]);
                    s += scenes[i].substr(j, scenes[i].size());
                }
               
                min_length = std::min(min_length, (int)s.length());
            } while (std::next_permutation(scenes.begin(), scenes.end()));
            printf("Case %d: %d\n", c++, min_length);
        }
    }
}