/*
───────────────────────────────────────────────────────────────
🧳 UVa 11451 Water Restrictions, https://onlinejudge.org/external/114/11451.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 


using vi = std::vector<int>;


int LENGTH, S, MAX_FLOW;

struct Sprinkle 
{
    int loc;
    int max_flow;
};

// Creates a mask where bits from l to r (inclusive) are set to 1
inline int get_range_mask(int l, int r) {
  int length = r - l + 1; // Number of consecutive 1s
  return ((1 << length) - 1) << l;
}


void backtrack(int i, int irrigated_land_so_far, int curr_flow, const std::vector<Sprinkle>& sprinkles, int& max_irrigated_land) {

  // base case
  if(i == S) {
    if(curr_flow <= MAX_FLOW) {
      if(__builtin_popcount(irrigated_land_so_far) > max_irrigated_land) {
        max_irrigated_land = __builtin_popcount(irrigated_land_so_far);
       }
    }
    return;
  }

  // pruning
  if(curr_flow > MAX_FLOW) {
    return;
  }

  Sprinkle sprinkle = sprinkles[i];

  for(int flow = 0; flow <= sprinkle.max_flow; ++flow) {
    int l = std::max(1, sprinkle.loc - flow);
    int r = std::min(LENGTH, sprinkle.loc + flow);
    int i_irrigated_land = get_range_mask(l, r);
    if(flow == 0) {
      i_irrigated_land = 0;
    }
    backtrack(i + 1, irrigated_land_so_far | i_irrigated_land, curr_flow + flow, sprinkles, max_irrigated_land);
  }

}



int get_max_irrigated_land(const std::vector<Sprinkle>& sprinkles) {
  int max_irrigated_land = 0;
  backtrack(0, 0, 0, sprinkles, max_irrigated_land);
  return max_irrigated_land;
}


namespace algorithms::onlinejudge::advanced_topics::water_restrictions
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
          std::cin >> LENGTH >> S;
          std::vector<Sprinkle> sprinkle(S);
          for(int i = 0; i < S; ++i) {
            std::cin >> sprinkle[i].loc;
          }
          std::cin >> MAX_FLOW;
          for(int i = 0; i < S; ++i) {
            std::cin >> sprinkle[i].max_flow;
          }
          printf("%d\n", get_max_irrigated_land(sprinkle));
        }
    }
}
