/*
───────────────────────────────────────────────────────────────
🧳 UVa 12950 Even Obsession, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/w_graph.cpp"

#include <optional>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>



namespace wg = algorithms::onlinejudge::graph::tools::wg;

constexpr int inf = 1e5;


enum Parity { Even, Odd };

// a helper function to flip the parity
Parity flip(Parity p) { return (p == Parity::Even) ? Parity::Odd : Parity::Even; }

struct State
{
    int city;
    Parity parity; // arrival in city can be made either through even number of roads or odd ones
    int toll;
    // for priority queue
    bool operator < (const State& other) const { return toll > other.toll; }
};



namespace algorithms::onlinejudge::graph::even_obsession
{
    /** https://onlinejudge.org/external/129/12950.pdf */
    int V, E;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        while(while_read(V, E)) {
          int source = 0, sink = V - 1;
          wg::WGraph<> graph(V);
          for(int e = 0; e <  E; ++e) {
            int u, v, toll;
            while_read(u, v, toll);
            --u; --v;
            wg::pair(graph, u, v, toll);
          }

          std::vector<std::array<int, 2>> states(V, {inf, inf});
          std::priority_queue<State> queue;

          states[source][Even] = 0;
          queue.push({source, Even, 0});
          while(!queue.empty()) {
            State state = queue.top(); queue.pop();
            int curr_city = state.city;
            Parity curr_parity = state.parity;
            int curr_toll = state.toll;

             // >>> ESSENTIAL DIJKSTRA'S CHECK <<<
            if(curr_toll > states[curr_city][curr_parity]) continue;

            for(const wg::WNode<>& node : graph[curr_city]) {
              int next_city = node.node;
              int next_toll = node.weight + curr_toll;
              Parity next_parity = flip(curr_parity);
              if(states[next_city][next_parity] > next_toll) {
                states[next_city][next_parity] = next_toll;
                queue.push({next_city, next_parity, next_toll});
              }
            }
          }

          int min_toll_paid = states[sink][Even];
          std::cout << (min_toll_paid != inf ? min_toll_paid : -1) << std::endl;
        }
    }
}