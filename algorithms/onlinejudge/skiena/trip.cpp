#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>


typedef std::vector<double> vd;

namespace algorithms::onlinejudge::skiena::trip
{
    /** https://onlinejudge.org/external/101/10137.pdf
     * The group agrees in advance to share expenses equally, but it is not practical to have them share
     * every expense as it occurs. So individuals in the group pay for particular things, like meals, hotels, taxi
     * rides, plane tickets, etc. After the trip, each student’s expenses are tallied and money is exchanged so
     * that the net cost to each is the same, to within one cent. In the past, this money exchange has been
     * tedious and time consuming. Your job is to compute, from a list of expenses, the minimum amount of
     * money that must change hands in order to equalize (within a cent) all the students’ costs. 
     */
    // O(n) complexity, 
    // linear scan to find average, go over elements which are less then average to accumulate their diff with average
    double makeEqual(vd expenses, double avg) 
    {
        double overpaid = 0;
        double underpaid = 0;
        for(double e : expenses)
          if(e < avg) underpaid += (avg - e);
          else overpaid += (e - avg);
        return std::min(overpaid, underpaid != 0 ? underpaid : avg);
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int n;
        while(std::cin >> n && (bool)n)
        {
            vd expenses = vd(n, 0);
            double e, total = 0;
            for(int i = 0; i < n; i++)
            {
                std::cin >> e;
                total += e;
                expenses[i] = e;
            }
            double avg = std::round((total / n) * 100.0) / 100.0;
            double ans = makeEqual(expenses, avg);
            printf("$%.2f\n", ans);
        } 
    }
}