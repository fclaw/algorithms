#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>


typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
#define loop(x, s, n) for(int x = s; x < n; x++)
const int PYRAMID_SIZE = 9;

namespace algorithms::onlinejudge::arrays::bricks
{
    // https://onlinejudge.org/external/110/11040.pdf, non trivial 2D array manipulation
    void completePyramid(vvi& pyramid) 
    { 
        //   a
        //   x y   
        //   b z c
        // int a = pyramid[i - 2][j]
        // int b = pyramid[i][j]
        // int c = pyramid[i][j + 2]
        // int x = pyramid[i - 1][j]
        // int y = pyramid[i - 1][j + 1]
        // int z = pyramid[i][j + 1]
        for(int i = PYRAMID_SIZE - 1; i >= 2; i -= 2)
          for(int j = 0; j <= i; j += 2)
          {
              int a = pyramid[i - 2][j];
              int b = pyramid[i][j];
              int c = pyramid[i][j + 2];
              // Calculate z (the middle value on the current row)
              pyramid[i][j + 1] = (a - b - c) >> 1;

              // Now use z to find x and y
              pyramid[i - 1][j] = b + pyramid[i][j + 1];        // x
              pyramid[i - 1][j + 1] = c + pyramid[i][j + 1];    // y
          }

    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            vvi pyramid = vvi(PYRAMID_SIZE, vi(PYRAMID_SIZE, 0));
            for(int i = 0; i < PYRAMID_SIZE; i += 2)
              for(int j = 0; j < i + 1; j += 2)
              {
                  int val;
                  std::cin >> val;
                  pyramid[i][j] = val;
              }

            // ...
            completePyramid(pyramid);

            loop(i, 0, PYRAMID_SIZE)
            {
                loop(j, 0, i + 1)
                  std::cout << pyramid[i][j] << (j != i ? " " : "");
                std::cout << std::endl;
            }
        }
    }
}