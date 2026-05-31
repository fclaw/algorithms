/*
───────────────────────────────────────────────────────────────
🧳 UVa 10896 Known Plaintext Attack, https://onlinejudge.org/external/108/10896.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>
#include <algorithm>


/**
 * ============================================================================
 * FUNCTION: tryCandidate
 * ============================================================================
 * Checks if a specific Caesar key transforms the 'decoded' word into the 
 * 'encoded' token.
 * 
 * THE WRAP-AROUND LOGIC:
 * Instead of normalizing to a 0-25 index, this uses raw ASCII boundaries:
 * 1. If (char + key) <= 122 ('z'): No wrap needed.
 * 2. If (char + key) > 122: 
 *      (Sum % 122) maps the overflow to a small integer (1, 2, 3...).
 *      Adding 96 ('a' - 1) translates that integer back into the lowercase 
 *      ASCII range starting at 'a'.
 * 
 * NOTE: This "Manual Wrap" is valid for keys 0-25, but the standard 
 * algebraic approach `(c - 'a' + k) % 26 + 'a'` is generally safer 
 * for larger keys or multi-lap shifts.
 * ============================================================================
 */
bool tryCandidate(const std::string& encoded, const std::string& decoded, int key) {  
  for(int i = 0; i < (int)encoded.size(); ++i) {
    int ascii_val = (int)decoded[i] + key > 122 ? ((int)decoded[i] + key) % 122 + 96 : (int)decoded[i] + key; // Wrap around the ASCII values to stay within the lowercase letters range
    char candidate_char = static_cast<char>(ascii_val);
    if(encoded[i] != candidate_char) {
      return false;
    }
  }
  return true;
}


namespace algorithms::onlinejudge::strings::plaintext_attack
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
        scanf("%d\n", &t_cases);
        while(t_cases--) {
          std::string encoded_message, decoded_piece;
          std::getline(std::cin, encoded_message);
          std::getline(std::cin, decoded_piece);
          std::stringstream ss(encoded_message);

          std::string token;
          std::string keys;
          while(ss >> token) {
            if(token.length() ==
               decoded_piece.length()) {
              for(int key = 0; key < 26; ++key) {
                if(tryCandidate(token, decoded_piece, key)) {
                  keys += static_cast<char>(key + 97);
                }
              }
            }
          }
          std::sort(keys.begin(), keys.end());
          std::cout << keys << std::endl;
        }
    }
}