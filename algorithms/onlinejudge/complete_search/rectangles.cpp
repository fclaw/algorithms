#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>




typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

namespace algorithms::onlinejudge::complete_search::rectangles
{
    /** https://onlinejudge.org/external/105/10502.pdf, 6 nested loops, rectangle, not too hard  */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int M, N;
        while(std::cin >> M && M)
        {
            std::cin >> N;
            vvi board(M, vi(N));
            for(int i = 0; i < M; i++)
              for(int j = 0; j < N; j++)
              {
                  char c;
                  std::cin >> c;
                  board[i][j] = (int)c - 48;
              }
            
            int cnt = 0;
            for(int i = 0; i < M; i++)
              for(int j = 0; j < N; j++)
                if(board[i][j])
                {}
                
            std::cout << cnt << std::endl;      
        }
    }
}