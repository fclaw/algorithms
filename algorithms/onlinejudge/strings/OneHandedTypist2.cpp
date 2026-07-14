/*
───────────────────────────────────────────────────────────────
🧳 UVa 10393 The One-Handed Typist, https://onlinejudge.org/external/103/10393.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



std::unordered_map<int, std::string> fingers = 
{
    {1, "qaz"},
    {2, "wsx"},
    {3, "edc"},
    {4, "rfvtgb"},
    {5, " "},
    {6, " "},
    {7, "yhnujm"},
    {8, "ik,"},
    {9, "ol."},
    {10, "p;/"}
};



namespace algorithms::onlinejudge::strings::one_handed_typist_2
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
    
        int F, N;
        while(std::cin >> F >> N) {
          int finger;
          std::string forbidden;
          for(int i = 0; i < F; ++i) {
            std::cin >> finger;
            std::string letters = fingers.at(finger);
            forbidden.append(letters);
          }
          int max_length = 0;
          std::string word;
          std::vector<std::string> valid_words;
          // PASS 1: Find the max length and collect all valid words
          for(int i = 0; i < N; ++i) {
            std::cin >> word;
            bool can_typed = true;
            for(char c : word) {
              if(forbidden.find(c) != 
                 std::string::npos) {
                can_typed = false;
                break;
              }
            }
            if(can_typed) {
              valid_words.push_back(word);
              max_length = std::max(max_length, (int)word.length());
            }
          }

          // PASS 2: Insert ONLY the absolute winners into the set!
          std::set<std::string> final_words;
          for (const std::string& w : valid_words) {
            if((int)w.length() == max_length) {
              final_words.insert(w);
            }
          }

          std::cout << final_words.size() << std::endl;
          for(const auto& w : final_words) {
            std::cout << w << std::endl;
          }
        }

    }
}