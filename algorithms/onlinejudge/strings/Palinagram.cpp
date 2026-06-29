
/*
───────────────────────────────────────────────────────────────
🧳 UVa 12770 Palinagram, https://onlinejudge.org/external/127/12770.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM: UVa 12770 - PALINAGRAM (The "Seed" Paradigm via DAT)
 * ============================================================================
 * THE PROBLEM:
 * Given a string S, we must find the shortest, lexicographically smallest string 
 * of characters we can append to S to allow it to be rearranged into a 
 * palindrome (a "Palinagram").
 * 
 * THE MATHEMATICAL CORE (The Palindrome Rule):
 * 1. A string is a palindrome if and only if at most ONE character has an 
 *    odd frequency. 
 * 2. If we have multiple characters with odd frequencies, they cannot all be 
 *    symmetrical. We must "fix" them by adding characters to make them even.
 * 
 * THE "SEED" PARADIGM (Your Discovery):
 * Any odd-length palindrome is composed of: Left_Half + [SEED] + Right_Half.
 * The "Seed" is the single, unique character allowed to remain odd-frequency.
 * 
 * To make our appended output string lexicographically (alphabetically) 
 * smallest, we want the characters we actually write down to be as small 
 * as possible (e.g., we prefer to append 'a' over 'z').
 * 
 * Therefore, we must select the alphabetically LARGEST odd-frequency character 
 * to act as the "Seed" in the center. Because the seed is not appended, we 
 * "save" ourselves from writing the largest characters, minimizing the output!
 * 
 * THE DIRECT ADDRESSING TABLE (DAT) ADVANTAGE:
 * Instead of using a slow std::map or sorting vectors, we use a 26-integer 
 * array: `int freq[26]`.
 * 
 * This gives us three massive advantages:
 * 1. O(N) Building: We map and count characters in a single linear pass.
 * 2. O(1) Access: Standard direct index memory jumps.
 * 3. Free Sorting: By iterating from index 0 ('a') to 25 ('z'), our collected 
 *    odd-frequency string 'ans' is automatically sorted alphabetically!
 * 
 * THE POP_BACK MECHANISM:
 * Because 'ans' is sorted alphabetically, the "Seed" (the largest character) 
 * is guaranteed to be at the very end of the string. Slicing it off with 
 * `ans.pop_back()` perfectly leaves behind the optimal appended characters!
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




namespace algorithms::onlinejudge::strings::palinagram
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

        std::string partial_anagram;
        while(std::cin >> partial_anagram && 
              partial_anagram != "#") {
          std::vector<std::pair<char, int>> freq;
          for(char c : partial_anagram) {
            auto cmp = [&c](const std::pair<char, int>& p) 
                           { return c == p.first; };
            auto it = std::find_if(freq.begin(), freq.end(), cmp);
            if(it == freq.end()) {
              freq.push_back({c, 1});
            } else { it->second++; }
          }
          
          auto cmp = [](const std::pair<char, int>& lhs, 
                        const std::pair<char, int>& rhs) 
                     { return (lhs.first < rhs.first) || 
                              (lhs.first == rhs.first && 
                               lhs.second > rhs.second); 
                     };
          std::sort(freq.begin(), freq.end(), cmp);  

          std::string ans;
          for(auto& p : freq) {
            if((p.second % 2)) {
              ans.push_back(p.first);
            }
          }
          if(!ans.empty()) ans.pop_back();
          std::cout << ans << std::endl;
        }
    }
}