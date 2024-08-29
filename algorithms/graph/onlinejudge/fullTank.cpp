#include <vector>

namespace algorithms::graph::onlinejudge::full_tank
{

using graph = std::vector<std::tuple<int, int, int>>;
using fuelPrice = std::vector<int>; 


     /** 
      *  https://onlinejudge.org/external/113/11367.pdf
      * Abridged problem description: Given a connected weighted graph length 
      * that stores the road length between E pairs of cities i and j (1 ≤ V ≤ 1000, 0 ≤ E ≤ 10000), 
      * the price p[i] of fuel at each city i, and the fuel tank capacity c of a car (1 ≤ c ≤ 100), 
      * determine the cheapest trip cost from starting city s to ending city e using a car with fuel capacity c. 
      * All cars use one unit of fuel per unit of distance and start with an empty fuel tank.
      * With this problem, we want to discuss the importance of graph modeling. 
      * The explicitly given graph in this problem is a weighted graph of the road network. 
      * However, we cannot solve this problem with just this graph. 
      * This is because the state of this problem requires not just the current location (city) 
      * but also the fuel level at that location. 
      * Otherwise, we cannot determine whether the car has enough fuel to make a trip along a certain road 
      * (because we cannot refuel in the middle of the road). 
      * Therefore, we use a pair of information to represent the state: (location, fuel) 
      * and by doing so, the total number of vertices of the modified graph explodes 
      * from just 1000 vertices to 1000 × 100 = 100000 vertices. We call the modified graph: ‘State-Space’ graph.
      * In the State-Space graph, the source vertex is state (s, 0)—at starting city s with empty fuel tank 
      * and the target vertices are states (e, any)—at ending city e with any level of fuel between [0..c]. 
      * There are two types of edge in the State-Space graph: 0-weighted edge 
      * that goes from vertex (x, fuel(x)) to vertex (y, fuel(x) − length(x, y)) 
      * if the car has sufficient fuel to travel from vertex x to vertex y, 
      * and the p[x]-weighted edge that goes from vertex (x,fuel(x)) to vertex 
      * (x, fuel(x) + 1) if the car can refuel at vertex x by one unit of fuel 
      * (note that the fuel level cannot exceed the fuel tank capacity c). 
      * Now, running Dijkstra’s on this State-Space graph gives us the solution for this problem */
     int cheapestTrip(const graph& g, const fuelPrice& ps, int capacity, int source, int sink)
     {
        return 1;
     }
}
