#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>




typedef long long ll;
typedef std::vector<std::pair<ll, int>> vpli;


namespace algorithms::onlinejudge::complete_search::magic_numbers
{
    /**  https://onlinejudge.org/external/4/471.pdf, somewhat similar to UVa 725 
     * We are given: s1 / s2 = N, with s1, s2, N being positive integers.
     * From the equation, we know s1 = N * s2.
     * 
     * Constraints:
     *   - 1 <= s2 < N        (so s1 = N * s2 < N * N)
     *   - s1 < INT32_MAX    (since s1 must fit in a 32-bit integer)
     * 
     * Therefore, s2 must also satisfy:
     *   s2 < INT32_MAX / N
     * 
     * So we tighten the upper bound for s2:
     *   upper_s2 = min(N - 1, INT32_MAX / N)
     * 
     * This significantly reduces the search space from a potential 
     * ~2 billion iterations to at most N - 1 iterations.
     * */
    bool isValid_ll(ll n)
    {
        ll mask = 0;
        ll d;
        bool isValid = true;
        while(n)
        {
            d = n % 10; 
            if((mask & (1LL << d)))
            { isValid = false; break; }
            mask |= (1LL << d);
            n /= 10;
        }
        return isValid;
    }
    void generatePairs(ll n, vpli& pairs)
    {
        ll upper_s2 = 9999999999LL / n;
        for(ll s2 = 1; s2 <= upper_s2; s2++)
        {
            ll s1 = s2 * n;
            if(!isValid_ll(s2) ||
               !isValid_ll(s1))
              continue;
            pairs.push_back({s1, s2});
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
            if(tc) std::cin.ignore();
            ll n;
            vpli numbers;
            std::cin >> n;
            generatePairs(n, numbers);
            for(auto& p : numbers)
              printf("%llu / %d = %llu\n", p.first, p.second, n);
            if(tc) std::cout << std::endl;
        }
    }
}