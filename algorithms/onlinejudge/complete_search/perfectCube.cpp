#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>




namespace algorithms::onlinejudge::complete_search::perfect_cube
{
    /** https://onlinejudge.org/external/3/386.pdf, 4 nested loops with pruning */
    const int MAX = 200;
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        for(int a = 2; a <= MAX; a++)
          for(int b = 2; b < a; b++)
            for(int c = b; c < a; c++)
              for(int d = c; d < a; d++)
                if(a * a * a == b * b * b + c * c * c + d * d * d)
                  printf("Cube = %d, Triple = (%d,%d,%d)\n", a, b, c, d);
    }
}