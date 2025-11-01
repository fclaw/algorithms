/*
───────────────────────────────────────────────────────────────
🧳 UVa 11291 Smeech, https://onlinejudge.org/external/112/11291.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



const std::string TERM = "()";
constexpr char space = ' ';
constexpr char open_bracket = '(';
constexpr char close_bracket = ')';


bool is_integer(const std::string& s, size_t l, size_t r) {
  for(size_t i = s[l] == '-' ? l + 1 : l; i < r; ++i) {
    if(!std::isdigit(s[i])) {
      return false;
    }
  }
  return true;
}

bool is_probability(const std::string& s, size_t l, size_t r) {
  return s[l] == open_bracket && s[r] == close_bracket;
}


std::pair<size_t, size_t> fetch_pos(const std::string& s, size_t l) {
  size_t i = l;
  if(s[i] == '-' || std::isdigit(s[i])) {
    size_t j = i + 1;
    while(std::isdigit(s[j])) j++;
    return {i, j};
  } else {
    size_t j = i + 1;
    int balance = 1;
    while(balance > 0) {
      if(s[j] == open_bracket) {
        ++balance;
      } else if(s[j] == close_bracket) {
        --balance;
      }
      ++j;
    }
    return {i, j};
  }
}


double calculate_ev(const std::string& s, size_t l, size_t r) {   
  // Check for empty range
  if (l >= r) return 0.0;

  double ev = 0.0;
  if(is_integer(s, l, r)) {
    bool is_neg = s[l] == '-';
    if(is_neg) l++;
    return (is_neg ? -1 : 1) * std::stod(s.substr(l, r - l));
  } else if(is_probability(s, l, r - 1)) {
    size_t first_space_pos = s.find(space, l + 1);
    std::string prob_str = s.substr(l + 1, first_space_pos - l);
    double prob = std::stod(prob_str);
    auto pair = fetch_pos(s, first_space_pos + 1);
    double first_ev = calculate_ev(s, pair.first, pair.second);
    size_t second_space_pos = pair.second + 1;
    while(s[second_space_pos] == space) second_space_pos++;
    double second_ev = calculate_ev(s, second_space_pos, r - 1);
    ev = prob * (first_ev + second_ev) + (1 - prob) * (first_ev - second_ev);
  }
  return ev;
}


namespace algorithms::onlinejudge::strings::smeech
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

        std::string exp;
        while(std::getline(std::cin, exp) && exp != TERM) {
          printf("%.2lf\n", calculate_ev(exp, 0, exp.size()));
        }
    }
}