/*
───────────────────────────────────────────────────────────────
🧳 UVa 622 Grammar Evaluation, https://onlinejudge.org/external/6/622.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;

std::stack<ll> eval_stack;



// --- Step 1: Forward Declaration ---
// "Promise" the compiler that this function will be defined later.
// This is the function prototype.
bool is_expression(const std::string& s, int l, int r);

// is_component might also be mutually recursive, so let's declare it too.
bool is_component(const std::string& s, int l, int r);


/**
 * @brief Checks if the substring s[l..r) is a valid <factor>.
 */
bool is_factor(const std::string& s, int l, int r) {
  // Check for empty range
  if (l >= r) return false;

  int size = 0;
  bool is_integer = true;
  for(int i = l; i < r; ++i) {
    if(!isdigit(s[i])) {
      is_integer = false;
      break;
    }
    size++;
  }
  if(is_integer) {
    ll val = std::stoll(s.substr(l, r - l));
    eval_stack.push(val);
    return true;
  }

  // --- Rule 3: A factor can be a parenthesized expression ---
  // Check if the substring is enclosed in a matching pair of parentheses.
  if(s[l] == '(' && s[r - 1] == ')') {
    // If it is, recursively check if the content INSIDE the parentheses
    // is a valid expression.
    return is_expression(s, l + 1, r - 1);
  }
    
  // If it's not an integer and not a valid parenthesized expression, it's not a factor.
  return false;
}


/**
 * @brief Checks if the substring s[l..r) is a valid <component>.
 * A <component> is a product of one or more <factor>s.
 * Example: "fact1 * fact2"
 */
bool is_component(const std::string& s, int l, int r) {
  int paren_balance = 0;
  for(int i = r - 1; i >= l; --i) {
    if(s[i] == ')') {
      paren_balance++;
    } else if (s[i] == '(') {
      paren_balance--;
    }
        
   // Find the last '*' at the top level.
   if(s[i] == '*' && paren_balance == 0) {
     // A component is a component multiplied by a factor.
     bool is_comp  = is_component(s, l, i);
     bool is_fac = is_factor(s, i + 1, r);
     if(is_comp && is_fac) {
      ll x = eval_stack.top();
      eval_stack.pop();
      ll y = eval_stack.top();
      eval_stack.pop();
      eval_stack.push(x * y);
      return true;
     } else return false;
    }
  }

  // If no '*' was found, this component must be a single factor.
  // We pass the check down to the next level of the grammar.
  return is_factor(s, l, r);
}

/**
 * @brief Checks if the substring s[l..r) is a valid <expression>.
 * An <expression> is a sum of one or more <component>s.
 * Example: "comp1 + comp2 + comp3"
 */
bool is_expression(const std::string& s, int l, int r) {
  // We scan from right-to-left to correctly handle left-associativity.
  // We must also handle parentheses to avoid splitting inside a sub-expression.
  int paren_balance = 0;
    
  for(int i = r - 1; i >= l; --i) {
    if(s[i] == ')') {
      paren_balance++;
    } else if (s[i] == '(') {
      paren_balance--;
    }

    // If we find a '+' at the top level (not inside any parentheses),
    // we have found our main splitting point.
    if(s[i] == '+' && paren_balance == 0) {
      // The string is an expression if the left part is a valid <expression>
      // and the right part is a valid <component>.
      bool is_exp = is_expression(s, l, i);
      bool is_comp = is_component(s, i + 1, r);
      if(is_exp && is_comp) {
        ll x = eval_stack.top();
        eval_stack.pop();
        ll y = eval_stack.top();
        eval_stack.pop();
        eval_stack.push(x + y);
        return true;
      } else return false;
    }
  }
    
  // If we scanned the whole substring and found no top-level '+',
  // it means this expression must be a single component.
  // We pass the check down to the next level of the grammar.
  return is_component(s, l, r);
}


bool is_valid_expression(const std::string& s) {
  return is_expression(s, 0, s.size());
}


namespace algorithms::onlinejudge::strings::grammar_eval
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
        scanf("%d", &t_cases);
        while(t_cases--) {
          eval_stack = std::stack<ll>();
          std::string exp;
          while_read(exp);
          printf("%s\n", is_valid_expression(exp) ? std::to_string(eval_stack.top()).c_str() : "ERROR");
        }
    }
}