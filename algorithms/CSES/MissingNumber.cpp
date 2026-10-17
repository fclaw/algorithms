/*
───────────────────────────────────────────────────────────────
🧳 Missing Number, https://cses.fi/problemset/task/1083, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../onlinejudge/debug.h"
#include "../aux.h"
#include <bits/stdc++.h>

using ll = long long;


namespace algorithms::cses::missing_number
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

        int N;
        while(stdin_read(N)) {
          vi nums(N - 1);
          for(int i = 0; i < N - 1; ++i) {
            stdin_read(nums[i]);
          }
          std::sort(nums.begin(), nums.end());
          int missing_num = N; // Default to N if 1 .. N-1 are all in place
          for (int i = 0; i < N - 1; ++i) {
            if(nums[i] != i + 1) {
              missing_num = i + 1;
              break;
            }
          }
        }
    }
}
