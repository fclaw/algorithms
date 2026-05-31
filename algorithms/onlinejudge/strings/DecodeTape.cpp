/*
───────────────────────────────────────────────────────────────
🧳 UVa 10878 Decode the tape, https://onlinejudge.org/external/108/10878.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>
#include "../maths/utility/arithmetics.cpp"


namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

using vs = std::vector<std::string>;

char sprocket_hole = '.';
char tape_hole = 'o';
int exponent = 7; // 2^7 = 128, which is the number of ASCII characters, so we have 7 bits to represent each character on the tape.


namespace algorithms::onlinejudge::strings::decode_tape
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

        vs raw_tape;
        std::string line;
        while(std::getline(std::cin, line)) {
          raw_tape.push_back(line);
        }

        // clear tape of sprocket holes and borders, leaving only the message payload
        raw_tape.pop_back(); // Remove the last line which is just a border
        raw_tape.erase(raw_tape.begin()); // Remove the first line which is just a border
        for(int i = 0; i < (int)raw_tape.size(); ++i) {
          raw_tape[i] = raw_tape[i].substr(1, raw_tape[i].size() - 2); // Remove the first and last character of each line which are just borders
        }

        std::string decoded_message;
        for(const std::string& tape_line : raw_tape) {
          int ascii_value = 0;
          int i = 0;
          for(int j = 0; j < (int)tape_line.size(); ++j) {
            if(tape_line[j] == sprocket_hole) { continue; } // Skip the sprocket hole and move to the next character
            ascii_value += arithmetics::power<int>(2, exponent - i++) * (tape_line[j] == tape_hole ? 1 : 0);
           }
          decoded_message += static_cast<char>(ascii_value);  
        }
        std::cout << decoded_message;
    }
}