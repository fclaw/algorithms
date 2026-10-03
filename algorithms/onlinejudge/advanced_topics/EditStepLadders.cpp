/*
───────────────────────────────────────────────────────────────
🧳 UVa 10029 Edit Step Ladders, https://onlinejudge.org/external/100/10029.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




int cache[25005]; // Cache for memoization, initialized to -1


inline auto find_it(const std::vector<std::string>& words, const std::string& target, int start_idx) {
    // Use std::lower_bound to find the first occurrence of 'target' in 'words'
    return std::lower_bound(words.begin() + start_idx, words.end(), target);
}

/**
 * Top-Down DAG Dynamic Programming (Longest Path in a Word Graph)
 *
 * For a given word at 'idx', we explore all valid forward edit steps.
 * A transition from words[idx] -> words[next_idx] is valid IF AND ONLY IF:
 *   1. It is an edit step (Insertion, Deletion, or Substitution).
 *   2. It moves strictly forward alphabetically (next_idx > idx).
 *   3. The generated word actually exists in the dictionary.
 */
int dp(int idx, const std::vector<std::string>& words) {

    // ------------------------------------------------------------------------
    // MEMOIZATION CHECK
    // ------------------------------------------------------------------------
    // Because the dictionary is a DAG, each word's longest forward ladder 
    // is fixed and immutable. Cache hits eliminate exponential recomputation!
    if (cache[idx] != -1) {
        return cache[idx];
    }

    int max_steps = 0;
    std::string word = words[idx];

   // ========================================================================
    // BRANCH 1: ADD (INSERTION)
    // ========================================================================
    // Transformation: word (length L) -> new_word (length L + 1)
    // We can insert a character:
    //   - At the beginning (pos = 0)
    //   - Between any two characters (0 < pos < length)
    //   - At the very end (pos = length) -> notice loop condition (pos <= length)!
    for(int pos = 0; pos <= (int)word.length(); ++pos) {
      for(char c = 'a'; c <= 'z'; ++c) {
        std::string new_word = word;
        new_word.insert(pos, 1, c);
        auto it = find_it(words, new_word, idx);
        if(it != words.end() && 
           *it == new_word) {
          int next_idx = it - words.begin();
          if(next_idx > idx) {
            max_steps = std::max(max_steps, 1 + dp(next_idx, words));
          }
        }
      }
    }

    // ========================================================================
    // BRANCH 2: DELETE (DELETION)
    // ========================================================================
    // Transformation: word (length L) -> new_word (length L - 1)
    // Guard clause: Only attempt deletion if word has at least 2 characters.
    //
    // The "Forward Deletion" Phenomenon:
    // Deleting a letter can make a word alphabetically LARGER if the deleted 
    // letter is smaller than the letter following it (e.g., "afar" -> "far").
    if(word.length() > 1) {
       for (int pos = 0; pos < (int)word.length(); ++pos) {
        std::string new_word = word;
        new_word.erase(pos, 1); // Deletes ONLY 1 character at index pos!
        auto it = find_it(words, new_word, idx);
        if(it != words.end() && 
           *it == new_word) {
          int next_idx = it - words.begin();
          if(next_idx > idx) {
            max_steps = std::max(max_steps, 1 + dp(next_idx, words));
          }
        }
      }
    }

    // ========================================================================
    // BRANCH 3: CHANGE (SUBSTITUTION)
    // ========================================================================
    // Transformation: word (length L) -> new_word (length L)
    // Length remains identical. We substitute one character at index 'pos'
    // with any character from 'a' to 'z'.
    for (int pos = 0; pos < (int)word.length(); ++pos) {
      std::string new_word = word;
      for (char c = 'a'; c <= 'z'; ++c) {
        new_word[pos] = c;
        auto it = find_it(words, new_word, idx);
        if (it != words.end() && 
           *it == new_word) {
          int next_idx = it - words.begin();
          if(next_idx > idx) {
            max_steps = std::max(max_steps, 1 + dp(next_idx, words));
          }
        }
      }
    }

    // ------------------------------------------------------------------------
    // MEMOIZATION STORE
    // ------------------------------------------------------------------------
    // Cache and return the longest ladder starting from words[idx]
    return (cache[idx] = max_steps);
}


namespace algorithms::onlinejudge::advanced_topics::edit_step_ladders
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

        std::vector<std::string> words;
        std::string word;
        while (std::cin >> word) {
          words.push_back(word);
        }

        std::memset(cache, -1, sizeof(cache)); // global cache for memoization, initialized to -1
        int max_steps = 0;
        for(int i = 0; i < (int)words.size(); ++i) {
          int w = dp(i, words);
          max_steps = std::max(max_steps, w);
        }
        std::cout << 1 + max_steps << std::endl;
    }
}