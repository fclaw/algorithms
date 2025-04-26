#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <iomanip>




typedef double dd;

const dd root_eps = 1e-9;
const dd ans_eps = 1e-3;

int p, q, r, s, t, u;

dd L = 0.0000;
dd R = 1.0000;

double solve(dd x) {
    return p * std::exp(-x) + q * std::sin(x) + r * std::cos(x) + s * std::tan(x) + t * x * x + u;
}



namespace algorithms::onlinejudge::divide_conquer::solve_it
{
    /** https://onlinejudge.org/external/103/10341.pdf,(bisection method discussed in this section; for alternative
     * solutions, see https://algorithmist.com/wiki/UVa_10341_-_Solve_It  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        while(scanf("%d %d %d %d %d %d\n", &p, &q, &r, &s, &t, &u) != EOF)
        {
            // at 0 it has a positive sign, at 1 a negative one
            double l = L, r = R;
            double ans, root;
            do
            {
                root = (l + r) / 2;
                ans = solve(root);
                if(ans > 0) l = root;
                else r = root;
            } while((r - l) > root_eps);
            if(std::abs(ans) > ans_eps)
              printf("No solution\n");
            else std::cout << std::fixed << std::setprecision(4) << root << std::endl;
        } 
    }
}