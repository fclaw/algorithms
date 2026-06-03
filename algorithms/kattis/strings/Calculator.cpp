/*
───────────────────────────────────────────────────────────────
🧳  Calculator, https://open.kattis.com/problems/calculator, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


int get_rank(char c) {
  if (c == '+' || c == '-') return 1;
  if (c == '*' || c == '/') return 2;
  return 100; 
}


double apply_operation(double left, double right, char op) {
  switch(op) {
    case '+': return left + right;
    case '-': return left - right;
    case '*': return left * right;
    case '/': return left / right;
    default: throw std::invalid_argument("Invalid operator");
  }
}

bool is_binary_op(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

//Find the weakest operator OUTSIDE of all parentheses
int findWeakestOperator(const std::string& expr, size_t start, size_t end) {
  int pivot = -1;
  int min_prec = 100;
  int balance = 0;
  for(int i = (int)start; i <= (int)end; ++i) {
    if(expr[i] == '(') {
      balance++;
    } else if(expr[i] == ')') {
      balance--;
    }

    // Only look at operators when we are NOT inside brackets
    if (balance == 0 && is_binary_op(expr[i])) {      
      // Unary Guard: Skip signs attached to numbers (like -5)
      bool is_unary = (i == (int)start) || (!std::isdigit((unsigned char)expr[i-1]) && expr[i-1] != ')');
      if(is_unary && (expr[i] == '+' || expr[i] == '-')) continue;

      int p = get_rank(expr[i]);
      // '<' guarantees we pick the RIGHTMOST weakest operator
      if (p <= min_prec) {
        min_prec = p;
        pivot = i;
      }
    }
  }
  return pivot;
}

bool has_parenthesised(const std::string& expr, size_t start, size_t end) {
  // 1. Basic bounds and character check
  if (start >= end) return false;
  if (expr[start] != '(' || expr[end] != ')') return false;

  int balance = 0;
    
  // 2. Loop through the string, but STOP BEFORE the last character
  for (size_t i = start; i < end; ++i) {
    if (expr[i] == '(') balance++;
    else if (expr[i] == ')') balance--;
        
    // 3. THE TRAP CHECK: 
    // If balance drops to 0 before we reach the very end, it means 
    // the first '(' closed early. Example: "(1+2) * (3+4)"
    if (balance == 0) return false;
  }

  // If balance is 1 right before the last character (which we know is ')'), 
  // then it perfectly wraps the entire expression!
  return balance == 1;
}

double parse(const std::string& expr, size_t start, size_t end) {
  
  // clean from parentheses on both sides
  if(has_parenthesised(expr, start, end)) {
    return parse(expr, start + 1, end - 1);
  }

  int pos = findWeakestOperator(expr, start, end);

  if(pos != -1) {
    double left = parse(expr, start, pos - 1);
    double right = parse(expr, pos + 1, end);
    return apply_operation(left, right, expr[pos]);
  }

  // Base case, only a single integer
  return std::stod(expr.substr(start, end + 1));
}


namespace algorithms::kattis::strings::calculator
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

  
        std::string expression;
        while(std::getline(std::cin, expression)) {
          // eliminate spaces from the expression to simplify parsing
          expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());

          double result = parse(expression, 0, expression.length() - 1);
         // 2. Kill the Negative Zero
         // If the number is going to round to 0.00 anyway, force it to be positive 0.0
         if (std::abs(result) < 0.005) {
            result = 0.0; 
         }
         
         std::cout << std::fixed << std::setprecision(2) << result << std::endl;
        }
    }
}