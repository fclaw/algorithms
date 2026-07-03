/*
───────────────────────────────────────────────────────────────
🧳 UVa 353 Pesky Palindromes, https://onlinejudge.org/external/3/353.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;


int is_palindrome(const std::string& str, int l, int r, vvi& cache) {
  
  if(l == r) return 1;
  if(l + 1 == r) 
    return str[l] == str[r];

  if(~cache[l][r]) {
    return cache[l][r];
  }
     
  return (cache[l][r] = str[l] == str[r] && is_palindrome(str, l + 1, r - 1, cache));
}


int count_unique_palindromes(const std::string& str) {
  
   vvi cache(str.size(), vi(str.size(), -1));
   std::unordered_set<std::string> unique_palindromes;

   int counter = 0;
   for(int i = 0; i < (int)str.size(); ++i) {
     for(int j = i; j < (int)str.size(); ++j) {
       auto substr = str.substr(i, j - i + 1);
       if(is_palindrome(str, i, j, cache) && 
          unique_palindromes.find(substr) == 
          unique_palindromes.end()) {
         unique_palindromes.insert(substr);
         ++counter;
       }
     }
   }
   

   return counter;
}


namespace algorithms::onlinejudge::strings::pesky_palindromes
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

        std::string str;
        while(std::cin >> str) {
          printf("The string '%s' contains %d palindromes.\n", str.c_str(), count_unique_palindromes(str));
        }
    }
}