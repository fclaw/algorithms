/*
───────────────────────────────────────────────────────────────
🧳 UVa 483 Word Scramble, https://onlinejudge.org/external/4/483.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




std::string do_reverse(const std::string& sentence) {
  std::string reversed;
  std::string curr_word;
  for (int i = 0; i < (int)sentence.size(); ++i) {
    if(!std::isspace(sentence[i])) {
      curr_word += sentence[i];
    }
    else {
      std::reverse(curr_word.begin(), curr_word.end());
      reversed += curr_word;
      reversed += sentence[i]; // Add the non-letter character
      curr_word.clear();
    }
  }
  // Handle the last word if there is one
  if (!curr_word.empty()) {
    std::reverse(curr_word.begin(), curr_word.end());
    reversed += curr_word;
  }
  return reversed;
}


namespace algorithms::onlinejudge::strings::word_scramble
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

        std::string sentence;
        while (std::getline(std::cin, sentence)) {
          auto reversed_sentence = do_reverse(sentence);
          std::cout << reversed_sentence << std::endl;
        }
    }
}