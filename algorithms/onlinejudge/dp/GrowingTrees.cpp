/*
───────────────────────────────────────────────────────────────
🧳 UVa 13141 Growing Trees, https://onlinejudge.org/external/131/13141.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


enum Branch_Status { INIT, NO_BRANCH, BRANCH};

using ll = long long;

ll memo[86][3];



ll count_leaves(int height, int curr_level, Branch_Status status) {

  if(curr_level == height) {
    return 1;
  }

  if(~memo[curr_level][status]) {
    return memo[curr_level][status];
  }

  ll count = 0;
  if(status == INIT) {
    count += count_leaves(height, curr_level + 1, NO_BRANCH);
  } else if (status == NO_BRANCH){
    count += count_leaves(height, curr_level + 1, BRANCH);
  } else {
    ll left = count_leaves(height, curr_level + 1, BRANCH);
    ll right = count_leaves(height, curr_level + 1, NO_BRANCH);
    count += left + right;
  }

  return memo[curr_level][status] = count;
}



namespace algorithms::onlinejudge::dp::growing_trees
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

        int level_of_growth;
        while(std::cin >> level_of_growth && level_of_growth) {
          std::memset(memo, -1, sizeof memo);
          std::cout << count_leaves(level_of_growth, 0, INIT) << std::endl;
        }

    }
}