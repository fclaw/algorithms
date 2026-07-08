/*
───────────────────────────────────────────────────────────────
🧳 UVa 11697 Playfair Cipher, https://onlinejudge.org/external/116/11697.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vs = std::vector<std::string>;

std::string alphabet = "abcdefghijklmnoprstuvwxyz"; // No 'q'

int D = 5;

using key_map = std::unordered_map<char, std::pair<int, int>>;


std::pair<key_map, vs> build_encryption_key(const std::string& key_phrase) {
  
    std::unordered_set<char> used;
    key_map key;
    vs search_table(D, std::string(D, ' '));

    int idx = 0;
    for(char c : key_phrase) {
      if(!std::isspace(c) &&
         c != 'q' &&
         !used.count(c)) {
        int C = idx % D;
        int R = idx / D;
        key[c] = {R, C};
        search_table[R][C] = c;
        used.insert(c);
        ++idx;
      }
    }

    for(char c : alphabet) {
      if(key_phrase.find(c) ==
         std::string::npos) {
        int C = idx % D;
        int R = idx / D;
        key[c] = {R, C};
        search_table[R][C] = c;
        ++idx;
      }
    }

    return {key, search_table};
}

bool is_the_same_row(const key_map& key, char f_char, char s_char) {
  return key.at(f_char).first == key.at(s_char).first;
}

bool is_the_same_column(const key_map& key, char f_char, char s_char) {
  return key.at(f_char).second == key.at(s_char).second;
}



std::string encrypt(const std::string& msg, const key_map& key, const vs& search_table) {
  std::string encrypted_msg;

  // STEP 1: Strip all spaces and 'q's first to make the string "pure"
  std::string clean_msg = "";
  for (char c : msg) {
    if (!std::isspace(c) && c != 'q') {
      clean_msg += c;
    }
  }

  // STEP 2: Safe pairing on the clean string
  std::vector<std::pair<char, char>> pairs;  
  int i = 0;
  while(i < (int)clean_msg.size()) {
    char first = clean_msg[i];
    char second = '\0';
        
    if (i + 1 < (int)clean_msg.size()) {
      second = clean_msg[i + 1];
    }

    if (second == '\0') {
      // Odd length trailing element
      pairs.push_back({first, 'x'});
      i += 1;
    } else if (first == second) {
      // Double letter mismatch: split with 'x'
      pairs.push_back({first, 'x'});
      i += 1; // Only consume the first char
    } else {
      // Standard valid pair
      pairs.push_back({first, second});
      i += 2; // Consume both
    }
  }
  
  for(auto p : pairs) {
    if(is_the_same_row(key, p.first, p.second)) {
      int row = key.at(p.first).first;
      int f_col = (key.at(p.first).second + 1) % D;
      int s_col = (key.at(p.second).second + 1) % D;
      encrypted_msg.push_back(search_table[row][f_col]);
      encrypted_msg.push_back(search_table[row][s_col]);
    } else if (is_the_same_column(key, p.first, p.second)) {
      int col = key.at(p.first).second;
      int f_row = (key.at(p.first).first + 1) % D;
      int s_row = (key.at(p.second).first + 1) % D;
      encrypted_msg.push_back(search_table[f_row][col]);
      encrypted_msg.push_back(search_table[s_row][col]);
    } else {
      // 1. Get the row and column of the two mismatched characters
      int r1 = key.at(p.first).first;
      int c1 = key.at(p.first).second;
      
      int r2 = key.at(p.second).first;
      int c2 = key.at(p.second).second;

      // 2. Swapping the columns:
      // - First char gets (row1, col2)
      // - Second char gets (row2, col1)
      encrypted_msg.push_back(search_table[r1][c2]);
      encrypted_msg.push_back(search_table[r2][c1]);
    }
  }



  std::transform(encrypted_msg.begin(), encrypted_msg.end(), encrypted_msg.begin(), ::toupper);
  return encrypted_msg;
}


namespace algorithms::onlinejudge::strings::playfair_cipher
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
        std::cin >> t_cases;
        std::cin.ignore();
        while(t_cases--) {
          std::string key_phrase;
          std::string msg;
          std::getline(std::cin, key_phrase);
          std::getline(std::cin, msg);

          auto [key, search_table] = build_encryption_key(key_phrase);
          std::cout << encrypt(msg, key, search_table) << std::endl;
        }

    }
}