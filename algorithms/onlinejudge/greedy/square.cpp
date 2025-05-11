#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <cctype>






struct Dir
{
    int r;
    int c;
};

typedef std::vector<char> vc;
typedef std::vector<vc> vvc;
typedef std::vector<Dir> vd;


namespace algorithms::onlinejudge::greedy::square
{
    /**  https://onlinejudge.org/external/115/11520.pdf, 
     * looking in four directions and assign a cell the smallest possible letter 
     * which is not in adjacent cells */
    int tc, s, c = 1;
    vd dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < s && c >= 0 && c < s; }
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

        std::cin >> tc;
        while(tc--)
        {
            std::cin >> s;
            vvc grid(s, vc(s));
            for(int i = 0; i < s; ++i)
              for(int j = 0; j < s; ++j)
                std::cin >> grid[i][j];
            
            for(int i = 0; i < s; ++i)
              for(int j = 0; j < s; ++j)
                if(!std::isalpha(grid[i][j]))
                {
                    int used = 0;
                    for(auto& d : dirs)
                    if(checkBoundary(i + d.r, j + d.c))
                    {
                       int adj_i = i + d.r;
                       int adj_j = j + d.c;
                       char adj_l = grid[adj_i][adj_j];
                       if(std::isalpha(adj_l)) 
                         used |= (1 << (adj_l - 'A'));
                    }

                    for(int l = 0; l < 26; ++l)
                      if(!(used & (1 << l)))
                      { grid[i][j] = l + 'A'; break; }
                }
            
            printf("Case %d:\n", c++);    
            for(int i = 0; i < s; ++i)
            {
                for(int j = 0; j < s; ++j)
                  std::cout << grid[i][j];
                std::cout << std::endl;
            }
        }
    }
}