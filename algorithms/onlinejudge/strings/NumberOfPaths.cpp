/*
───────────────────────────────────────────────────────────────
🧳 UVa 10854 Number of Paths, https://onlinejudge.org/external/108/10854.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



enum Token { IF, ELSE, END_IF, S, ENDPROGRAM };

using v_token = std::vector<Token>;

std::istream& operator >> (std::istream& is, Token& t) {
  std::string s;
  is >> s;
  if(s == "IF") t = IF;
  else if(s == "ELSE") t = ELSE;
  else if(s == "END_IF") t = END_IF;
  else if(s == "S") t = S;
  else if(s == "ENDPROGRAM") t = ENDPROGRAM;
  return is;
}


// The recursive descent parser.
// It takes the token stream and the current position (by reference).
// It returns the number of paths in the block it just parsed.
int count_paths(int& i, v_token& tokens) {
  int paths_in_current_sequence = 1;

  while (i < (int)tokens.size()) {
    Token t = tokens[i];

    if (t == S) {
      // 'S' is a sequential statement, it doesn't change the path count. Move past it.
      i++;
    } else if (t == IF) {
      // --- We've hit a parallel branching structure ---
      i++; // Consume the 'IF' token

      // Recursively calculate paths in the 'if' branch
      int if_paths = count_paths(i, tokens);

      // The recursive call above will stop when it hits the 'ELSE' token.
      i++; // Consume the 'ELSE' token

      // Recursively calculate paths in the 'else' branch
      int else_paths = count_paths(i, tokens);
            
      // The recursive call above will stop at the 'END_IF'.
      i++; // Consume the 'END_IF' token

      // The total paths for this IF-ELSE block is the SUM of the branch paths.
      int parallel_paths = if_paths + else_paths;
            
      // These parallel paths combine with the current sequence by MULTIPLICATION.
      paths_in_current_sequence *= parallel_paths;

    } else if (t == ELSE || t == END_IF) {
      // If we are in the main loop of a block and hit an ELSE or END_IF,
      // it means this block is finished. Break the loop and return.
      break;
    }
  }
  return paths_in_current_sequence;
}


namespace algorithms::onlinejudge::strings::number_of_paths
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
        scanf("%d", &t_cases);
        while(t_cases--) {
          Token token;
          v_token tokens;
          while(while_read(token)) {
            if(token == ENDPROGRAM) break;
            tokens.push_back(token);
          }
          int i = 0;
          printf("%d\n", count_paths(i, tokens));
        }
    }
}