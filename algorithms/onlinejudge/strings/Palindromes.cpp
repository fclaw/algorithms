/*
───────────────────────────────────────────────────────────────
🧳 UVa 401 Palindromes, https://onlinejudge.org/external/4/401.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




std::unordered_map<char, char> mirror;

void initialize_mirror() {
    mirror['A'] = 'A'; mirror['E'] = '3'; mirror['H'] = 'H'; mirror['I'] = 'I'; 
    mirror['J'] = 'L'; mirror['L'] = 'J'; mirror['M'] = 'M'; mirror['O'] = 'O'; 
    mirror['S'] = '2'; mirror['T'] = 'T'; mirror['U'] = 'U'; mirror['V'] = 'V'; 
    mirror['W'] = 'W'; mirror['X'] = 'X'; mirror['Y'] = 'Y'; mirror['Z'] = '5'; 
    mirror['1'] = '1'; mirror['2'] = 'S'; mirror['3'] = 'E'; mirror['5'] = 'Z'; 
    mirror['8'] = '8';
}


void check_for_palindrome(const std::string& str, bool& is_palindrome, bool& is_mirrored) {

    auto lptr = str.begin();
    auto rptr = --str.end();
    while(lptr <= rptr) {
      if(!is_palindrome && 
         !is_mirrored) {
        break;  
      }

      // palindrome
      if(is_palindrome && *lptr != *rptr) {
        is_palindrome = false;
      }

      // mirror
      if(is_mirrored && 
         (*lptr != mirror[*rptr] || 
          *rptr != mirror[*lptr])) {
        is_mirrored = false;
      }
      ++lptr; --rptr;
    }

}

namespace algorithms::onlinejudge::strings::palindromes
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

        initialize_mirror();
        std::string str;
        while(std::cin >> str) {
          bool is_palindrome = true;
          bool is_mirrored = true;
          check_for_palindrome(str, is_palindrome, is_mirrored);
          std::string ans = str;
          if(is_palindrome && 
             is_mirrored) {
            ans += " -- is a mirrored palindrome.";
          } else if (!is_palindrome && 
                     is_mirrored) {
            ans += " -- is a mirrored string."; 
          } else if (is_palindrome && 
                     !is_mirrored) {
            ans += " -- is a regular palindrome.";
          } else {
            ans += " -- is not a palindrome.";
          }
          std::cout << ans << std::endl << std::endl;
        }
    }
}