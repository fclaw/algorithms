#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
#include <cmath>  // For std::round



typedef std::vector<std::pair<double, double>> vpdd;
typedef double dd;
constexpr double EPS = 1e-6;


namespace algorithms::onlinejudge::complete_search::budget_travel
{
    /** https://onlinejudge.org/external/2/222.pdf, 
     * looks like a DP problem, but the state cannot be memoized as ‘tank’ is floating-point; 
     * fortunately, the input is not large
     * General Approach for Solving the Pathfinding Problem:
    *  1. Enumerating All Paths with Backtracking:
    *   - Recursively explore all possible routes from the start to the destination.
    *   - Each decision branches into multiple possibilities, forming a tree-like exploration.
    *  2. Pruning to Avoid Redundant Computation:
    *   - Bounding Constraints: Discard paths that exceed a given constraint (e.g., cost, number of moves).
    *   - Cycle Prevention: Use a `visited` mechanism to prevent revisiting stations/nodes.
    *   - Early Termination: If an optimal path is found early, halt further exploration in that branch.
    *  3. Greedy Heuristics & Sorting for Efficiency (optional):
    *   - Sorting choices optimally (e.g., by cost) helps prioritize better solutions.
    *   - Reduces the search depth by quickly identifying promising paths.
    *  4. Using Memoization to Cache Results (optional):
    *   - If a state (combination of visited nodes and remaining budget) is revisited, skip redundant computation.
    *   - Bridges the gap between backtracking and dynamic programming.
    *  5. Bridging Backtracking with Other Strategies:
    *   - Backtracking ensures completeness but can be slow.
    *   - Combining it with greedy choices (e.g., prioritizing the cheapest move first) speeds up finding a near-optimal solution.
    *   - In some cases, graph search algorithms (like Dijkstra’s or DFS with heuristics) may be more efficient.
    *  Summary:
    *   - The approach balances brute-force exploration with pruning techniques.
    *   - Alternative strategies like sorting, memoization, and greedy methods help improve performance.
    */
    double min_expenses;
    // the distance from the origin to the destination
    double journey;
    // the gallon capacity of the automobile’s fuel tank
    double capacity;
    // the miles per gallon that the automobile can travel
    double fuel_consumption;
    // the cost in dollars of filling the automobiles tank in the origination city
    double gas_price;
    // The integer (less than 51) is the number of gasoline stations along the route
    int N;
    /** idx - of the current station we are at
     *  fuel = amount of fuel the car has at the current station 
     * */
    void backtrack(const vpdd& stations, int idx, double total, double fuel, double dist_so_far)
    {
        if(idx == stations.size())
        {
            dd last = journey - dist_so_far;
            if(fuel >= last / fuel_consumption)
            {  min_expenses = std::min(min_expenses, total); }
            return;
        }

        // dist to next point
        dd dist = stations[idx].first - dist_so_far;
        dd price = stations[idx].second;

        // the car cannot make to next station thereby 
        // we are forced to retreat to the previous station and top up the tank 
        if(fuel * fuel_consumption < dist) return;
        fuel -= dist / fuel_consumption;

        // this branch is hit whenever the car lacks the fuel to go on journey
        if(fuel <= capacity / 2)
        {
            dd exp = 2 + std::round((capacity - fuel) * price) / 100;
            backtrack(stations, idx + 1, total + exp, capacity, stations[idx].first); // to next station
        }

        backtrack(stations, idx + 1, total, fuel, stations[idx].first);

    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
       
        int s = 1;
        while(true)
        {
            scanf("%lf\n", &journey);
            if((int)journey == -1) break;

            scanf("%lf %lf %lf %d\n", &capacity, &fuel_consumption, &gas_price, &N);
            vpdd stations(N);
            for(int i = 0; i < N; i++)
            {
                double d, p;
                scanf("%lf %lf\n", &d, &p);
                stations[i] = {d, p};
            }

            min_expenses = std::numeric_limits<double>::infinity();
            backtrack(stations, 0, gas_price, capacity, 0);
            printf("Data Set #%d\nminimum cost = $%0.2f\n", s++, min_expenses);
        }
    }
}