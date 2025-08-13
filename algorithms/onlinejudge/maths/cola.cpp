/*
───────────────────────────────────────────────────────────────
🧳 UVa 11150 Cola, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int EXCHANGE_RATE = 3;


bool try_borrow(int& bottles, int borrowed) {
  int newly_borrowed = EXCHANGE_RATE - bottles % EXCHANGE_RATE;
  return ((bottles + newly_borrowed) / EXCHANGE_RATE >= newly_borrowed + borrowed);
}


namespace algorithms::onlinejudge::maths::cola
{
    /** https://onlinejudge.org/external/111/11150.pdf */
    int bottles;
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
        
        while(while_read(bottles)) {
          int consumed = 0;
          int borrowed = 0;
          while(bottles > 1) {
            consumed += bottles;
            bottles -= borrowed;
            borrowed = 0;
            if((bottles % EXCHANGE_RATE) &&
                try_borrow(bottles, borrowed)) {
              int newly_borrowed = EXCHANGE_RATE - bottles % EXCHANGE_RATE;
              borrowed += newly_borrowed;
              bottles = (bottles + newly_borrowed) / EXCHANGE_RATE;
            } else { bottles /= EXCHANGE_RATE; }
          }
          std::cout << (consumed + bottles) << std::endl;
        }
    }
}