
/*
───────────────────────────────────────────────────────────────
🧳 UVa 12641 Reodrnreig Lteetrs in Wrods, https://onlinejudge.org/external/126/12641.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using sig_map = std::unordered_map<std::string, std::set<std::string>>;

std::string get_signature(const std::string& word) {
  // A word of length 1, 2, or 3 cannot have its middle scrambled
  // (e.g. "a", "to", "cat" have no middle or only 1 middle char)
  if (word.length() <= 3) {
    return word;
  }
    
  // Safely extract the middle segment using substr
  std::string mid = word.substr(1, word.length() - 2);
  std::sort(mid.begin(), mid.end());
    
  // Reconstruct the signature: First + Sorted Middle + Last
  return word.front() + mid + word.back();
}


namespace algorithms::onlinejudge::strings::reordering_words
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
        std::string line, word;
        std::cin >> t_cases;
        std::cin.ignore();
        while(t_cases--) {
          // read dictionary
          std::getline(std::cin, line);
          std::stringstream ss_dictionary(line);
          sig_map signature_to_words;
          while(ss_dictionary >> word) {
            std::string sig = get_signature(word);
            signature_to_words[sig].insert(word);
          }

          // read sentence
          std::getline(std::cin, line);
          std::stringstream ss_sentence(line);
          bool is_first = true;
          std::string unscrambled_sentence;
          while(ss_sentence >> word) {
            if(is_first) {
              is_first = false;
            } else {
              unscrambled_sentence += " ";
            }
            std::string sig = get_signature(word);
            auto it = signature_to_words.find(sig);
            if(it == signature_to_words.end()) {
              unscrambled_sentence += word;
            } else {
              unscrambled_sentence += *((it->second).begin());
            }
          }
          std::cout << unscrambled_sentence << std::endl;
        }
    }
}