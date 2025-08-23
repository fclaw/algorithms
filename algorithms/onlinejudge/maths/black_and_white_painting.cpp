/*
───────────────────────────────────────────────────────────────
🧳 UVa 11231 Black and white painting, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include <bits/stdc++.h>




// 0-based indexing
constexpr int BOARD_SIZE = 7;

using ll = long long;


namespace algorithms::onlinejudge::maths::black_and_white_painting
{
    /** https://onlinejudge.org/external/112/11231.pdf */
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
         
        int n, m, c;
        while(scanf("%d %d %d", &n, &m, &c) == 3 && n != 0 && m != 0) {
          // the number of boards are counted horizontally, vertically
          // total boards is multiple of them: vertical_boards * horizontal_boards
          // 0-based indexing
          ll boards_n = (ll)((n - BOARD_SIZE) * (m - BOARD_SIZE) + c) / 2;
          printf("%lld\n", boards_n);
        }
    }
}