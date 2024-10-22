#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>


namespace algorithms::maths::onlinejudge::collatz
{

#define loop(x, s, n) for(int x = s; x < n; x++)

    /** https://en.wikipedia.org/wiki/Collatz_conjecture
     * https://onlinejudge.org/external/1/100.pdf 
     */
    void cycleLength(int n, int& cnt)
    {
        if(n == 1) { ++cnt; return; }
        ++cnt;
        if(!(bool)(n % 2)) cycleLength( n/ 2, cnt);
        else cycleLength(3 * n + 1, cnt);
    } 

    int getCycleLengths(int first, int second)
    {
        if(first > second)
        {
            int tmp = first;
            first = second;
            second = tmp;
        }
        int ans = 0;
        loop(i, first, second + 1) 
        {
            int cycle = 0;
            cycleLength(i, cycle);
            ans = std::max(ans, cycle);
        }
        return ans;
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int first, second;
        while(std::cin >> first >> second)
        {
            int ans = getCycleLengths(first, second);
            printf("%d %d %d\n", first, second, ans);
        }
    }
}