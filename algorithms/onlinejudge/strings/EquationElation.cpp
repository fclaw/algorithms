/*
───────────────────────────────────────────────────────────────
🧳 UVa 397 Equation Elation, https://onlinejudge.org/external/3/397.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vs = std::vector<std::string>;

bool is_space(unsigned char c) { return std::isspace(c); };

std::unordered_map<std::string, std::function<int(int, int)>> 
 operations = 
 {{"+", std::plus<int>()}, 
 {"-", std::minus<int>()}, 
 {"*", std::multiplies<int>()}, 
 {"/", std::divides<int>()}};


bool is_operator(const std::string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

bool is_number(const std::string& s) {
  if(s.empty()) {
    return false;
  }

  auto start = s.begin();
  if(s.front() == '-' || s.front() == '+') {
    start = s.begin() + 1;
  }
  return start < s.end() && std::all_of(start, s.end(), ::isdigit);
}


// --- The Core Backtracking Function ---

// Returns true if a valid tokenization is found, false otherwise.
// Takes 'tokens' by reference to build the result efficiently.
bool backtrack(int start_index, const std::string& expression, vs& tokens, vs& reduction) {
  // BASE CASE: We've successfully tokenized the entire string.
  if(start_index == (int)expression.length()) {
    reduction = tokens;
    return true; // A solution has been found!
   }

  // RECURSIVE STEP: Try every possible next token starting from start_index.
  // We iterate through all possible lengths for the next token.
  for (int len = 1; start_index + len <= (int)expression.length(); ++len) {
    std::string candidate = expression.substr(start_index, len);
    // --- CONTEXTUAL VALIDATION ---
    // Apply rules to see if this candidate is valid right now.
    bool is_valid_candidate = false;
    if(tokens.empty()) {
      // The first token must be a number (e.g., "5", "-92").
      if(is_number(candidate)) {
        is_valid_candidate = true;
      }
    } else {
      const std::string& last_token = tokens.back();
      if(is_number(last_token)) {
        // If the last token was a number, the next must be an operator.
        if (is_operator(candidate)) {
          is_valid_candidate = true;
        }
      } else if (is_operator(last_token)) {
        // If the last token was an operator, the next must be a number.
        if (is_number(candidate)) {
          is_valid_candidate = true;
        }
      }
    }

    // --- RECURSION and BACKTRACKING ---
    if(is_valid_candidate) {
      // 1. CHOOSE: Add the candidate token to our list.
      if(is_number(candidate)) {
        if(candidate.front() == '+')
          candidate = candidate.erase(0, 1);
      }
      tokens.push_back(candidate);

      // 2. EXPLORE: Recurse with the new index.
      if(backtrack(start_index + len, expression, tokens, reduction)) {
        return true; // If the recursive call found a solution, propagate success.
      }

      // 3. UNCHOOSE: If the recursive call failed, backtrack by removing the candidate.
      tokens.pop_back();
    }
  }

  // If the loop finishes without finding any valid path, this path is a dead end.
  return false;
}


// Converts a vector of tokens back into a readable string
std::string tokensToString(const vs& tokens) {   
  std::string result = tokens[0];
  for(size_t i = 1; i < tokens.size(); ++i) {
    result += " " + tokens[i];
  }
  return result;
}

// Performs a single mathematical operation on two number strings
int performOperation(const std::string& lhs_str, const std::string& op, const std::string& rhs_str) {
  return operations[op](std::stoi(lhs_str), std::stoi(rhs_str));
}


vs do_reduction(const vs& tokens) {
  vs reduction_steps;
  vs current_tokens = tokens;

  while(current_tokens.size() > 1) {
    int op_idx = -1; // Index of the operator to use

    // 1. Pass 1: Find the first high-precedence operator (* or /)
    for(int i = 0; i < (int)current_tokens.size(); ++i) {
      if (current_tokens[i] == "*" || 
          current_tokens[i] == "/") {
        op_idx = i;
        break;
      }
    }

    // 2. Pass 2: If no high-precedence ops, find the first low-precedence one (+ or -)
    if(op_idx == -1) {
      for(int i = 0; i < (int)current_tokens.size(); ++i) {
        if (current_tokens[i] == "+" || 
            current_tokens[i] == "-") {
          op_idx = i;
          break;
        }
      }
    }
        
    // 3. Perform the calculation
    int result = performOperation(current_tokens[op_idx - 1], current_tokens[op_idx], current_tokens[op_idx + 1]);

    // 4. Create the new, reduced list of tokens
    vs next_tokens;
    // Add tokens before the operation
    for(int i = 0; i < op_idx - 1; ++i) {
      next_tokens.push_back(current_tokens[i]);
    }
    // Add the calculated result
    next_tokens.push_back(std::to_string(result));
    // Add tokens after the operation
    for (int i = op_idx + 2; i < (int)current_tokens.size(); ++i) {
      next_tokens.push_back(current_tokens[i]);
    }

    // 5. Update current_tokens for the next loop
    current_tokens = next_tokens;
    // 6. Record the current state of the expression as a string
    reduction_steps.push_back(tokensToString(current_tokens));
  }

  return reduction_steps;
}


namespace algorithms::onlinejudge::strings::equation_elation
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

        bool first_line = true;
        std::string equation;
        while(std::getline(std::cin, equation)) {
          if(first_line) {
            first_line = false;
          } else {
            printf("\n");
          }
         
          equation.erase(
            std::remove_if(
              equation.begin(), 
              equation.end(), 
              is_space), 
            equation.end());
          size_t eq_pos = equation.find('=');
          std::string left = equation.substr(eq_pos + 1, equation.length());
          std::string exp = equation.substr(0, eq_pos);
          vs tokens, reduction;
          backtrack(0, exp, tokens, reduction);
          vs reduced_exp = do_reduction(reduction);
          reduced_exp.insert(reduced_exp.begin(), tokensToString(reduction));
          for(auto s : reduced_exp) {
            printf("%s\n", (s + " = " + left).c_str());
          }
        }
    }
}