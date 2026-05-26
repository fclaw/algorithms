/*
───────────────────────────────────────────────────────────────
🧳 UVa 12364 InBraille, https://onlinejudge.org/external/123/12364.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



// Mapping: Digit -> {Row 1, Row 2, Row 3}
std::map<char, std::vector<std::string>> digit_to_braille = {
    {'1', {"*.", "..", ".."}},
    {'2', {"*.", "*.", ".."}},
    {'3', {"**", "..", ".."}},
    {'4', {"**", ".*", ".."}},
    {'5', {"*.", ".*", ".."}},
    {'6', {"**", "*.", ".."}},
    {'7', {"**", "**", ".."}},
    {'8', {"*.", "**", ".."}},
    {'9', {".*", "*.", ".."}},
    {'0', {".*", "**", ".."}}
};

// Mapping: {Row 1, Row 2, Row 3} -> Digit
std::map<std::vector<std::string>, char> braille_to_digit = {
    {{"*.", "..", ".."}, '1'},
    {{"*.", "*.", ".."}, '2'},
    {{"**", "..", ".."}, '3'},
    {{"**", ".*", ".."}, '4'},
    {{"*.", ".*", ".."}, '5'},
    {{"**", "*.", ".."}, '6'},
    {{"**", "**", ".."}, '7'},
    {{"*.", "**", ".."}, '8'},
    {{".*", "*.", ".."}, '9'},
    {{".*", "**", ".."}, '0'}
};


namespace algorithms::onlinejudge::strings::braille
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

        int digits;
        while(scanf("%d\n", &digits) && digits != 0) {
          char mode;
          scanf("%c\n", &mode);
          if(mode == 'S') {
            std::string line;
            std::getline(std::cin, line); // consume the newline after the operation character
            std::vector<std::vector<std::string>> braille_rows;
            for(char c : line) {
              braille_rows.push_back(digit_to_braille[c]);
            }
            for(int i = 0; i < 3; ++i) {
              for(int j = 0; j < (int)braille_rows.size(); ++j) {
                printf("%s", braille_rows[j][i].c_str());
                if(j != (int)braille_rows.size() - 1) {
                    printf(" ");
                }
              }
              printf("\n");
            }
          } else if(mode == 'B') {
            std::vector<std::string> row1(digits), row2(digits), row3(digits);
            for(int i = 0; i < 3; ++i) {
              for(int j = 0; j < digits; ++j) {
                char c1, c2;
                scanf(" %c%c", &c1, &c2);
                if(i == 0) {
                  row1[j] = std::string{c1, c2};
                } else if(i == 1) {
                  row2[j] = std::string{c1, c2};
                } else {
                  row3[j] = std::string{c1, c2};
                }
              }
            }
            for(int j = 0; j < digits; ++j) {
              std::vector<std::string> braille_char = {row1[j], row2[j], row3[j]};
              printf("%c", braille_to_digit[braille_char]);
            }
            printf("\n");
          }
        }

    }
}