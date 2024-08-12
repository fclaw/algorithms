#include <algorithm>

namespace algorithms::backtrack::leetcode::tiling
{
    // https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares
    // Given a rectangle of size n x m, 
    // return the minimum number of integer-sided squares that tile the rectangle.
    // hints:
    //  Suppose you've placed a bunch of squares. 
    //    Where is the natural spot to place the next square?
    //  The maximum number of squares to be placed will be <= max(n, m)
    // int ans = 0;
    int N;
    int M;
    int ans;
    bool checkBoundary(int r, int c) 
      { return r >= 0 && r < N && c >= 0 && c < M; }  
    void backtrack(int r, int c, int squares)
    {
    }
    int tilingRectangle(int n, int m) 
    { 
        N = n;
        M = m;
        backtrack(0, 0, 0);
        return ans;
    }
}