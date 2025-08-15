/*
───────────────────────────────────────────────────────────────
🧳 UVa 616 Coconuts, Revisited, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



bool try_division(int coconuts, int people) {
  int left = coconuts;
  for(int i = 0; i < people; ++i) {
    if((left % people) != 1) return false;
    left -= (left / people); // subtract person's share
    --left; // hand 1 coconut over to a monkey
  }
  return (left % people) == 0; // final division among all people must leave no spare coconut
}


namespace algorithms::onlinejudge::maths::coconuts
{
    /** https://onlinejudge.org/external/6/616.pdf */
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
        
        int coconuts;
        while(scanf("%d", &coconuts) == 1 && 
              coconuts >= 0) {
          int people_found = -1;
          int upper_b = std::sqrt(coconuts) + 1;
          for(int people = 1; people <= upper_b; ++people) {
            bool can_divided = try_division(coconuts, people);
            if(can_divided) { people_found = std::max(people_found, people); }
          }

          if(people_found == -1) printf("%d coconuts, no solution\n", coconuts);
          else printf("%d coconuts, %d people and 1 monkey\n", coconuts, people_found);
        }
    }
}