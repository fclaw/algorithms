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
    int M, N;
    int getCnt(const vvi& board) 
    { 
        int counter = 0;
        for(int r = 0; r < M; r++)
          for(int c = 0; c < N; c++)
            if(board[r][c])
            {
                for(int l = 1; l <= N - c; l++)
                  for(int h = 1; h <= M - r; h++)
                  {
                      bool isFailed = false;
                      for(int i = r; i < r + h && !isFailed; i++)
                        for(int j = c; j < c + l && !isFailed; j++)
                          if(!board[i][j]) isFailed = true;
                     if(!isFailed) counter++;
                  }
            }
        return counter;    
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
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
            std::cout << getCnt(board) << std::endl;   
        }
    }
}