#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>



typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<bool> vb;


namespace algorithms::onlinejudge::complete_search::firetruck
{
    /** https://onlinejudge.org/external/2/208.pdf, backtracking with some pruning
     * Pruning Strategy: Detect and Eliminate Redundant or Cyclic Paths
     * Goal: Avoid exploring nodes during forward DFS from node 1 that can reach the TARGET
     * only by routing back through node 1 — which would either form a cycle or cause redundant work.
     * Approach:
     * 1. Build a reverse graph if needed (edges reversed).
     * 2. From the TARGET node, perform a reverse DFS to mark all nodes that can reach the target
     * without traversing through node 1.
     * 3. In the forward DFS from node 1, prune any node v if:
     * canReachTarget[v] == false
     * Meaning: the only way for v to reach the target is by cycling back through node 1,
     * which we disallow or deem inefficient.
     * Benefit:
     * This avoids revisiting subgraphs that are doomed to fail or repeat earlier work,
     * significantly improving the efficiency of the backtracking search.
     */
    vvi paths;
    int TARGET, SOURCE = 0, MAX = 21, CASE = 1;
    /*
    ==================== Reverse Reachability Pruning (RRP) ====================

    Purpose:
        Preemptively eliminate nodes that cannot contribute to valid paths 
        from the source to the target. This reduces the search space before
        the main DFS/backtracking begins.

    Strategy:
        - Perform a reverse DFS starting from the target node.
        - Mark all nodes that can reach the target *without passing through* the source.
        - Skip the source node during this traversal.
        - Any node not marked is only able to reach the target via the source,
        and can safely be excluded from further consideration.

    Use Case:
        Particularly useful in dense or unordered graphs with many paths or cycles.
        Avoids redundant computation by pruning unproductive branches early.

    Implementation Note:
        - Run reverse DFS and mark reachable nodes in a `reachable[]` array.
        - In your main DFS/backtrack, skip any node where `reachable[node] == false`.

    Effect:
        This serves as a preprocessing step — similar in spirit to precomputations 
        in problems like N-Queens — and greatly reduces runtime for hard problems.

    ===========================================================================
    */
    void prune(int u, const vvi& graph, vb& reachable, int avoid)
    {
        for (int v : graph[u]) 
        {
          if (v == avoid || 
              reachable[v])
            continue;
           reachable[v] = true;
           prune(v, graph, reachable, avoid);
        }
    }
    void backtrack(const vvi& graph, int u, int mask, vi& path, const vb& reachable)
    {
        if(u == TARGET)
        { paths.push_back(path); return; }

        for(int v : graph[u])
        {
            // basic pruning && check reachability
            if((mask & (1 << v)) || 
                !reachable[v])
              continue;
            path.push_back(v);
            backtrack(graph, v, mask | (1 << v), path, reachable);
            path.pop_back();
        }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        while(std::cin >> TARGET)
        {
            paths = {};
            --TARGET;
            vvi graph(MAX);
            int from, to;
            while(std::cin >> from >> to 
                  && from && to)
            {
                --from; --to;
                graph[from].push_back(to);
                graph[to].push_back(from);
            }
            for(auto& ps : graph)
              std::sort(ps.begin(), ps.end());
            vi path = {SOURCE};
            vb reachable(MAX, false);
            reachable[TARGET] = true;
            prune(TARGET, graph, reachable, SOURCE);
            backtrack(graph, SOURCE, 0 | (1 << SOURCE), path, reachable);
            printf("CASE %d:\n", CASE++);
            for(auto ps : paths)
            {
                std::string res = 
                  std::accumulate(
                    ps.begin(), 
                    ps.end(),
                    std::string(), 
                    [](std::string& s, int n) 
                    { return s + (s.empty() ? "" : " ") + std::to_string(n + 1); });
                std::cout << res << std::endl;
            }
            printf("There are %d routes from the firestation to streetcorner %d.\n", (int)paths.size(), TARGET + 1);
        }
    }
}