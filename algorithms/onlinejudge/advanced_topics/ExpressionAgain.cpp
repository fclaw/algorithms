/*
───────────────────────────────────────────────────────────────
🧳 UVa 10690 Expression Again, https://onlinejudge.org/external/106/10690.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int OFFSET = 2500;

using vi = std::vector<int>;
using vb = std::vector<bool>;
using vvb = std::vector<vb>;
using vvvb = std::vector<vvb>;
using ii = std::pair<int, int>;

void dp(int idx, int used, int val, int N, const vi& nums, std::unordered_set<int>& vals, vvvb& visited) {

   if(used == N) {
     vals.insert(val);
     return;
   }

   if(idx == (int)nums.size() || visited[idx][used][val + OFFSET]) {
      return;
    }

   visited[idx][used][val + OFFSET] = true;
   // take
   int new_val = val + nums[idx];
   dp(idx + 1, used + 1, new_val, N, nums, vals, visited);
   // skip
   dp(idx + 1, used, val, N, nums, vals, visited);
}


ii get_min_max_products(int n, int m, const vi& nums) {

  int limit = std::accumulate(nums.begin(), nums.end(), 0, [](int sum, int val) {return sum + std::abs(val);});
  int sum = std::accumulate(nums.begin(), nums.end(), 0);
  int target_k = std::min(n, m); // Slashes search depth up to 50x!
  std::unordered_set<int> vals;
  vvvb visited(nums.size() + 1, vvb(target_k + 1, vb(limit + OFFSET + 1, false)));
  dp(0, 0, 0, target_k, nums, vals, visited);

  int min_product = INT32_MAX;
  int max_product = INT32_MIN;
  for(int x : vals) {
    int y = sum - x;
    min_product = std::min(min_product, y * x);
    max_product = std::max(max_product, y * x);
  }

  return {min_product, max_product};
}


namespace algorithms::onlinejudge::advanced_topics::expression_again
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

        int n, m;
        while(std::cin >> n >> m) {
          vi nums(n + m);
          for(int i = 0; i < n + m; ++i) {
            std::cin >> nums[i];
          }
          ii min_max = get_min_max_products(n, m, nums);
          printf("%d %d\n", min_max.second, min_max.first);
        }
    }
}