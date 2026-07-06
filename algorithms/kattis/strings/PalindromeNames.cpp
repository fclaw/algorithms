/*
───────────────────────────────────────────────────────────────
🧳  Palindrome Names, https://open.kattis.com/problems/names, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



int min_steps_to_palindrome(const std::string& S) {
  int N = S.length();
  int min_cost = N; // Worst case: append the entire reverse

  for (int L = 0; L < N; ++L) {
    // Calculate num(Suffix)
    int num_changes = 0;
    int left = L, right = N - 1;
    while (left < right) {
      if(S[left++] != S[right--]) 
        num_changes++;
    }

    // Apply your exact formula: num(pal) + L
    min_cost = std::min(min_cost, num_changes + L);
  }

  return min_cost;
}


namespace algorithms::kattis::strings::palindrome_names
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

        std::string name;
        while(std::cin >> name) {
          std::cout << min_steps_to_palindrome(name) << std::endl;
        }
    }
}