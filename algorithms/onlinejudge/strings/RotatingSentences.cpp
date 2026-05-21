/*
───────────────────────────────────────────────────────────────
🧳 UVa 490 Rotating Sentences, https://onlinejudge.org/external/4/490.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vs = std::vector<std::string>;


namespace algorithms::onlinejudge::strings::rotating_sentences
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

        std::string line;
        vs lines;
        int cols = 0, rows = 0;
        while(std::getline(std::cin, line)) {
          lines.push_back(line);
          rows++;
          cols = std::max(cols, (int)line.length());
        }

        std::vector<std::string> 
          words_array(rows, std::string(cols, ' '));
        for(int i = 0; i < rows; ++i) {
          for(int j = 0; j < cols; ++j) {
            if(j < (int)lines[i].length()) {
              words_array[i][j] = lines[i][j];
            }
          }
        }

        std::string output;
        for(int j = 0; j < cols; ++j) {
          for(int i = rows - 1; i >= 0; --i) {
             output += words_array[i][j];
          }
          output += "\n";
        }
        printf("%s", output.c_str()); 
    }
}