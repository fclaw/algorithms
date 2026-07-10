/*
───────────────────────────────────────────────────────────────
🧳 UVa 11734 Big Number of Teams will Solve This, https://onlinejudge.org/external/117/11734.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


enum Verdict { Yes, WrongAnswer, FormatError};



bool check_format_error(const std::string& input) {
  bool is_prev_space = false;
  for(char c : input) {
    if(std::isspace(c)) {
      if(!is_prev_space) {
        return true;
      } else {
        is_prev_space = true;
      }
    } else {
      if(is_prev_space) {
        is_prev_space = false;
      }
    }
  }
  return false;
}

bool check_wrong_answer(const std::string& judge, const std::string& input) {
  
   std::string no_spaces_input;
   for(char c : input) {
     if(!std::isspace(c)) {
        no_spaces_input.push_back(c);
     }
   }

  if(no_spaces_input.size() > judge.size()) {
    return true;
  }

  for(int i = 0; i < (int)judge.size(); ++i) {
    if(judge[i] != no_spaces_input[i]) {
      return true;
    }
  }
  return false;
}


Verdict get_verdict(const std::string& judge, const std::string& contestant) {
  if(check_wrong_answer(judge, contestant)) {
    return WrongAnswer; 
  } else if(check_format_error(contestant)) {
    return FormatError;
  } else {
    return Yes;
  }
}

std::string verdict_to_string(Verdict verdict) {
    switch(verdict) {
      case Yes:
        return "Yes";
      case WrongAnswer:
        return "Wrong Answer";
      default:
        return "Output Format Error";
    }
}

namespace algorithms::onlinejudge::strings::verdict
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

        int t_cases, t_case = 1;
        std::cin >> t_cases;
        std::cin.ignore();
        while(t_cases--) {
          std::string contestant;
          std::string judge;
          std::getline(std::cin, contestant);
          std::getline(std::cin, judge);
          printf("Case %d: %s\n", t_case++, verdict_to_string(get_verdict(judge, contestant)).c_str());
        }
    }
}