/*
───────────────────────────────────────────────────────────────
🧳 UVa 11878 Homework Checker, https://onlinejudge.org/external/118/11878.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


std::unordered_map<char, std::function<double(double, double)>> op_map =
  {{'+', std::plus<double>()}, 
   {'-', std::minus<double>()}};


namespace algorithms::onlinejudge::strings::homework_checker
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

        int correct_answers = 0;
        std::string exp;
        while(std::getline(std::cin, exp)) {
          std::stringstream ss(exp);
          int x, y;
          ss >> x;
          char op;
          ss >> op;
          ss >> y;
          char _eq;
          ss >> _eq;
          std::string ans;
          ss >> ans;
          if(ans != "?") {
            if(op_map.at(op)(x, y) == std::stoi(ans)) 
              correct_answers++;
          }
        }
        printf("%d\n", correct_answers);
    }
}