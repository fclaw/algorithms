#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>




typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

namespace algorithms::onlinejudge::complete_search::coloured_field
{
    /** https://onlinejudge.org/external/101/10102.pdf, 
     * 4 nested loops will do, we do not need BFS; 
     * get max of minimum Manhattan distance from a ‘1’ to a ‘3’ */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int N;
        while(std::cin >> N)
        {
            vvi field(N, vi(N));
            for(int i = 0; i < N; i++)
              for(int j = 0; j < N; j++)
              {
                  char v;
                  std::cin >> v;
                  field[i][j] = (v - '0');
              }
            
            int ans = INT32_MIN;
            for(int i = 0; i < N; i++)
              for(int j = 0; j < N; j++)
                if(field[i][j] == 1)
                {
                    int dist = INT32_MAX;
                    for(int k = 0; k < N; k++)
                      for(int l = 0; l < N; l++)
                        if(field[k][l] == 3)
                          dist = std::min(dist, std::abs(i - k) + std::abs(j - l));
                    ans = std::max(ans, dist);      
                }
            std::cout << ans << std::endl;    
        }
    }
}