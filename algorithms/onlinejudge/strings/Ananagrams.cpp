/*
───────────────────────────────────────────────────────────────
🧳 UVa 156 Ananagrams, https://onlinejudge.org/external/1/156.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::strings::ananagrams
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
        std::set<std::string> dictionary;
        std::unordered_map<std::string, std::string> signature_to_word;
        std::unordered_set<std::string> blacklisted_words;
        while(std::cin >> word && word != "#") {
          std::string sig = word;
          for(char& c : sig) {
            c = std::tolower(c);
          }
          std::sort(sig.begin(), sig.end());
          dictionary.insert(word);
          auto it = signature_to_word.find(sig);
          if(it == signature_to_word.end()) {
            signature_to_word.insert({sig, word});
          } else {
            blacklisted_words.insert(word);
            blacklisted_words.insert(it->second);
          }
        }

        for(auto& word : dictionary) {
          if(blacklisted_words.find(word) == 
             blacklisted_words.end()) {
            std::cout << word << std::endl;
          }
        }
    }
}