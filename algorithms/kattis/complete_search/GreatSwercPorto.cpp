/*
───────────────────────────────────────────────────────────────
🧳 GREAT + SWERC = PORTO, https://open.kattis.com/problems/greatswercporto, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vs = std::vector<std::string>;


const int MAX = 26;

struct Letter
{
    bool is_leading;
    bool is_on;
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

int count_solutions(int pos, const std::vector<Letter>& letters, std::unordered_map<char, int>& assigned, int used) {


  if(pos == (int)letters.size()) {
    if(verify(assigned)) {
      return 1;
    } else {
      return 0;
    }
  }

  Letter letter = letters[pos];
  int ways = 0;
  if(!letter.is_on) {
    ways = count_solutions(pos + 1, letters, assigned, used);
  } else {

    for(int d = 0; d <= 9; d++) {
      if((letter.is_leading && d == 0) || 
         (used & (1 << d))) {
        continue;
      }

      char idx = (char)(pos + 'A');
      int old = assigned[idx];
      assigned[idx] = d;
      ways += count_solutions(pos + 1, letters, assigned, used | (1 << d));
      assigned[idx] = old;
    }
  }

  return ways;
}


namespace algorithms::kattis::complete_search::great_swerc_porto
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

        int N;
        while(std::cin >> N) {
          vs words(N);
          std::vector<Letter> letters(MAX);
          for(int i = 0; i < MAX; ++i) {
            letters[i].is_on = false;
          }
          for(int i = 0; i < N; ++i) {
            std::cin >> words[i];
            auto word = words[i];
            for(int p = 0; p < (int)word.size(); ++p) {
              char ch = word[p];
              int idx = (int)(ch - 65);
              letters[idx].is_on = true;
              letters[idx].is_leading = letters[idx].is_leading || (p == 0);
            }
          }

          precompute_coefficients(words);
          std::unordered_map<char, int> assigned;
          printf("%d\n", count_solutions(0, letters, assigned, 0));
        }
    }
}