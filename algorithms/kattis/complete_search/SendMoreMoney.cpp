/*
───────────────────────────────────────────────────────────────
🧳 Send More Money, https://open.kattis.com/problems/sendmoremoney,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;
// using vi = std::vector<int>;
// using vvi = std::vector<vi>;
using vs = std::vector<std::string>;


struct Letter
{
    char val;
    bool is_leading;
    bool is_addend;
    // Sorts: is_addend == true first, then letter alphabetically
    bool operator < (const Letter& other) const {
      // Negating 'is_addend' (!is_addend) ensures 'true' (0) comes before 'false' (1)
      return std::make_tuple(!is_addend, val) < 
             std::make_tuple(!other.is_addend, other.val);
    }
};

ll coeff[256]; // Stores the net multiplier for each character

void precompute_coefficients(const std::vector<std::string>& words) {
  std::memset(coeff, 0, sizeof(coeff));
  int N = words.size();

  // 1. Addend words (0 to N-2) contribute +10^j
  for(int i = 0; i < N - 1; ++i) {
    ll p10 = 1;
    for (int j = (int)words[i].length() - 1; j >= 0; --j) {
      coeff[(unsigned char)words[i][j]] += p10;
      p10 *= 10;
    }
  }

  // 2. Result word (N-1) contributes -10^j
  ll p10 = 1;
  for(int j = (int)words[N - 1].length() - 1; j >= 0; --j) {
    coeff[(unsigned char)words[N - 1][j]] -= p10;
    p10 *= 10;
  }
}


bool verify(const std::unordered_map<char, int>& assigned) {
  ll total_sum = 0;
  for(auto& t : assigned) {
    char letter = t.first;
    int d = t.second;
    total_sum += (long long)d * coeff[(unsigned char)letter];
  }
  return total_sum == 0;
}

auto find_letter_it(std::vector<Letter>& letters, char v) {
  return std::find_if(letters.begin(), letters.end(), [v](Letter o) { return v == o.val; });
}


void backtrack(int pos, const std::vector<Letter>& letters, std::unordered_map<char, int>& assigned, std::unordered_map<char, int>& sol, bool& is_found, int used) {
  if(pos == (int)letters.size()) {
    if(verify(assigned)) {
      sol = assigned;
      is_found = true;
    }
    return;
  }

  Letter letter = letters[pos];
  for(int d = 0; d <= 9; d++) {
    if((letter.is_leading && d == 0) || 
       (used & (1 << d))) {
      continue;
    }

    int old = assigned[letter.val];
    assigned[letter.val] = d;
    backtrack(pos + 1, letters, assigned, sol, is_found, used | (1 << d));
    assigned[letter.val] = old;
    if(is_found) {
      return;
    }
  }
}

std::string find_solution(const std::vector<Letter>& letters, const std::string& origin) {

  std::unordered_map<char, int> assigned;
  std::unordered_map<char, int> sol;
  bool is_found = false;
  backtrack(0, letters, assigned, sol, is_found, 0);
   
  std::string ans;
  if(!is_found) {
    ans = "impossible";
  } else {
    ans = origin;
    for(char& oc : ans) {
      for(auto& o : sol) {
        if(oc == o.first) {
          oc = (char)(o.second + '0');
        }
      }
    }
  }
  return ans;
}


namespace algorithms::kattis::complete_search::send_me_more_money
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

        std::string origin;
        while(std::getline(std::cin, origin)) {

          // Strip trailing '\r' and spaces
          while (!origin.empty() && 
                 (origin.back() == '\r' || 
                  origin.back() == ' ')) {
            origin.pop_back();
          }
         if (origin.empty()) continue;

          std::vector<std::string> words;

          size_t pos_plus = origin.find('+');            
          std::string first_addend = origin.substr(0, pos_plus);
          words.push_back(first_addend);   
          size_t pos_eq = origin.find('=');
          size_t pos_end = pos_eq - pos_plus - 1;
          std::string second_addend = origin.substr(pos_plus + 1, pos_end);
          words.push_back(second_addend);  
          std::string resultant = origin.substr(pos_eq + 1);
          words.push_back(resultant);

          std::vector<Letter> letters;
          for(char v : first_addend) {
            auto it = find_letter_it(letters, v);
            if(it == letters.end()) {
              letters.push_back({v, v == first_addend.front(), true});
            } else { 
              bool old = it->is_leading;
              it->is_leading = old || (v == first_addend.front());
            }
          }

          for(char v : second_addend) {
            auto it = find_letter_it(letters, v);
            if(it == letters.end()) {
              letters.push_back({v, v == second_addend.front(), true});
            } else {
              bool old = it->is_leading;
              it->is_leading = old || (v == second_addend.front());
            }
          }

          for(char v : resultant) {
            auto it = find_letter_it(letters, v);
            if(it == letters.end()) {
              letters.push_back({v, v == resultant.front(), false});
            } else {
               bool old = it->is_leading;
              it->is_leading = old || (v == resultant.front());
            }
          }
          std::sort(letters.begin(), letters.end());
          precompute_coefficients(words);
          printf("%s\n", find_solution(letters, origin).c_str());
        }
    }
}