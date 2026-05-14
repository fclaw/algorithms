/*
───────────────────────────────────────────────────────────────
🧳 UVa 11357 Ensuring Truth, https://onlinejudge.org/external/113/11357.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


bool evaluate_clause(const std::string& clause) {
  std::unordered_set<char> pos_vars; // Tracks variables like 'a'
  std::unordered_set<char> neg_vars; // Tracks variables like '~a'

  for (size_t i = 0; i < clause.length(); ++i) {
    char c = clause[i];

    if (isalpha(c)) {
      // Found a literal like 'a'
      if (neg_vars.count(c)) return false; // Contradicts previously found '~a'
      pos_vars.insert(c);
    } else if (c == '~') {
      // Found a literal like '~a'
      // Move to next character to see which variable it is
      i++; 
      if (i < clause.length()) {
        char var = clause[i];
        if (pos_vars.count(var)) return false; // Contradicts previously found 'a'
        neg_vars.insert(var);
      }
    }
   // Symbols like '&' are effectively ignored by skipping to the next loop iteration
  }
    
  // No contradictions (A and ~A) found in the entire clause
  return true; 
}

std::vector<std::string> parse_formula(const std::string& formula) {
  std::vector<std::string> clauses;
  std::stringstream ss(formula);
  std::string item;

  while (std::getline(ss, item, '|')) {
    // 1. Trim whitespaces first
    size_t first = item.find_first_not_of(' ');
    size_t last = item.find_last_not_of(' ');

    if (first != std::string::npos) {
      std::string clause = item.substr(first, (last - first + 1));

      // 2. Remove the surrounding parentheses '(' and ')'
      // substr(1, length - 2) skips the first char and stops before the last char
      if (clause.size() >= 2 && 
          clause.front() == '(' && 
          clause.back() == ')') {
          clause = clause.substr(1, clause.size() - 2);
      }

      clauses.push_back(clause);
    }
  }
  return clauses;
}


namespace algorithms::onlinejudge::strings::ensuring_truth
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

        int t_cases;
        std::string formula;
        scanf("%d", &t_cases);
        while(t_cases--) {
          while_read(formula);
          
          std::vector<std::string> clauses = parse_formula(formula);
          bool is_satisfiable = false;
          for(auto clause : clauses) {
            is_satisfiable |= evaluate_clause(clause);
          }
          printf("%s\n", is_satisfiable ? "YES" : "NO");
        }
    }
}