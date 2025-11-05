/*
───────────────────────────────────────────────────────────────
🧳 UVa 10906 Strange Integration, https://onlinejudge.org/external/109/10906.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vs = std::vector<std::string>;


bool is_space(unsigned char c) { return std::isspace(c); };

bool is_operator(const std::string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

bool is_number(const std::string& s) {
  if(s.empty()) {
    return false;
  }
  return std::all_of(s.begin(), s.end(), ::isdigit);
}

bool is_variable(const std::string& s) {
  if(s.empty()) {
    return false;
  }
  return std::all_of(s.begin(), s.end(), ::isalpha);
}

// --- The Core Backtracking Function ---

// Returns true if a valid tokenization is found, false otherwise.
// Takes 'tokens' by reference to build the result efficiently.
bool backtrack(int start_index, const std::string& expression, vs& tokens, vs& out_tokens) {
  // BASE CASE: We've successfully tokenized the entire string.
  if(start_index == (int)expression.length()) {
    out_tokens = tokens;
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
      if(is_number(candidate) || 
         is_variable(candidate)) {
        is_valid_candidate = true;
      }
    } else {
      const std::string& last_token = tokens.back();
      if(is_number(last_token)) {
        // If the last token was a number, the next must be an operator.
        if (is_operator(candidate) || 
            is_variable(candidate)) {
          is_valid_candidate = true;
        }
      } else if (is_operator(last_token)) {
        // If the last token was an operator, the next must be a number.
        if (is_number(candidate) || 
            is_variable(candidate)) {
          is_valid_candidate = true;
        }
      } else if (is_variable(last_token)) {
        // If the last token was an operator, the next must be a number.
        if (is_number(candidate) || 
            is_operator(candidate)) {
          is_valid_candidate = true;
        }
      }
    }

    // --- RECURSION and BACKTRACKING ---
    if(is_valid_candidate) {
      // 1. CHOOSE: Add the candidate token to our list.
      tokens.push_back(candidate);

      // 2. EXPLORE: Recurse with the new index.
      if(backtrack(start_index + len, expression, tokens, out_tokens)) {
        return true; // If the recursive call found a solution, propagate success.
      }

      // 3. UNCHOOSE: If the recursive call failed, backtrack by removing the candidate.
      tokens.pop_back();
    }
  }

  // If the loop finishes without finding any valid path, this path is a dead end.
  return false;
}

struct ExpressionInfo {
  std::string text; // The string representation, e.g., "2+3"
  std::string top_op;      // The top-level operator, e.g., '+'. Use a placeholder like ' ' for numbers.
};


/**
 * Constructs a token vector for an expression, adding parentheses where needed.
 */
std::vector<std::string> 
  parenthesize(
    const std::vector<std::string>& tokens,
    const std::unordered_map<std::string, ExpressionInfo>& exp_map) {

    if (tokens.size() != 3) {
        // Handle error or invalid input
        return {};
    }

    const std::string& left_token = tokens[0];
    const std::string& op_token = tokens[1];
    const std::string& right_token = tokens[2];
    
    std::vector<std::string> result_tokens;

   // --- Process Left Operand ---
   if(is_variable(left_token)) {
     const auto& info = exp_map.at(left_token);
     // Left operand ONLY needs parens for PRECEDENCE conflict.
     if (op_token == "*" && info.top_op == "+") {
        result_tokens.push_back("(");
        result_tokens.push_back(left_token);
        result_tokens.push_back(")");
      } else {
        result_tokens.push_back(left_token);
      }
   } else {
      result_tokens.push_back(left_token);
   }

   // --- Add Operator ---
   result_tokens.push_back(op_token);

   // --- Process Right Operand ---
  if(is_variable(right_token)) {
    const auto& info = exp_map.at(right_token);
    // Right operand needs parens for PRECEDENCE or ASSOCIATIVITY conflict.
    bool precedence_conflict = (op_token == "*" && info.top_op == "+");
    bool associativity_conflict = (op_token == info.top_op); // e.g., outer '+' and inner '+'

    if (precedence_conflict || associativity_conflict) {
      result_tokens.push_back("(");
      result_tokens.push_back(right_token);
      result_tokens.push_back(")");
    } else {
        result_tokens.push_back(right_token);
    }
  } else {
    result_tokens.push_back(right_token);
  }

  return result_tokens;
}


std::string do_reduction(const vs& expressions, std::unordered_map<std::string, ExpressionInfo>& exp_map) {
    vs current_expressions = expressions;
    while(current_expressions.size() >= 1) {
      std::string curr_exp = current_expressions.front();
      size_t eq = curr_exp.find('=');
      std::string lhs = curr_exp.substr(0, eq);
      std::string rhs = curr_exp.substr(eq + 1);
      vs tokens, out_tokens;
      backtrack(0, rhs, tokens, out_tokens);
      std::string result_exp;
      std::string last_op;
      /*
        * Parenthesization Rule:
        * To preserve the correct order of operations, parentheses are required around a
        * sub-expression IF its root operator has lower precedence than the outer operator.
        * In this grammar, this means an addition ('+') sub-expression needs parentheses
        * when it becomes an operand of a multiplication ('*').
        * Example: A*B where A = 2+3 must become (2+3)*B, not 2+3*B.
        * The operator inside S has a lower precedence than the operator outside S (i.e., the one next to S).
        * The operator inside S is the same as the operator outside and to the right (due to left-associativity)
      */
      vs parenthesized_tokens = parenthesize(out_tokens, exp_map);
      for(auto t : parenthesized_tokens) {
        if(is_variable(t)) {
          auto exp = exp_map.at(t).text;
          result_exp += exp;
        } else {
          result_exp += t;
        }

        if(is_operator(t)) {
          last_op = t;
        }
      }
      exp_map[lhs] = {result_exp, last_op};
      current_expressions.erase(current_expressions.begin());
    }
    size_t eq = expressions.back().find('=');
    std::string lhs = expressions.back().substr(0, eq);
    return exp_map.at(lhs).text;
}


namespace algorithms::onlinejudge::strings::strange_integration
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

        int t_cases, n, t_case = 1;
        std::string exp;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d\n", &n);
          vs expressions(n);
          for(int i = 0; i < n; ++i) {
            std::getline(std::cin, exp);
            exp.erase(
              std::remove_if(
                exp.begin(), 
                exp.end(), 
                is_space), 
              exp.end());
            expressions[i] = exp;
          }
          std::unordered_map<std::string, ExpressionInfo> exp_map;
          std::string reduced_exp = do_reduction(expressions, exp_map);
          printf("Expression #%d: %s\n", t_case++, reduced_exp.c_str());
        }
    }
}