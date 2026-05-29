/*
───────────────────────────────────────────────────────────────
🧳 UVa 444 Encoder and Decoder, https://onlinejudge.org/external/4/444.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




// Global arrays (initialized to 0 by default)
int charToAscii[256] = {0};
char asciiToChar[256] = {0};

void initializeFastMaps() {
    // 1. Map Uppercase A-Z (65-90)
    for (int i = 'A'; i <= 'Z'; ++i) {
        charToAscii[i] = i;
        asciiToChar[i] = (char)i;
    }

    // 2. Map Lowercase a-z (97-122)
    for (int i = 'a'; i <= 'z'; ++i) {
        charToAscii[i] = i;
        asciiToChar[i] = (char)i;
    }

    // 3. Map specific punctuation from the problem table
    // Space, !, ,, ., :, ;, ?
    std::string special = " !,.:;?"; 
    for (char c : special) {
        int code = (unsigned char)c;
        charToAscii[code] = code;
        asciiToChar[code] = c;
    }
}


void backtrack(const std::string& encoded, int index, std::string& currentDecoded, std::string& result, bool& found) {
    if (index >= (int)encoded.size()) {
        result = currentDecoded;
        found = true;
        return;
    }

    // Try to decode 3 digits first (for codes 100-122)
    if (index + 2 < (int)encoded.size() && !found) {
      std::string threeDigits = encoded.substr(index, 3);
      int code = std::stoi(threeDigits);
      if ((bool)asciiToChar[code] && code <= 255) { // Check if it's a valid character
        currentDecoded += asciiToChar[code];
        backtrack(encoded, index + 3, currentDecoded, result, found);
        currentDecoded.pop_back(); // Backtrack
      }
    }
    // Try to decode 2 digits (for codes 32-99)
    if (index + 1 < (int)encoded.size() && !found) {
      std::string twoDigits = encoded.substr(index, 2);
      int code = std::stoi(twoDigits);
      if ((bool)asciiToChar[code]) { // Check if it's a valid character
        currentDecoded += asciiToChar[code];
        backtrack(encoded, index + 2, currentDecoded, result, found);
        currentDecoded.pop_back(); // Backtrack
      }
    }
}


namespace algorithms::onlinejudge::strings::encoder_and_decoder
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

        initializeFastMaps();
        std::string message;
        while(std::getline(std::cin, message)) {
          if(std::isdigit(message.front())) {
            // Decode the message
            // Split the message by spaces and convert each number back to a character
            std::string decoded;
            std::string currentDecoded;
            bool found = false;
            std::reverse(message.begin(), message.end());
            backtrack(message, 0, currentDecoded, decoded, found);
            std::cout << decoded << std::endl;
          } else {
            // Encode the message
            std::string encoded;
            for(char c : message) {
              int asciiCode = charToAscii[(unsigned char)c];
              encoded += std::to_string(asciiCode);
            }
            std::reverse(encoded.begin(), encoded.end());
            std::cout << encoded << std::endl;
          }
        }
    }
}