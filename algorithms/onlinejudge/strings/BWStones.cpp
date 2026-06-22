/*
───────────────────────────────────────────────────────────────
🧳 UVa 12855 Black and white stones, https://onlinejudge.org/external/128/12855.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;

char BLACK = 'B';
char WHITE = 'W';

ll get_minimized_penalty(std::string& stones, int left, int right, ll penalty, ll reimbursement) {
  return 0LL;
}


namespace algorithms::onlinejudge::strings::bw_stones
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

        ll penalty, reimbursement;
        std::string stones;
        while(std::cin >> penalty >> reimbursement) {
          std::cin.ignore();  
          std::getline(std::cin, stones);
          std::cout << get_minimized_penalty(stones, 0, stones.size() - 1, penalty, reimbursement) << std::endl;
        }
    }
}