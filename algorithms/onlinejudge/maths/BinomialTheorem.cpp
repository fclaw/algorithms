/*
───────────────────────────────────────────────────────────────
🧳 UVa 11955 Binomial Theorem, https://onlinejudge.org/external/119/11955.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ull = unsigned long long;
using vull = std::vector<ull>;
using vvull = std::vector<vull>;



constexpr int MAX = 50;


std::string term_to_string(const std::string& term, int power) {
  if(power == 1) return term;
  if(power == 0) return "";
  return term + "^" + std::to_string(power);
}


namespace algorithms::onlinejudge::maths::binomial_theorem
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

        vvull binomial(MAX + 1, vull(MAX + 1));
        for(int i = 0; i <= MAX; i++) {
          for(int j = 0; j <= std::min(i, MAX); j++) {
            if(j == 0 || j == i) binomial[i][j] = 1;
            else binomial[i][j] = binomial[i - 1][j - 1] + binomial[i - 1][j];
          }
        }

        int t_cases, t_case = 1;
        std::string s;
        scanf("%d", &t_cases);
        while(t_cases--) {
          std::cin >> s;
          size_t plus_pos = s.find('+');
          std::string first_term = s.substr(1, plus_pos - 1);
          size_t close_bracket_pos = s.find(')');
          std::string second_term = s.substr(plus_pos + 1, close_bracket_pos - plus_pos - 1);
          size_t power_pos = s.find('^');
          std::string power = s.substr(power_pos + 1, s.size() - power_pos - 1);
          int n = std::stoi(power);

          std::vector<std::string> exps; 
          for(int i = 0; i <= n; ++i) {
            std::string exp;
            if(binomial[n][i] > 1)
              exp = std::to_string(binomial[n][i]);
            if(!term_to_string(first_term, n - i).empty()) {
              if(!exp.empty()) exp += "*";
              exp += term_to_string(first_term, n - i);
            }
            if(!term_to_string(second_term, i).empty()) {
              if(!exp.empty()) exp += "*";
              exp += term_to_string(second_term, i);
            }
            exps.push_back(exp);
          }

          std::string exp;
          for(int i = 0; i < (int)exps.size(); ++i) {
            if(!exps[i].empty()) {
              if(i > 0) exp += "+";
              exp += exps[i];
            }
          } 
          printf("Case %d: %s\n", t_case++, exp.c_str());
        }
    }
}