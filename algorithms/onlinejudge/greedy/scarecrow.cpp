#include "../debug.h"
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>






typedef long long ll;
typedef std::vector<char> vc;


namespace algorithms::onlinejudge::greedy::scarecrow
{
    /** https://onlinejudge.org/external/124/12405.pdf, simple interval covering */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            int N;
            std::cin >> N;
            vc land(N);
            for(int i = 0; i < N; i++)
              std::cin >> land[i];
            
            int scarecrows = 0;  
            for(int i = 0; i < N;)
            {
                if(land[i] == '#') 
                { i++; continue; }
                int isArable = false;
                for(int j = i; j < std::min(N, i + 3); j++)
                  isArable |= (land[j] == '.');
                if(isArable)
                { scarecrows++; i += 3; }
            }

            printf("Case %d: %d\n", c++, scarecrows);
        } 
    }
}