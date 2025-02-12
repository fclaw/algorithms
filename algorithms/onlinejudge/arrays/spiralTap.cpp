#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>


typedef long long ll;
#define loop(x, s, n) for(int x = s; x < n; x++)

namespace algorithms::onlinejudge::arrays::spiral_tap
{

    enum Dir { Down, Left, Up, Right};
    // https://onlinejudge.org/external/109/10920.pdf, simulate the process
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        ll n, target;
        while(true)
        {
            std::cin >> n >> target;
            if(n == 0 && target == 0) break;
            int centre = n / 2 + 1;
            ll line = centre, column = centre;
            if(target != 1)
            {
                int level;
                ll square;
                ll sq = std::sqrt(target);
                if(!(sq % 2)) square = sq + 1;
                else if(sq + 2 <= n && sq * sq != target) 
                  square = sq + 2;
                else square = sq;
                
                level = (square - 1) / 2;
                line += level, column += level;

                ll val = square * square;
                bool isFinished = false;
                loop(d, Down, 4 && !isFinished)
                  loop(j, 0, square - 1 && !isFinished)
                  {
                      if(val == target) 
                      { isFinished = true; break; }
                      --val;
                      if(d == Up) ++line;
                      if(d == Down) --line;
                      if(d == Left) --column;
                      if(d == Right) ++column;
                   }
            }
            printf("Line = %lld, column = %lld.\n", line, column);
        }
    }
}