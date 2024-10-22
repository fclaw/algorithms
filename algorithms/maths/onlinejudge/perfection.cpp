#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

namespace algorithms::maths::onlinejudge::perfection
{

typedef std::vector<int> vi;
typedef std::vector<std::pair<int, std::string>> vp;

enum Perfection { PERFECT, DEFICIENT, ABUNDANT };

    /** https://onlinejudge.org/external/3/382.pdf
     * do trial division, https://en.wikipedia.org/wiki/Trial_division */
    std::string printPerfection(Perfection p)
    {
        std::string s;
        if(p == PERFECT) s = "PERFECT";
        if(p == DEFICIENT) s = "DEFICIENT";
        if(p == ABUNDANT) s = "ABUNDANT";
        return s;
    }
    
    vi doTrialDivision(int n) 
    {
        vi divisors;
        int divisor = 1;
        while(divisor < n)
        {
            if(!(bool)(n % divisor))
                divisors.push_back(divisor);
            divisor += 1;
        }
        return divisors;
    }
    std::pair<int, std::string> determine(int n) 
    {
        vi xs = doTrialDivision(n);
        int sum = 0;
        for(int x : xs) sum += x;
        std::pair<int, std::string> p;
        if(sum == n) p = {n, printPerfection(PERFECT)};
        if(sum > n) p = {n, printPerfection(ABUNDANT)};
        if(sum < n) p = {n, printPerfection(DEFICIENT)};
        return p;
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        vi nums;
        int n;
        while(std::cin >> n)
        {
            if(n == 0) break;
            nums.push_back(n);
        }
        vp ans;
        for(int n : nums) ans.push_back(determine(n));
        printf("PERFECTION OUTPUT\n");
        // the echoed integers should be right justified within the first 5 spaces of the output line
        // followed by two blank spaces, followed by the description of the integer
        for(auto p : ans) printf("%5d  %s\n", p.first, p.second.c_str());
        printf("END OF OUTPUT\n");
    }
}