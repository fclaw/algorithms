/*
───────────────────────────────────────────────────────────────
🧳 UVa 12543 Longest Word, https://onlinejudge.org/external/125/12543.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




const std::set<char> alphabet = 
  {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 
   'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
   'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 
   'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 
   'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 
   'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 
   'W', 'X', 'Y', 'Z', '-' };


namespace algorithms::onlinejudge::strings::longest_word
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

        std::string line;
        std::string longest_word;
        int longest_word_len = 0;
        std::string curr_word = {};
        int curr_word_len = 0;
        while(std::getline(std::cin, line)) {
          if(line.empty()) continue;
          for(char c : line) {
            if(alphabet.count(c)) {
              curr_word += c;
              curr_word_len++;
            } else {
              if(curr_word == "E-N-D") {
                goto finished;
              }
              if(curr_word_len > longest_word_len) {
                longest_word = curr_word;
                longest_word_len = curr_word_len;
              }
              curr_word = {};
              curr_word_len = 0;
            }
          }
        }
        std::transform(longest_word.begin(), longest_word.end(), longest_word.begin(), ::tolower);
        finished: std::cout << longest_word << std::endl;
    }
}