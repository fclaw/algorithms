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

// Function to split a mathematical expression string into tokens (numbers and operators)
vs tokenize(const std::string& expression) {
    vs tokens;
    std::string current_number;

    for (int i = 0; i < (int)expression.length(); ++i) {
        char c = expression[i];

        if (isspace(c)) {
            continue; // Skip all whitespace
        }

        if (isdigit(c)) {
            current_number += c;
        } else {
            // It's an operator or parenthesis.
            // First, push any number we've accumulated.
            if (!current_number.empty()) {
                tokens.push_back(current_number);
                current_number.clear();
            }

            // Now, analyze the current character 'c'.
            bool is_unary_context = tokens.empty() || 
                                    std::string("+-*/(").find(tokens.back()) != std::string::npos;

            if ((c == '+' || c == '-') && is_unary_context) {
                // This is a unary operator.
                if (c == '-') {
                    // Start a new number with the negative sign.
                    current_number += c;
                }
                // If c == '+', we do nothing, effectively ignoring the redundant unary plus.
            } else {
                // This is a binary operator or a parenthesis.
                tokens.push_back(std::string(1, c));
            }
        }
    }

    // After the loop, push any remaining number.
    if (!current_number.empty()) {
        tokens.push_back(current_number);
    }

    return tokens;
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
          vs tokens = tokenize(exp);
          vs reduced_exp = do_reduction(tokens);
          reduced_exp.insert(reduced_exp.begin(), tokensToString(tokens));
          for(auto s : reduced_exp) {
            printf("%s\n", (s + " = " + left).c_str());
          }
        }
    }
}