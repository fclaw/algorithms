/*
───────────────────────────────────────────────────────────────
🧳 UVa 711 Dividing up, https://onlinejudge.org/external/7/711.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ii = std::pair<int, int>;
using vpii = std::vector<std::pair<int, int>>;



const int N = 6;

bool is_feasible(vpii& marbles, int curr_value, int target) {
  return false;
}


namespace algorithms::onlinejudge::complete_search::dividing_up
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

        bool is_go;
        int collection = 1;
        do {
          is_go = false;  
          vpii marbles;
          int total_value = 0;
          int c;
          for(int v = 1; v <= N; ++v) {
            std::cin >> c;
            marbles.push_back({v, c});
            total_value += v * c;
            is_go |= (c != 0);
          }

          if(is_go) {
            if((total_value % 2)) {
              printf("Collection #%d:\nCan't be divided.\n\n", collection++);
            } else {
              int target = total_value / 2;
              bool res = is_feasible(marbles, 0, target);
              printf("Collection #%d:\n%s\n\n", collection++, (res ? "Can be divided." : "Can't be divided."));
            }
          }
        } while(is_go);
    }
}