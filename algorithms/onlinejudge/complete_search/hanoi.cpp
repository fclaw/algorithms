#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>


typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::hanoi
{
    /** https://onlinejudge.org/external/102/10276.pdf, 
     * insert a number one by one  
     * The number of balls that can be placed is finite due to the following reasons:
     * 1. Perfect Square Growth:
     * - The gap between consecutive perfect squares increases as numbers grow: (n+1)^2 - n^2 = 2n + 1.
     * - This widening gap makes it harder to find valid square sums indefinitely.
     * 2. Limited Pegs:
     * - Each peg must hold a ball such that its sum with the new ball forms a perfect square.
     * - With a fixed number of pegs (N), the choices become more restricted as balls increase.
     * 3. Finite Termination:
     * - Eventually, no peg will satisfy the perfect square condition for a given ball.
     * - Empirical tests suggest a stopping point, meaning an infinite placement is not possible.
     * => If a valid sequence cannot continue indefinitely, print '-1' to indicate the limit.
     *  T(k, n) = l
     *  k - is the current ball number (starting from 1, 2, 3, ..),  
     *  n - is the number of pegs available, 
     *  l - is the maximum number of balls that can be placed while following the given constraints
     *  recurrence relation: T(k, n) = max(T(k + 1, n), T(k, n - 1)) + 1), base: T(1, n) = 1;
     * */
    bool isPerfectSquare(int s) 
    { int r = std::sqrt(s); return r * r == s; }
    void backtrack(int n, int k, vi& pegs, int& balls) 
    {
        bool ok = false;
        for(int i = 0; i <= k; i++)
          if(pegs[i] != 0 && isPerfectSquare(n + pegs[i]))
          {
              pegs[i] = n;
              balls++;
              backtrack(n + 1, k, pegs, balls);
              return;
          }
        
        if(k < pegs.size())  
        {
            pegs[k] = n;
            balls++;
            backtrack(n + 1, k + 1, pegs, balls);
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
            int limit;
            std::cin >> limit;
            vi pegs(limit);
            int balls = 0;
            backtrack(1, 0, pegs, balls);
            std::cout << balls << std::endl;
        }
    }
}