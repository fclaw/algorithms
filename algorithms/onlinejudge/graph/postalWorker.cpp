 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 117 The Postal Worker Rings Once, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include <numeric>
#include <bits/stdc++.h>


const std::string stop = "deadend";
constexpr int MAX_LETTER = 26;


struct Degree 
{
    int in;
    int out;
};

struct Street
{
    int from;
    int to;
    int length;
};


using vi = std::vector<int>;
using vvi = std::vector<vi>;
using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vvii = std::vector<vii>;
using map_ci = std::unordered_map<char, int>;
using map_degree = std::unordered_map<int, Degree>;
using v_street = std::vector<Street>;
using PQ = std::priority_queue<ii, std::vector<ii>, std::greater<ii>>;



int do_dijkstra(const vvii& graph, const vi& odd_degree_points) {

  if(odd_degree_points.empty()) return 0;

  int source = odd_degree_points.front();
  int target = odd_degree_points.back();

  vi dist(MAX_LETTER, INT32_MAX);
  PQ queue;
  queue.push({source, 0});
  dist[source] = 0;
  while(!queue.empty()) {
    ii p = queue.top(); queue.pop();
    int u = p.first;
    int d = p.second;
    if(d > dist[u]) continue; // lazy deletion
    if(u == target) return d;
    for(const ii& neigh : graph[u]) {
      int v = neigh.first;
      int w = neigh.second;
      if(dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        queue.push({v, dist[v]});
      }
    }
  }
  return 0;
}


void do_delivery_round(const v_street& streets, const map_degree& degrees) {

  int sum_of_all_roads = 0;
  for(auto& s : streets) {
    sum_of_all_roads += s.length;
  }

  vvii graph(MAX_LETTER);
  for(const Street& street : streets) {
    int from = street.from;
    int to = street.to;
    int l = street.length;
    graph[from].push_back({to, l});
    graph[to].push_back({from, l});
  }

  vi odd_degree_points;
  for(int i = 0; i < MAX_LETTER; ++i) {
    auto it = degrees.find(i);
    if(it == degrees.end()) continue;
    int in = degrees.at(i).in;
    int out = degrees.at(i).out;
    if(((in + out) % 2)) 
      odd_degree_points.push_back(i);
  }

  int last_leg_dist = do_dijkstra(graph, odd_degree_points);

  std::cout << sum_of_all_roads + last_leg_dist << std::endl;
}


namespace algorithms::onlinejudge::graph::postal_worker
{
    /** https://onlinejudge.org/external/1/117.pdf  */
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
        
        std::string str;
        int idx = 0;
        v_street streets;
        map_degree degrees;
        map_ci streets_to_idx;
        while(while_read(str)) {
          if(str == stop) {
            do_delivery_round(streets, degrees);
            idx = 0;
            degrees.clear();
            streets_to_idx.clear();
            streets.clear();
          } else {
            Street street;
            street.length = (int)str.size();
            char start = str.front();
            char end = str.back();
            if(auto it = streets_to_idx.find(start); 
               it == streets_to_idx.end()) {
              streets_to_idx[start] = idx++;
              street.from = streets_to_idx.at(start);
            } else { street.from = it->second; }
            
            if(auto it = streets_to_idx.find(end); 
               it == streets_to_idx.end()) {
              streets_to_idx[end] = idx++;
              street.to = streets_to_idx.at(end);
            } else { street.to = it->second; }

            degrees[street.from].out++;
            degrees[street.to].in++;

            streets.push_back(street);
          }
        }  
    }
}