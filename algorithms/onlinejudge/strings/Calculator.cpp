/*
───────────────────────────────────────────────────────────────
🧳 UVa 11070 The good old times, https://onlinejudge.org/external/110/11070.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



std::unordered_map<char, std::pair<int, std::function<double(double, double)>>> 
 op_prec = 
 {{'+', {1, std::plus<double>()}}, 
 {'-', {1, std::minus<double>()}}, 
 {'*', {2, std::multiplies<double>()}}, 
 {'/', {2, std::divides<double>()}}};


double parse_num(const std::string& exp, size_t& i) {
  bool is_neg = exp[i] == '-';
  if(is_neg) i++;
  size_t j = i;
  while(j < exp.size() && 
        (std::isdigit(exp[j]) || 
         exp[j] == '.')) j++;     
  double num = std::stod(exp.substr(i, j));
  i = j;
  return is_neg ? -num : num;
}

void apply_op(std::stack<double>& eval_stack, std::stack<char>& op_stack) {
  char top_op = op_stack.top();
  double x = eval_stack.top();
  eval_stack.pop();
  double y = eval_stack.top();
  eval_stack.pop();
  op_stack.pop();
  eval_stack.push(op_prec[top_op].second(y, x));
}


double eval(const std::string& exp) {
  std::stack<double> eval_stack;
  std::stack<char> op_stack;
  size_t i = 0;
  double num = parse_num(exp, i);
  eval_stack.push(num);
  while(i < exp.size()) {
    char curr_op = exp[i++];
    while(!op_stack.empty() &&
          (op_prec[op_stack.top()].first >= 
           op_prec[curr_op].first)) {
      apply_op(eval_stack, op_stack);
    }
    op_stack.push(curr_op);
    num = parse_num(exp, i);
    eval_stack.push(num);
  }
   while(!op_stack.empty()) {
    apply_op(eval_stack, op_stack);
  }
  return eval_stack.top();
}

namespace algorithms::onlinejudge::strings::calculator
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
        while(std::getline(std::cin, exp)) {
          printf("%.3lf\n", eval(exp));
        }
    }
}