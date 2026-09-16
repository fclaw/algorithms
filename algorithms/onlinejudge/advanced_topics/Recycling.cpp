 /*
───────────────────────────────────────────────────────────────
🧳 11523 Recycling, https://onlinejudge.org/external/115/11523.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int INF = (int)1e9;

using vi = std::vector<int>;
using vvi = std::vector<vi>;



int get_thing_id(int& idx, const std::string& name, std::unordered_map<std::string, int>& things_to_id) {
  auto it = things_to_id.find(name);
  if (it != things_to_id.end()) {
    return it->second; // Already exists
  }
  // New city: assign new index and store in vector
  int new_id = idx++;
  things_to_id[name] = new_id;
  return new_id;
}



int cache[110][110];

int dp(int left, int right, const vi& things) {

  if(left > right) {
    return 0;
  }

  if(left == right) {
    return 1;
  }

  if(~cache[left][right]) {
    return cache[left][right];
  }

  int best = 1 + dp(left + 1, right, things);
 
  // int throw_bundle = INF;
  for(int k = left + 1; k <= right; ++k) {
    if(things[k] == things[left]) {
      best = std::min(best, dp(left + 1, k - 1, things) + dp(k, right, things));
    }
  }

  return (cache[left][right] = best);
}


int get_optimal_moves(const vvi& disposable_bundles) {
  int min_moves = 0;
  for(vi bundle : disposable_bundles) {
    std::memset(cache, -1, sizeof cache);
    min_moves += dp(0, (int)bundle.size() - 1, bundle);
  }
  return min_moves;
}


namespace algorithms::onlinejudge::advanced_topics::recycling
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

        int t_cases, t_case = 1;
        std::cin >> t_cases;
        while(t_cases--) {
          int things_n;
          std::cin >> things_n;
          vvi disposable_bundles;
          vi things;
          std::string name;
          std::string prev_thing;
          int idx = 0;
          std::unordered_map<std::string, int> things_to_id;
          for(int i = 0; i < things_n; ++i) {
            std::cin >> name;
            if(prev_thing.empty() ||
               (!prev_thing.empty() && 
                name != prev_thing)) {
               prev_thing = name;
              if(std::isupper(name.front())) {
                if (!things.empty()) { // ✅ Guard against empty bundles!
                  disposable_bundles.push_back(things);
                  things.clear();
                }
                continue;
              }
              int thing_id = get_thing_id(idx, name, things_to_id);
              things.push_back(thing_id);
            }
          }
          if(!things.empty()) {
            disposable_bundles.push_back(things);
          }
          printf("Case %d: %d\n", t_case++, get_optimal_moves(disposable_bundles));
        }
    }
}
