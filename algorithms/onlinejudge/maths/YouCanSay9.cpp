/*
───────────────────────────────────────────────────────────────
🧳 UVa 10922 2 the 9s, https://onlinejudge.org/external/109/10922.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




bool isDivisibleBy9(const std::string& numStr) {
  int digitSum = 0;
  for(char c : numStr) {
    digitSum += (c - '0'); // Convert char to int and add to sum
  }
  return digitSum % 9 == 0;
}

int degree_9(const std::string& numStr) {
  if(numStr.size() == 1) return 0; // Single digit numbers
  int new_num = 0;
  for(char c : numStr) {
    new_num += (c - '0'); // Convert char to int and add to sum
  }
  return 1 + degree_9(std::to_string(new_num));
}


namespace algorithms::onlinejudge::maths::you_can_say_9
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

        std::string numStr;
        while(std::cin >> numStr && numStr != "0") {
          if(isDivisibleBy9(numStr)) {
            int deg = numStr.size() > 1 ? degree_9(numStr) : 1;
            printf("%s is a multiple of 9 and has 9-degree %d.\n", numStr.c_str(), deg);
          } else {
            printf("%s is not a multiple of 9.\n", numStr.c_str());
          }
        }
    }
}