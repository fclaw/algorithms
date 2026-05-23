/*
───────────────────────────────────────────────────────────────
🧳 UVa 10800 Not That Kind of Graph, https://onlinejudge.org/external/108/10800.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



struct Point {
  int x, y;
  char type;
};

using vs = std::vector<std::string>;
using vp = std::vector<Point>;



std::pair<vp, int> fillChartArray(std::string& fluctuations) {
  vp points;
  int curr_y = 0, min_y = 0, max_y = 0;

   for (int x = 0; x < (int)fluctuations.length(); ++x) {
     char move = fluctuations[x];
     if (move == 'R') {
       points.push_back({x, curr_y, '/'});
       curr_y++;
       max_y = std::max(max_y, curr_y);
     } else if (move == 'F') {
        curr_y--;
        points.push_back({x, curr_y, '\\'});
        min_y = std::min(min_y, curr_y);
     } else { // 'C'
       points.push_back({x, curr_y, '_'});
         max_y = std::max(max_y, curr_y + 1);
         min_y = std::min(min_y, curr_y + 1);
     }
  }

  // THE "FIX-UP": Now that we know min_y, adjust all points to be positive
  int vertical_offset = std::abs(min_y);
  for (auto& p : points) {
    p.y += vertical_offset;
    p.x += 2;
  }
  max_y += vertical_offset;

  return {points, max_y};
}


namespace algorithms::onlinejudge::strings::stock_chart
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
        int t_case = 1;
        scanf("%d", &t_cases);
        while(t_cases--) {
          
          std::string fluctuations;
          std::cin >> fluctuations;

          auto [fluctuations_points, max_y] = fillChartArray(fluctuations);
           
          int total_rows = max_y;
          int total_cols = fluctuations.length();
          std::vector<std::string> grid(total_rows + 1, std::string(total_cols + 2, ' '));
    
          for (const auto& p : fluctuations_points) {
            grid[p.y][p.x] = p.type;
          }

          // add y-axis
          for(int i = 0; i < total_rows; i++) {
            grid[i][0] = '|';
          }

          printf("Case #%d:\n", t_case++);

          // print grid
          for(int j = max_y - 1; j >= 0; j--) {
            size_t last_char_pos = grid[j].find_last_not_of(' ');
            std::cout << grid[j].substr(0, last_char_pos + 1) << "\n";
          }

          // add x-axis
          printf("+");
          for(int i = 1; i < total_cols + 3; i++) {
            printf("-");
          }
          printf("\n\n");
        }
    }
}