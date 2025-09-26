/*
───────────────────────────────────────────────────────────────
🧳 UVa 11344 The Huge One, https://onlinejudge.org/external/113/11344.pdf,  rt: s
───────────────────────────────────────────────────────────────
 * --- COMMON DIVISIBILITY RULES (1-12) ---
 *
 * A set of efficient, non-computational rules to check if an integer 'N' is
 * perfectly divisible by a given divisor. These are particularly useful for
 * large numbers represented as strings.
 *
 * Divisible by 1:
 *   - Rule: All integers are divisible by 1.
 *
 * Divisible by 2:
 *   - Rule: The last digit of N is an even number (0, 2, 4, 6, 8).
 *   - Check: `(last_digit) % 2 == 0`.
 *
 * Divisible by 3:
 *   - Rule: The sum of the digits of N is divisible by 3. This can be applied recursively.
 *   - Check: `(sum_of_digits) % 3 == 0`.
 *
 * Divisible by 4:
 *   - Rule: The number formed by the last two digits of N is divisible by 4.
 *   - Check: `(last_two_digits) % 4 == 0`.
 *
 * Divisible by 5:
 *   - Rule: The last digit of N is either 0 or 5.
 *   - Check: `last_digit == 0 || last_digit == 5`.
 *
 * Divisible by 6:
 *   - Rule: The number N is divisible by BOTH 2 and 3.
 *   - Check: Apply the rules for 2 and 3 simultaneously.
 *
 * Divisible by 7:
 *   - Rule: (Recursive) Take the last digit of N, double it, and subtract this
 *     from the rest of the number. If the result is divisible by 7 (including 0),
 *     then N is divisible by 7.
 *   - Example (for 357): Last digit is 7. Double it to get 14. Subtract from the rest (35).
 *     35 - 14 = 21. Since 21 is divisible by 7, 357 is divisible by 7.
 *   - Note: For programming, `N % 7 == 0` is usually much faster unless N is a string.
 *
 * Divisible by 8:
 *   - Rule: The number formed by the last three digits of N is divisible by 8.
 *   - Check: `(last_three_digits) % 8 == 0`.
 *
 * Divisible by 9:
 *   - Rule: The sum of the digits of N is divisible by 9. This can be applied recursively.
 *   - Check: `(sum_of_digits) % 9 == 0`.
 *
 * Divisible by 10:
 *   - Rule: The last digit of N is 0.
 *   - Check: `last_digit == 0`.
 *
 * Divisible by 11:
 *   - Rule: The alternating sum of the digits of N (from right to left) is
 *     divisible by 11.
 *   - Example (for 1829): 9 - 2 + 8 - 1 = 14. Not divisible by 11.
 *   - Example (for 2541): 1 - 4 + 5 - 2 = 0. Divisible by 11.
 *   - Check: `(alternating_sum) % 11 == 0`.
 *
 * Divisible by 12:
 *   - Rule: The number N is divisible by BOTH 3 and 4.
 *   - Check: Apply the rules for 3 and 4 simultaneously.
 *
 * --- WHY THEY WORK (MODULAR ARITHMETIC) ---
 * These rules are shortcuts for calculating N mod D without full division.
 * For 2, 4, 5, 8, 10: Based on properties of powers of 10. (e.g., 1000 is divisible by 8).
 * For 3, 9: Because 10^k ≡ 1 (mod 3) and 10^k ≡ 1 (mod 9) for any k > 0.
 * For 6, 12: Based on prime factorization (6=2*3, 12=3*4), since the factors are coprime.
 * For 7, 11: Based on the pattern of powers of 10 modulo 7 or 11.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


// Helper function to get the numeric value of a character
int to_digit(char c) {
    return c - '0';
}

bool isDivisibleBy1(const std::string& numStr) {
    return true; // All integers are divisible by 1
}

bool isDivisibleBy2(const std::string& numStr) {
    if (numStr.empty()) return false;
    int last_digit = to_digit(numStr.back());
    return last_digit % 2 == 0;
}

bool isDivisibleBy3(const std::string& numStr) {
    long long sum = 0;
    for (char c : numStr) {
        sum += to_digit(c);
    }
    return sum % 3 == 0;
}

bool isDivisibleBy4(const std::string& numStr) {
    if (numStr.length() < 2) {
        return std::stoi(numStr) % 4 == 0;
    }
    int last_two_digits = std::stoi(numStr.substr(numStr.length() - 2));
    return last_two_digits % 4 == 0;
}

bool isDivisibleBy5(const std::string& numStr) {
    if (numStr.empty()) return false;
    char last_char = numStr.back();
    return last_char == '0' || last_char == '5';
}

bool isDivisibleBy6(const std::string& numStr) {
    // A number is divisible by 6 if it's divisible by both 2 and 3.
    return isDivisibleBy2(numStr) && isDivisibleBy3(numStr);
}

bool isDivisibleBy7(const std::string& numStr) {
    // For programming, direct modulo is usually faster unless numStr is very large.
    long long num = 0;
    for (char c : numStr) {
      num = (num * 10 + to_digit(c)) % 7;
    }
    return num == 0;
}

bool isDivisibleBy8(const std::string& numStr) {
    if (numStr.length() < 3) {
        return std::stoi(numStr) % 8 == 0;
    }
    int last_three_digits = std::stoi(numStr.substr(numStr.length() - 3));
    return last_three_digits % 8 == 0;
}


// And so on for 7, 8, 9, 10, 11, 12...
// Let's implement 9 and 11 as they are common.

bool isDivisibleBy9(const std::string& numStr) {
    long long sum = 0;
    for (char c : numStr) {
        sum += to_digit(c);
    }
    return sum % 9 == 0;
}

bool isDivisibleBy10(const std::string& numStr) {
    if (numStr.empty()) return false;
    return numStr.back() == '0';
}

bool isDivisibleBy11(const std::string& numStr) {
    long long alternating_sum = 0;
    int sign = 1;
    for (int i = numStr.length() - 1; i >= 0; --i) {
        alternating_sum += to_digit(numStr[i]) * sign;
        sign *= -1;
    }
    return alternating_sum % 11 == 0;
}

bool isDivisibleBy12(const std::string& numStr) {
    return isDivisibleBy3(numStr) && isDivisibleBy4(numStr);
}

// Define the function pointer type for clarity
using DivisibilityTest = bool (*)(const std::string&);

// Create an array (or vector) of these pointers
// We'll add a dummy at index 0 to make indexing intuitive (e.g., tests[3] for rule 3)
DivisibilityTest tests[] = {
    nullptr, // Index 0 is unused
    isDivisibleBy1,
    isDivisibleBy2,
    isDivisibleBy3,
    isDivisibleBy4,
    isDivisibleBy5,
    isDivisibleBy6,
    isDivisibleBy7,
    isDivisibleBy8,
    isDivisibleBy9,
    isDivisibleBy10,
    isDivisibleBy11,
    isDivisibleBy12
};


namespace algorithms::onlinejudge::maths::the_huge_one
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
          std::string numStr;
          std::cin >> numStr;
          int n;
          bool is_wonderful = true;
          scanf("%d", &n);
          for(int i = 0; i < n; ++i) {
            int rule;
            scanf("%d", &rule);
            is_wonderful &= tests[rule](numStr);
          }
          printf("%s - %s.\n", numStr.c_str(), is_wonderful ? "Wonderful" : "Simple");
        }
    }
}