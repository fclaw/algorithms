#include <vector>
#include <cstdio>
#include <iostream>
#include <bitset>

namespace algorithms::dp::codeforces
{
    // https://codeforces.com/problemset/problem/189/A
    /**
     * there is a ribbon, its length is n. it is to be cut in a way that fulfils the following two conditions:
     * 1 - After the cutting each ribbon piece should have length a, b or c.
     * 2 - After the cutting the number of ribbon pieces should be maximum.
     * determine the number of ribbon pieces after the required cutting.
     * The first line contains four space-separated integers n, a, b and c (1 ≤ n, a, b, c ≤ 4000) — t
     * he length of the original ribbon and 
     * the acceptable lengths of the ribbon pieces after the cutting, correspondingly. 
     * The numbers a, b and c can coincide.
     */
    const size_t MAX = 4000;
    int size;
    int ribbon;
    std::bitset<MAX> pieces;
    void dfs(const std::vector<int>& cuts, int i, int p, std::bitset<MAX>& m)
    {
    }

    void submit_189_a()
    {
    }
}