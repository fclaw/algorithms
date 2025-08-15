/*
───────────────────────────────────────────────────────────────
🧳 UVa 493 Rational Spiral, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


int gcd(int a, int b) {
  if(b == 0) return a;
  return gcd(b, a % b);
}


struct Rational
{
    int numerator;
    int denominator;
    Rational() {}
    Rational(int num, int denom) {
      if(denom == 0) {
        numerator = 0;
        denominator = 0;
      } else {
        int g = gcd(std::abs(num), std::abs(denom));
        numerator = num / g;
        denominator = denom / g;
        
        // --- THE KEY CANONICALIZATION STEP ---
        // Ensure the denominator is always positive.
        if(denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
      }
    }

    // New, simpler operator==
    bool operator == (const Rational& other) const {
      // No std::abs needed, because the state is now canonical.
      return numerator == other.numerator && denominator == other.denominator;
    }
};

// --- THE HASH FUNCTION ---
// We specialize the std::hash template for our Rational struct.
// This must be done inside the std namespace.
namespace std {
  template <>
  struct hash<Rational> {
    size_t operator()(const Rational& r) const {
      // Use a robust method to combine the hashes of the two members.
      auto num_hash = std::hash<int>{}(r.numerator);
      auto denom_hash = std::hash<int>{}(r.denominator);

      // This is a common and effective bit-mixing formula.
      return num_hash ^ (denom_hash + 0x9e3779b9 + (num_hash << 6) + (num_hash >> 2));
    }
  };
}


using set_rational = std::unordered_set<Rational>;


// Helper function to process a potential new rational number.
// Returns true if the target is found, false otherwise.
bool process_rational(int num, int denom, int target, int& idx, Rational& target_rational, set_rational& seen) {
  Rational rational(num, denom);
  // If we've already seen this simplified fraction, skip it.
  if(seen.count(rational)) return false;

   seen.insert(rational);
   idx++;
   if(idx == target) {
      target_rational = rational;
      return true; // Target found!
    }
    return false;
}


namespace algorithms::onlinejudge::maths::rational_spiral
{
    /** https://onlinejudge.org/external/4/493.pdf */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
 
        int target;
        while(scanf("%d", &target) == 1) {
          // init state
          set_rational seen;
          seen.insert(Rational(0, 0));
          int idx = -1;
          int numerator = 0;
          int denominator = 0;
          Rational target_rational;
          while(true) {

            // numerator goes up
            for(int num = (-1) * numerator; num <= numerator; num++) {
              bool is_found = process_rational(num, denominator, target, idx, target_rational, seen);
              if(is_found) goto found;
            }

            numerator += 1;

            // denominator goes right
            for(int denom = (-1) * denominator; denom <= denominator; denom++) {
              bool is_found = process_rational(numerator, denom, target, idx, target_rational, seen);
              if(is_found) goto found;
            }

            denominator += 1;

            // numerator goes down
            for(int num = numerator; num >= (-1) * numerator; num--) {
              bool is_found = process_rational(num, denominator, target, idx, target_rational, seen);
              if(is_found) goto found;
            }

            // denominator goes left
            for(int denom = denominator; denom >= (-1) * denominator; denom--) {
              bool is_found = process_rational(numerator, denom, target, idx, target_rational, seen);
              if(is_found) goto found;
            }
          }

          found:
          printf("%d / %d\n", target_rational.numerator, target_rational.denominator);
        }
    }
}