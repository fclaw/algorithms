/*
───────────────────────────────────────────────────────────────
🧳 UVa 264 Count on Cantor, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ii = std::pair<int, int>;

namespace algorithms::onlinejudge::maths::count_on_cantor
{
    /** https://onlinejudge.org/external/2/264.pdf */
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
         
        int term;
        while(scanf("%d", &term) == 1) {
         
           ii start = {1, 1};
           int diagonal_length = 1;
           int curr_term = 1;
           while(curr_term < term) {
            // move right
            start.second += 1;
            curr_term++;
            if(curr_term == term) goto finish;

            // move down along the diagonal
            for(int i = 1; i <= diagonal_length; ++i) {
              if(curr_term == term) goto finish;
              start.first += 1;
              start.second -= 1;
              curr_term++;
            }

            diagonal_length++;
            if(curr_term == term) goto finish;

            // move down
            start.first += 1;
            curr_term++;
            if(curr_term == term) goto finish;

            // move up along the diagonal
            for(int i = 1; i <= diagonal_length; ++i) {
              if(curr_term == term) goto finish;
              start.first -= 1;
              start.second += 1;
              curr_term++;
            }

            diagonal_length++;
            if(curr_term == term) goto finish;
           }

           finish:
           printf("TERM %d IS %d/%d\n", term, start.first, start.second);
        }
    }
}