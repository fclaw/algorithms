#pragma once

#include "dfs.cpp"

#include <queue>


namespace algorithms::onlinejudge::graph::tools
{

    struct TopSortKahn
    {
        tools::vi top_sort;
        bool is_cycle;   
    };

    // ---------- Kahn's algorithm for topological sort ----------
    // Step 1: Calculate the In-Degree of Each Node
    // In-degree represents the number of incoming edges to a node, i.e., its dependencies.
    // Initialize an array `in_degree[]` of size V (number of nodes) to zero.
    // Traverse the graph and for each edge u -> v, increment the in-degree of v by 1.

    // Step 2: Initialize the Queue
    // Create an empty queue to store nodes with an in-degree of 0 (i.e., nodes with no dependencies).
    // Traverse the in-degree array and enqueue all nodes with in-degree 0.

    // Step 3: Process the Nodes in the Queue (BFS-like)
    // While the queue is not empty:
    //   1. Remove a node `u` from the front of the queue.
    //   2. Add `u` to the topological order result list.
    //   3. For each adjacent node `v` of `u` (i.e., for each outgoing edge u -> v):
    //      - Decrease the in-degree of `v` by 1 (because we've processed one of its dependencies).
    //      - If the in-degree of `v` becomes 0, enqueue `v` (since it now has no dependencies and can be processed next).

    // Step 4: Cycle Detection
    // After processing all nodes, check if the number of nodes in the topological order matches the total number of nodes in the graph.
    // If the number of nodes in the result is less than the total number of nodes, a cycle exists in the graph.
    // In this case, a topological sort is not possible.

    // Step 5: Output the Topological Sort
    // If no cycle was detected and all nodes were processed, output the topological order.
    // If a cycle was detected (i.e., some nodes were not processed), report that topological sorting is not possible.
    template <typename T = tools::Unit>
    TopSortKahn top_sort_kahn(int V, const tools::Graph<T>& graph)
    {
        tools::vi in_degree(V, 0);
        for(int v = 0; v < V; ++v)
          for(const tools::Node<T>& u : graph[v])
            in_degree[u.node]++;
             
        std::priority_queue<int, std::vector<int>, std::greater<int>> no_degree;
        for(int v = 0; v < V; ++v)
          if(!in_degree[v])
            no_degree.push(v);
            
        tools::vi tops_sort;
        while(!no_degree.empty()) {
          int u = no_degree.top();
          no_degree.pop();
          tops_sort.push_back(u);

          for(const tools::Node<T>& v : graph[u]) {
            in_degree[v.node]--;
            if(!in_degree[v.node])
              no_degree.push(v.node);
          }
        }
        return {tops_sort, (int)tops_sort.size() == V};
    }
}