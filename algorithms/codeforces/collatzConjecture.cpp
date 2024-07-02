#include <iostream>
#include <tuple>

namespace algorithms::codeforces
{

    // https://codeforces.com/contest/1982/problem/B
    int solveCollatzConjecture(int n, int c, int t)
    {
        int res = n;
        int constant = c;
        int times = t; 
        while(times > 0)
        {
            res++;
            while(res % constant == 0)
                res /= constant;
            times--;
        }

        return res;
    }
}