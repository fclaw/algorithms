 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 12186 Another Crisis, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>
#include <set>


using vi = std::vector<int>;
using vvi = std::vector<vi>;

struct Petition
{
    int boss;
    int workers;
    bool operator < (const Petition& other) const {
      return workers < other.workers || 
            (workers == other.workers && 
             boss < other.boss);
    }
};

int min_workers_needed(int boss, const vvi& hierarchy, const std::unordered_map<int, int>& threshold) 
{
    bool is_boss = false;
    std::vector<Petition> petitions;
    for(int subordinate : hierarchy[boss]) {
      is_boss = true; // If there are children, this node is a boss
      // Recursively calculate the number of workers needed in the child subtree
      int workers = min_workers_needed(subordinate, hierarchy, threshold);
      petitions.push_back({subordinate, workers});
    }

    // If the current node is a boss, how min workers are needed to meet the threshold?
    if(is_boss) {
      std::sort(petitions.begin(), petitions.end());
      int required_petitions = threshold.at(boss);
      int total_workers = 0;
      for (int i = 0; i < required_petitions; ++i) {
        total_workers += petitions[i].workers;
      }
      return total_workers;
    } else return 1; // If it's not a boss, it needs at least one worker
}


namespace algorithms::onlinejudge::graph::petitions
{
    /** https://onlinejudge.org/external/121/12186.pdf */
    int n, t;
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
        
        while(while_read(n, t)) {
          if(!n && !t) break;
          int boss;
          std::unordered_map<int, int> threshold;
          vvi hierarchy(n + 1);
          for(int e = 1; e <= n; ++e) {
            while_read(boss);
            threshold[boss]++;
            hierarchy[boss].push_back(e);
          }
          for(auto& p : threshold) {
            p.second = std::ceil(p.second * t / 100.0);
          }
          std::cout << min_workers_needed(0, hierarchy, threshold) << std::endl;
        }
    }
}