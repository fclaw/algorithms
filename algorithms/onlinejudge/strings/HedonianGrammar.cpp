/*
───────────────────────────────────────────────────────────────
🧳 UVa 271 Simply Syntax, https://onlinejudge.org/external/2/271.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



// Helper function to check if a char is in a given category.
// More efficient than std::set for single characters.
bool is_atomic(char c) {
  return c >= 'p' && c <= 'z';
}

bool is_unary(char c) {
  return c == 'N';
}

bool is_binary(char c) {
  return c == 'C' || c == 'D' || c == 'E' || c == 'I';
}


size_t is_well_formed(const std::string& s, size_t pos) {
  // Boundary check to prevent reading past the end of the string.
  if(pos >= s.length()) {
    return std::string::npos;
  }

  if(is_atomic(s[pos])) {
    return pos;
  }
  
  if(is_unary(s[pos])) return is_well_formed(s, pos + 1);

  if(is_binary(s[pos])) {
    size_t left_end_pos = is_well_formed(s, pos + 1);
    if(left_end_pos == std::string::npos) return std::string::npos;
    size_t right_end_pos = is_well_formed(s, left_end_pos + 1);
    if(right_end_pos == std::string::npos) return std::string::npos;
    return right_end_pos;
  }

  return std::string::npos;
}


namespace algorithms::onlinejudge::strings::hedonian_grammar
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
        while(std::getline(std::cin, sentence)) {
          size_t final_pos = is_well_formed(sentence, 0);
          printf("%s\n", final_pos == sentence.size() - 1 ? "YES" : "NO");
        }
    }
}