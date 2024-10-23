#include <cassert>
#include <optional>
#include <iostream>

namespace algorithms::maths::onlinejudge::rational_neighbour
{

typedef std::pair<int, int> neighbour;

    /** https://onlinejudge.org/external/9/906.pdf, 
     *  compute c, from d = 1 until a / b < c / d 
     *  Given a rational a/b and an upper bound n for the distance, the problem consists to find the rational c/d such that:
     *  1 a/b < c/d;
     *  2 the distance between the rationals a/b and c/d is smaller or equal than n
     *  3 the denominator d is as small as possible
     * */
    neighbour getNeighbour(int num, int denom, double n) { return {1, 1}; }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int num, denom;
        double n;
        while(std::cin >> num >> denom)
        {
            std::cin >> n;
            neighbour p = getNeighbour(num, denom, n);
            printf("%d %d\n", p.first, p.second);
        }
    }
}