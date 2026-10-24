/*
───────────────────────────────────────────────────────────────
🧳 UVa 957 Popes, https://onlinejudge.org/external/9/957.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"



namespace algorithms::onlinejudge::divide_conquer::popes
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

        int period, n;
        while(stdin_read(period)) {
          stdin_read(n);
          vi years(n);
          for(int i = 0; i < n; ++i) {
            stdin_read(years[i]);
          }

          
          int max_popes_in_office = 0;
          int first_pope, last_pope;

          for(int s = 0; s < n; ++s) {
            int start = years[s];
            int end = start + period;
            auto it = std::lower_bound(years.begin() + s, years.end(), end);
            int popes_in_office = std::distance(years.begin() + s, it);
            if(popes_in_office > max_popes_in_office) {
              max_popes_in_office = popes_in_office;
              first_pope = start;
              last_pope = *(it - 1);
            }
          }

          std::cout << max_popes_in_office << " " << first_pope << " " << last_pope << "\n";
        }

    }
}