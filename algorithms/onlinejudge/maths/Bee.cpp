/*
───────────────────────────────────────────────────────────────
🧳 UVa 11000 Bee, https://onlinejudge.org/external/110/11000.pdf,  
   combinatorics, the pattern is similar to Fibonacci, https://oeis.org/A000071 : a(n) = Fibonacci(n) - 1, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ull = unsigned long long;


constexpr int MAX_FIB = 105;

enum Gender { MALE, FEMALE };

struct Bee {
  Gender gender;
  int reproduction_year;
};

std::ostream& operator<<(std::ostream& os, const Bee& bee) {
  return os << "Bee(gender=" << (bee.gender == MALE ? "MALE" : "FEMALE") << ", reproduction_year=" << bee.reproduction_year << ")";
}

// ... Comparator for the priority queue (same as before) ...
struct CompareBees {
  bool operator () (const Bee& a, const Bee& b) const {
    return a.reproduction_year > b.reproduction_year;
  }
};

using bee_queue = std::priority_queue<Bee, std::vector<Bee>, CompareBees>;


void simulate_bee_reproduction(int years) {
  // Priority queue for MORTAL bees only.
  bee_queue mortal_bees;

  // The magical female is a special, separate variable.
  Bee magical_queen = {FEMALE, 0};

  for(int current_year = 0; current_year < years; ++current_year) {
    // --- Process the Magical Queen's Reproduction ---
    if(magical_queen.reproduction_year == current_year) {
      // She produces one new male.
      mortal_bees.push({MALE, current_year + 1});
      // Schedule her for the next year.
      magical_queen.reproduction_year++;
    }

    // --- Process all Mortal Bees scheduled for this year ---
    while(!mortal_bees.empty() && mortal_bees.top().reproduction_year == current_year) {
      Bee current_bee = mortal_bees.top();
      mortal_bees.pop();

      // All mortal bees die after reproducing.
      if (current_bee.gender == MALE) {
        mortal_bees.push({MALE, current_year + 1});
        mortal_bees.push({FEMALE, current_year + 1});
      } else { // Mortal FEMALE
        mortal_bees.push({MALE, current_year + 1});
      }
    }
  }

  // total bees
  int total_bees = (int)mortal_bees.size() + 1; // +1 for the magical queen
  // total male bees
  int total_male_bees = 0;
  while(!mortal_bees.empty()) {
    if(mortal_bees.top().gender == MALE) total_male_bees++;
    mortal_bees.pop();
  }

  printf("%d %d\n", total_male_bees, total_bees); // +1 for the magical queen
}





namespace algorithms::onlinejudge::maths::bee
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

        std::vector<ull> fib_n(MAX_FIB);
        fib_n[0] = 0;
        fib_n[1] = 1;
        for (int i = 2; i < MAX_FIB; i++) {
          fib_n[i] = fib_n[i - 1] + fib_n[i - 2];
        }

        int years;
        while(scanf("%d", &years) == 1 && years != -1) {
          printf("%llu %llu\n", fib_n[years + 2] - 1, fib_n[years + 3] - 1);
        }
    }
}