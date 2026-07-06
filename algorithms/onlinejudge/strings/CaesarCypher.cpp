/*
───────────────────────────────────────────────────────────────
🧳 UVa 554 Caesar Cypher, https://onlinejudge.org/external/5/554.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



std::string alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";


char apply_shift(char c, int k) {
  int val = alphabet.find(c);
  // 1. Apply the shift and handle the modulo
  // We do (val + k) % 26.
  int shifted_val = (val + k) % 27;

  // 2. Handle Negative Shifts (e.g., if k was negative, like -3)
  if (shifted_val < 0) {
    shifted_val += 27;
  }
  
  // 3. Convert back to the original ASCII range
  return alphabet[shifted_val];
}


std::string decrypt(const std::unordered_set<std::string>& dictionary, const std::string& msg) {
      
  std::vector<std::string> candidates;
  for(int k = 1; k <= 26; ++k) {
    std::string candidate = msg;
    for(char& c : candidate) {
       c = apply_shift(c, k);
    }
    candidates.push_back(candidate);
  }

  bool found = false;
  std::string ans;
  for(auto& candidate : candidates) {
    std::stringstream ss(candidate);
    std::string word;
    while(ss >> word) {
      if(dictionary.count(word)) {
        found = true;
        ans = candidate;
      }
    }
    if(found) break;
  } 

  return ans;

}


void printWordWrapped(const std::string& decrypted_text) {
    std::stringstream ss(decrypted_text);
    std::string word;
    
    int current_line_len = 0;
    bool first_on_line = true;

    while (ss >> word) {
        // Calculate how long the line would be if we added this word
        // (including the 1 space separator if it's not the first word on the line)
        int space_needed = first_on_line ? 0 : 1;
        int projected_len = current_line_len + space_needed + word.length();

        if (projected_len > 60) {
            // Adding this word would exceed 60 characters.
            // Move to a new line!
            std::cout << "\n";
            current_line_len = 0;
            first_on_line = true;
        }

        // Print the space separator if we are in the middle of a line
        if (!first_on_line) {
            std::cout << " ";
            current_line_len++;
        }

        // Print the word
        std::cout << word;
        current_line_len += word.length();
        first_on_line = false;
    }
    
    // Always print a final newline to close the output file cleanly
    std::cout << "\n"; 
}


namespace algorithms::onlinejudge::strings::ceasar_cypher
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

        std::string word;
        std::unordered_set<std::string> dictionary;
        while(std::cin >> word && word != "#") {
          dictionary.insert(word);
        }

        std::cin.ignore();
        std::string encrypted_message;
        while(std::getline(std::cin, encrypted_message)) {
          printWordWrapped(decrypt(dictionary, encrypted_message)); 
        }
    }
}