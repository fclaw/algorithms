/*
───────────────────────────────────────────────────────────────
🧳 10604 Chemical Reaction, https://onlinejudge.org/external/106/10604.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;



// Represents the result of mixing chemical i and chemical j
struct Reaction {
    int result; // The new resulting chemical type (1 to m)
    int heat;   // The amount of energy/heat emitted (can be negative!)
};

using ReactionTable = std::vector<std::vector<Reaction>>;


vi get_alive_tubes(const vi& tubes) {
  vi alive_tubes;
  for (int chemical : tubes) {
    if (chemical) { // Tube is not empty
      alive_tubes.push_back(chemical);
    }
    if(alive_tubes.size() > 2) {
      break;
    }
  }

  return alive_tubes;
}


int dp(const vi& tubes, const ReactionTable& table, std::map<vi, int>& cache) {

  vi alive_tubes = get_alive_tubes(tubes);
  // ✅ Exactly 2 tubes are alive!
  if(alive_tubes.size() == 2) {
    int f = alive_tubes.front();
    int s = alive_tubes.back();
    return cache[tubes] = std::min(table[f][s].heat, table[s][f].heat);
  }
 

  if(auto it = cache.find(tubes); it != cache.end()) {
    return it->second;
  }

  int min_heat = (int)1e9;
  for(int i = 0; i < (int)tubes.size(); ++i) {
    for(int j = 0; j < (int)tubes.size(); ++j) {
      int ci = tubes[i];
      int cj = tubes[j];
      if(i != j && ci && cj) {
        // ==========================================
        // Mix ci into cj -> table[ci][cj]
        // ==========================================
        Reaction ij_r = table[ci][cj];
        vi next_tubes = tubes;
        next_tubes[i] = ij_r.result;
        next_tubes[j] = 0;
        // ====================================================================
        // 🧠 STATE CANONICALIZATION: Sorting in Descending Order (std::greater)
        // ====================================================================
        // 1. COLLAPSING REDUNDANT PERMUTATIONS (Multiset Equivalence):
        //    In the physical lab, the slot order of tubes does NOT matter!
        //    Whether chemicals are scattered across slots as:
        //        [1, 0, 3, 0, 2]  OR  [0, 2, 0, 1, 3]  OR  [3, 2, 1, 0, 0]
        //    they represent the EXACT SAME physical state: {1, 2, 3}.
        //
        //    Without sorting, each slot permutation is treated as a separate 
        //    key in `cache`, destroying memoization and causing an exponential 
        //    state explosion (TLE!).
        //
        // 2. COMPACTING ALIVE TUBES & FLUSHING ZEROS:
        //    By sorting with `std::greater<int>()`:
        //      • All active/alive chemicals are pushed contiguously to the FRONT.
        //      • All dead/empty '0' slots are flushed to the BACK.
        //    Every state containing {1, 2, 3} collapses into the unique key:
        //        [3, 2, 1, 0, 0, 0, 0, 0, 0, 0]
        //
        // 3. CACHE HIT EXPLOSION:
        //    This forces all symmetric paths to hit the exact same memoized entry,
        //    slashing the search space from O(K!) permutations down to a small,
        //    tight DAG.
        // ====================================================================
        std::sort(next_tubes.begin(), next_tubes.end(), std::greater<int>());
        std::sort(next_tubes.begin(), next_tubes.end(), std::greater<int>());
        min_heat = std::min(min_heat, ij_r.heat + dp(next_tubes, table, cache));
      }
    }
  }
  return (cache[tubes] = min_heat);
}


int get_min_heat(int chemicals_n, const ReactionTable& table, vi& tubes) {
  std::map<vi, int> cache;
  std::sort(tubes.begin(), tubes.end());
  return dp(tubes, table, cache);
}



namespace algorithms::onlinejudge::advanced_topics::chemical_reaction
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        int t_cases;
        std::cin >> t_cases;
        while(t_cases--) {
          int chemicals_n;
          std::cin >> chemicals_n;
          // Read the m x m reaction table in row-major order
          // 1-based indexing for m chemicals (m <= 6)
          ReactionTable table(chemicals_n + 1, std::vector<Reaction>(chemicals_n + 1));

          for(int i = 1; i <= chemicals_n; ++i) {
            for(int j = 1; j <= chemicals_n; ++j) {
              std::cin >> table[i][j].result >> table[i][j].heat;
            }
          }
          int tubes_n;
          std::cin >> tubes_n;
          vi tubes(tubes_n);
          for(int i = 0; i < tubes_n; ++i) {
            std::cin >> tubes[i];
          }

          // Consume the delimiter line ('/' between cases, or '.' at EOF)
          std::string delimiter;
          std::cin >> delimiter;
          printf("%d\n", get_min_heat(chemicals_n, table, tubes));
        }
    }
}
