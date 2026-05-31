/*
───────────────────────────────────────────────────────────────
🧳 UVa 11278 One-Handed Typist, https://onlinejudge.org/external/112/11278.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


// The global lookup table
char translator[256];

void initialize() {
    // 1. Initialize everything to map to itself (default)
    for (int i = 0; i < 256; ++i) translator[i] = (char)i;

    // 2. Define the QWERTY layout
    std::string Q = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./"
               "~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ";

    // 3. Define the Dvorak layout
    std::string D = "`123qjlmfp/[]456.orsuyb;=\\789aehtdck-0zx,inwvg'"
               "~!@#QJLMFP?{}$%^>ORSUYB:+|&*(AEHTDCK_)ZX<INWVG\" ";

    // 4. Populate the translator
    for (size_t i = 0; i < Q.length(); ++i) {
        translator[(unsigned char)Q[i]] = D[i];
    }
}



namespace algorithms::onlinejudge::strings::one_handed_typist
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
        
        initialize(); // Set up the translator mapping
        std::string querty_message;
        while(std::getline(std::cin, querty_message)) {
          std::string dvorak_message;
          for(char c : querty_message) {
            dvorak_message += translator[(unsigned char)c];
          }
          std::cout << dvorak_message << std::endl;
        }
    }
}