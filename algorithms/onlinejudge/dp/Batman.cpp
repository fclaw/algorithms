/*
───────────────────────────────────────────────────────────────
🧳 UVa 11514 Batman, https://onlinejudge.org/external/115/11514.pdf, bottom-up: 1.970, top-down: 0.790, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>
 


using vi = std::vector<int>;
using vvi = std::vector<vi>;


struct Power
{
    std::string name;
    int attack_factor;
    int energy;

};

// Overloading operator>> for single-word names
std::istream& operator >> (std::istream& is, Power& p) {
  return (is >> p.name >> p.attack_factor >> p.energy);
}

using v_power = std::vector<Power>;

struct Villain
{
    std::string name;
    int defense_factor;
    std::vector<std::string> ps;
};


using v_villain = std::vector<Villain>;


std::vector<std::string> split_by_comma(const std::string& s) {
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string word;
    
  // Read from the stringstream until the comma delimiter is hit
  while (std::getline(ss, word, ',')) {
    result.push_back(word);
  }
    
  return result;
}

int cache[1001][1001];

/**
 * why we choose the Minimization Approach over the Feasibility Approach:
 *
 * 1. The Feasibility Formulation (The Naive Way):
 *    Initially, one might define a DP state like:
 *       bool can_defeat(int i, int j, int remaining_energy)
 *    This state checks if we can defeat the remaining villains from index 'j' 
 *    using a subset of powers from index 'i' given a specific 'remaining_energy'.
 *
 *    The state dimensions would be:
 *       State Space = P * V * E
 *    Given the problem constraints:
 *       P <= 1000, V <= 1000, E <= 10^8
 *    This would require a 3D table of size:
 *       1000 * 1000 * 10^8 = 10^14 states!
 *    This size makes a feasibility DP completely impossible, resulting in immediate 
 *    Memory Limit Exceeded (MLE) and Time Limit Exceeded (TLE) errors.
 *
 * 2. The Inversion Trick (The Minimization Way):
 *    Instead of passing the energy as a parameter to check feasibility, we invert 
 *    the question: 
 *       "What is the absolute minimum energy required to defeat all the villains?"
 *
 *    By making the energy cost the RETURN VALUE of the DP rather than a STATE PARAMETER,
 *    we completely eliminate 'E' from the state dimension.
 *
 *    The new state dimensions are simply:
 *       State Space = P * V
 *    For P, V <= 1000, this requires a 2D table of size:
 *       1000 * 1000 = 10^6 states.
 *    At 4 bytes per integer, a 10^6 table consumes only ~4MB of memory, fitting 
 *    comfortably inside any standard competitive programming memory limit (typically 128MB+),
 *    and executes in milliseconds.
 *
 * 3. The Final Comparison:
 *    After the DP completes and returns the minimum energy required to defeat all 
 *    villains, we simply compare this result against Batman's budget 'E' in O(1) time:
 *       min_energy <= E ? "Yes" : "No"
 */
int min_energy_to_beat_all_villains(int i, int j, const v_power& powers, const v_villain& villains) {
  int P = (int)powers.size();
  int V = (int)villains.size();

  // Base Case 1: All villains defeated successfully
  if (j == V) {
    return (cache[i][j] = 0);
  }

  // Base Case 2: Out of powers, but villains remain
  if(i == P) {
    return (cache[i][j] = INT32_MAX);
   }

  if(~cache[i][j]) {
    return cache[i][j];
  }

  // Choice 1: Skip the current power
  int min_energy = min_energy_to_beat_all_villains(i + 1, j, powers, villains);

  for(auto& power : villains[j].ps) {
    if(power == powers[i].name && 
       powers[i].attack_factor >= 
       villains[j].defense_factor) {
      int next_energy = min_energy_to_beat_all_villains(i + 1, j + 1, powers, villains);
      if(next_energy != INT32_MAX) {
        min_energy = std::min(min_energy, powers[i].energy + next_energy);
      }
    }
  }
  return (cache[i][j] = min_energy);
}


namespace algorithms::onlinejudge::dp::batman
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

        int P, V, E;
        while(std::cin >> P >> V >> E
              && P && V && E) {
          v_power powers(P);
          for(int i = 0; i < P; ++i) {
            std::cin >> powers[i];
          }

          std::cin.ignore();
          std::string input;
          v_villain villains(V);
          for(int i = 0; i < V; ++i) {
            Villain villain;
            std::getline(std::cin, input);
            std::stringstream ss(input);
            ss >> villain.name >> villain.defense_factor;
            std::string power_names;
            ss >> power_names;
            for(auto& pn : split_by_comma(power_names)) {
              villain.ps.push_back(pn);
            }
            villains[i] = villain;
          }

          //   std::memset(cache, -1, sizeof cache);
          //   int min_energy = min_energy_to_beat_all_villains(0, 0, powers, villains);

          vvi dp(P + 1, vi(V + 1, INT32_MAX));
          for(int i = 0; i <= P; ++i) {
            dp[i][0] = 0;
          }

          for(int i = 1; i <= P; ++i) {
            for(int j = 1; j <= V; ++j) {
              int skip = dp[i - 1][j];
              int take = INT32_MAX;
              for(auto& power : villains[j - 1].ps) {
                if(power == powers[i - 1].name && 
                   powers[i - 1].attack_factor >= 
                   villains[j - 1].defense_factor) {
                   int prev = dp[i - 1][j - 1];
                  // if reachable
                  if(prev != INT32_MAX) {
                    take = std::min(take, powers[i - 1].energy + prev);
                  }
                }
              }
              dp[i][j] = std::min(dp[i][j], std::min(skip, take));
            }
          }
          printf("%s\n", dp[P][V] <= E ? "Yes" : "No");
        }
     }
}