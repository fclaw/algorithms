/*
───────────────────────────────────────────────────────────────
🧳 UVa 642 Word Amalgamation, https://onlinejudge.org/external/6/642.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



std::string sentinel = "XXXXXX";


namespace algorithms::onlinejudge::strings::word_amalgamation
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

       
        std::string word, sig, anagram;
        std::unordered_map<std::string, std::set<std::string>> signature_to_words;
        // read signature_to_words
        while(std::cin >> word && 
              word != sentinel) {
          sig = word;
          std::sort(sig.begin(), sig.end());
          auto it = signature_to_words.find(sig);
          if(it == signature_to_words.end()) {
           signature_to_words[sig] = {word}; 
          } else {
            signature_to_words[sig].insert(word);
          }
        }

        // read anagrams
        while(std::cin >> anagram && 
              anagram != sentinel) {
          sig = anagram;
          std::sort(sig.begin(), sig.end());
          auto it = signature_to_words.find(sig);
          if(it == signature_to_words.end()) {
            printf("NOT A VALID WORD\n******\n");
          } else {
            for(auto& word : it->second) {
              printf("%s\n", word.c_str());
            }
            printf("******\n");
          }
        }
    }
}