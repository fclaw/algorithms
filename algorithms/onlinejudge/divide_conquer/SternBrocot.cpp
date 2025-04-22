#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>





typedef long long ll;


struct Fraction
{
    int num;
    int denom;
};

constexpr Fraction operator + (const Fraction& lhs, const Fraction& rhs) 
{ return { lhs.num + rhs.num, lhs.denom + rhs.denom}; }

constexpr bool operator < (const Fraction& lhs, const Fraction& rhs) 
{ return lhs.num * rhs.denom < rhs.num * lhs.denom; }

constexpr bool operator == (const Fraction &lhs, const Fraction& rhs) 
{ return lhs.num == rhs.num && lhs.denom == rhs.denom; }

namespace algorithms::onlinejudge::divide_conquer::Stern_Brocot
{
    /** https://onlinejudge.org/external/100/10077.pdf, (binary search */
    void buildPath(const Fraction& left, const Fraction& right, const Fraction& t, std::string& path)
    {
        Fraction m = left + right;
        if(m == t) return;
        if(m < t) 
        { path += 'R'; buildPath(m, right, t, path); }
        else 
        { path += 'L'; buildPath(left, m, t, path); }
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int num, denom;
        while(std::cin >> num >> denom)
        {
            if(num == 1 && denom == 1) break;
            Fraction left = {0, 1};
            Fraction right = {1, 0};
            Fraction target = {num, denom};
            std::string path;
            buildPath(left, right, target, path);
            std::cout << path << std::endl;
        }
    }
}