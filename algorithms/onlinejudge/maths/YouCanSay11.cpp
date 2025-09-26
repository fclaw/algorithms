/*
───────────────────────────────────────────────────────────────
🧳 UVa 10929 You can say 11, rt: s
───────────────────────────────────────────────────────────────
 * --- Divisibility by 11 ---
 *
 * A number is divisible by 11 if the alternating sum of its digits is
 * divisible by 11.
 *
 * Method 1: Alternating Sum
 * Start from the rightmost digit (the ones place) and alternately subtract and
 * add the digits. If the final result is 0 or a multiple of 11, the original
 * number is divisible by 11.
 *
 * Example: 8,291,547
 * Calculation: 7 - 4 + 5 - 1 + 9 - 2 + 8 = 22
 * Since 22 is divisible by 11, the number 8,291,547 is divisible by 11.
 *
 * Method 2: Difference of Sums (Often easier to implement)
 * 1. Sum the digits in the odd positions (1st, 3rd, 5th, ... from the right).
 * 2. Sum the digits in the even positions (2nd, 4th, 6th, ... from the right).
 * 3. Calculate the difference: (sum of odd positions) - (sum of even positions).
 * 4. If the difference is divisible by 11, the number is divisible by 11.
 *
 * Example: 8,291,547
 * Odd positions (7, 5, 9, 8): 7 + 5 + 9 + 8 = 29
 * Even positions (4, 1, 2):  4 + 1 + 2 = 7
 * Difference: 29 - 7 = 22.  Divisible by 11.
 *
 * Why it works:
 * The rule is based on modular arithmetic. The powers of 10 modulo 11
 * follow a pattern: 10^0=1, 10^1=-1, 10^2=1, 10^3=-1, ... (mod 11).
 * The alternating sum of digits is equivalent to calculating the number's
 * value modulo 11.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>





bool isDivisibleBy11(const std::string& numStr) {
  int oddSum = 0;
  int evenSum = 0;
  int length = numStr.length();

  for(int i = 0; i < length; ++i) {
    int digit = numStr[length - 1 - i] - '0'; // Convert char to int
    if(i % 2 == 0) {
      oddSum += digit;  // Odd position from the right
    } else {
      evenSum += digit; // Even position from the right
    }
  }

  int difference = oddSum - evenSum;
  return difference % 11 == 0;
}


namespace algorithms::onlinejudge::maths::you_can_say_11
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

        std::string numStr;
        while(std::cin >> numStr && numStr != "0") {
          if(isDivisibleBy11(numStr)) {
            printf("%s is a multiple of 11.\n", numStr.c_str());
          } else {
            printf("%s is not a multiple of 11.\n", numStr.c_str());
          }
        }
    }
}