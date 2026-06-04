/*
───────────────────────────────────────────────────────────────
🧳  Otpor, https://open.kattis.com/problems/otpor, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




int findFirstConnector(const std::string& schema, size_t start, size_t end) {
   int balance = 0;
  for (size_t i = start; i <= end; ++i) {
    if (schema[i] == '(') {
      balance++;
    } else if (schema[i] == ')') {
      balance--;
    } else if (balance == 0) {
      // Check if this character is a connector
      if (schema[i] == '-' || schema[i] == '|') {
        return (int)i;
      }
    }
  }
  return -1; // No connector found at this level
}

double apply_connector(double left, double right, char connector) {
  if (connector == '-') {
    // Series: Resistance adds up
    return left + right;
  } else if (connector == '|') {
    // Parallel: 1/R_total = 1/R1 + 1/R2
    // Simplified for two values: (R1 * R2) / (R1 + R2)
    // Guard against division by zero just in case
    if (left + right == 0) return 0;
    return (left * right) / (left + right);
  }
  return 0;
}


bool has_parenthesised(const std::string& schema, size_t start, size_t end) {
  // 1. Basic bounds and character check
  if (start >= end) return false;
  if (schema[start] != '(' || schema[end] != ')') return false;

  int balance = 0;
    
  // 2. Loop through the string, but STOP BEFORE the last character
  for (size_t i = start; i < end; ++i) {
    if (schema[i] == '(') balance++;
    else if (schema[i] == ')') balance--;
        
    // 3. THE TRAP CHECK: 
    // If balance drops to 0 before we reach the very end, it means 
    // the first '(' closed early. Example: "(1+2) * (3+4)"
    if (balance == 0) return false;
  }

  // If balance is 1 right before the last character (which we know is ')'), 
  // then it perfectly wraps the entire expression!
  return balance == 1;
}


double getCircuitResistance(const std::string& schema, size_t start, size_t end, std::unordered_map<std::string, double>& resistors) {

  // clean from parentheses on both sides
  if(has_parenthesised(schema, start, end)) {
    return getCircuitResistance(schema, start + 1, end - 1, resistors);
  }

  int pos = findFirstConnector(schema, start, end);

  if(~pos) {
    double left = getCircuitResistance(schema, start, pos - 1, resistors);
    double right = getCircuitResistance(schema, pos + 1, end, resistors);
    return apply_connector(left, right, schema[pos]);
  }

  auto resistor = schema.substr(start, end - start + 1);
  return resistors.at(resistor);
}



namespace algorithms::kattis::strings::otpor
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

        int n;
        while(std::cin >> n && n) {
          std::unordered_map<std::string, double> resistors;
          double resistance;
          for(int i = 1; i <= n; ++i) {
            std::cin >> resistance;
            std::string label = "R" + std::to_string(i);
            resistors[label] = resistance;        
          }
          // 1. CONSUME THE NEWLINE leftover from 'cin >> resistance'
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::string schema;
          std::getline(std::cin, schema);
          double res = getCircuitResistance(schema, 0, schema.size() - 1, resistors);
          std::cout << std::fixed << std::setprecision(5) << res << std::endl;
        }
    }
}