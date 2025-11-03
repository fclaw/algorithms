/*
───────────────────────────────────────────────────────────────
🧳 UVa 11878 Homework Checker, https://onlinejudge.org/external/118/11878.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr char plus = '+';
constexpr char minus = '-';


std::unordered_map<char, std::function<int(int, int)>> op_map =
  {{plus, std::plus<int>()}, 
   {minus, std::minus<int>()}};


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
          size_t op_pos = exp.find(plus);
          if(op_pos == std::string::npos) {
            op_pos = exp.find(minus);
          }
          
          size_t ans_pos = exp.find('=');

          std::string x_str = exp.substr(0, op_pos);
          std::string y_str = exp.substr(op_pos + 1, ans_pos);
          std::string ans = exp.substr(ans_pos + 1);

          int x = std::stoi(x_str);
          int y = std::stoi(y_str);

          if(ans != "?") {
            if(op_map.at(exp[op_pos])(x, y) == std::stoi(ans)) 
              correct_answers++;
          }
        }
        printf("%d\n", correct_answers);
    }
}