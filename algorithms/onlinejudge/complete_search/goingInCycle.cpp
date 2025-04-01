#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>



typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<std::pair<int, vi>> vpivi;
typedef std::vector<vpivi> vvpivi;
typedef std::vector<std::vector<bool>> vvb;


namespace algorithms::onlinejudge::complete_search::going_in_cycle
{
    /** https://onlinejudge.org/external/110/11090.pdf, 
     * minimum mean weight cycle problem; solvable with backtracking 
     * with important pruning when current running mean is 
     * greater than the best found mean weight cycle cost */
    double best_mean;
    bool isCycle;
    void backtrack(const vvpivi& graph, int u, ll mask, vvb& visited, vi path, int sw)
    {
        mask |= (1LL << u);
        for(auto& p : graph[u])
        {
            int v = p.first;
            for (int w : p.second) 
            {   // Iterate over all possible edge weights
                vi tmp = path;
                if(!visited[u][v] &&
                   !(mask & (1LL << v)))
                {
                    tmp.push_back(v);
                    double projected_mean = static_cast<double>(sw + w) / (tmp.size() + 1);
                    if(projected_mean >= best_mean)
                      continue;
                    
                    visited[u][v] = true;
                    backtrack(graph, v, mask | (1LL << v), visited, tmp, sw + w);  
                    visited[u][v] = false;
                }
                            
                if((mask & (1LL << v)))
                {
                    if(!isCycle) isCycle = true;
                    // Step 1: Identify cycle start in path
                    auto it = std::find(tmp.begin(), tmp.end(), v);
                    if (it != tmp.end()) 
                    {
                        vi cycle(it, tmp.end()); // Extract only cycle nodes

                        // Step 2: Compute cycle weight
                        int cycle_weight = 0;
                        for (size_t i = 0; i < cycle.size() - 1; i++) 
                        {
                            int u = cycle[i], next_v = cycle[i + 1];
                            int min_w = INT32_MAX;  // Store minimum weight for u → next_v
                            for (auto p : graph[u])
                              if (p.first == next_v)
                                for (int w : p.second)  // Iterate over all parallel weights
                                  min_w = std::min(min_w, w);

                            if (min_w != INT32_MAX)  // Only add if we found a valid edge
                              cycle_weight += min_w;
                        }

                        // Add weight of the last edge closing the cycle
                        cycle_weight += w;
                        // Step 3: Compute mean weight of this cycle
                        int cycle_length = cycle.size();

                        double mean_weight = static_cast<double>(cycle_weight) / cycle_length;
                        // Step 4: Prune if mean_weight is worse than best_mean
                        best_mean = std::min(best_mean, mean_weight);
                    }
                }
            }
        }
    }
    void addEdge(vvpivi& graph, int u, int v, int w) 
    {
        for (auto& p : graph[u])
          if (p.first == v) 
          { p.second.push_back(w); return; }
        graph[u].push_back({v, {w}});  // Create new edge entry
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int TC, c = 1;
        scanf("%d\n", &TC);
        while(TC--)
        {
            best_mean = std::numeric_limits<double>::max();
            isCycle = false;
            int V, E;
            scanf("%d %d\n", &V, &E);
            vvpivi graph(V);
            int u, v, w;
            for(int e = 0; e < E; e++)
            {
                scanf("%d %d %d", &u, &v, &w);
                --u; --v;
                addEdge(graph, u, v, w);
            }
            vvb visited(51, std::vector<bool>(51, false));
            backtrack(graph, 0, 0, visited, {0}, 0.0);

            printf("Case #%d: ", c++);
            !isCycle ? printf("No cycle found.\n") : printf("%0.2lf\n", best_mean);
        }
    }
}