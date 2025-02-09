#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>

typedef std::vector<int> vi;

namespace algorithms::onlinejudge::arrays::gas_station
{
    /** https://onlinejudge.org/external/110/11093.pdf
     * linear scan, circular array, a bit challenging  */
    // greedy approach with optimization:
    // start from station A to C 
    // If starting from station A results in failure at C, then any station between A and C also cannot be a valid starting point.
    // This is because the total fuel from A to C is negative, meaning we are in deficit before reaching C.
    // Hence, when a failure occurs at C, we can jump directly to station C + 1 as the new starting candidate.
    int canCompleteLap(const vi& petrol, const vi& distance)
    {
        int N = petrol.size();
        int station = -1;
        int start = 0;
        bool finished = false;
        while(start < N && !finished)
        {
            int next = start;
            int tank = petrol[start];
            while(true)
            {
                tank -= distance[next];
                ++next;
                if(next == N) next = 0;
                if(tank < 0 || next == start) break; 
                tank += petrol[next];
            }
            if(tank >= 0) { station = start; finished = true; }
            else if(start < next) start = next;
            else finished = true;
        }
        return finished && (station != -1) ? ++station : station;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            int n, var;
            std::cin >> n;
            // First N integers denote the values of p(i) (petrol available at station i)
            vi petrol = vi(n);
            // subsequent N integers denote the value of q(i) 
            // (amount of patrol needed to go to the next station 
            // in the clockwise direction
            vi distance = vi(n);
            for(int i = 0; i < n; i++)
              std::cin >> var,
              petrol[i] = var;
            for(int i = 0; i < n; i++)
              std::cin >> var,
              distance[i] = var;
            int station = canCompleteLap(petrol, distance);
            if(station != -1) 
              printf("Case %d: Possible from station %d\n", c++, station);
            else printf("Case %d: Not possible\n", c++);
        }
    }
}