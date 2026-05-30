/*
───────────────────────────────────────────────────────────────
🧳 UVa 458 The Decoder, https://onlinejudge.org/external/4/458.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM OVERVIEW: UVa 458 - THE DECODER (Arithmetic Cipher)
 * ============================================================================
 * THE CRUX:
 * The problem describes a "one-for-one character substitution based upon a 
 * single arithmetic manipulation." By performing a "Known-Plaintext Attack" 
 * comparing the Sample Input to the Sample Output, we discover a constant 
 * offset in the ASCII space.
 *
 * MAPPING ANALYSIS:
 * -----------------
 * Encoded Char (ASCII)  |  Decoded Char (ASCII)  |  Difference (Shift)
 * ------------------------------------------------------------------
 * '1' (49)              |  '*' (42)              |  49 - 42 = 7
 * 'J' (74)              |  'C' (67)              |  74 - 67 = 7
 * 'K' (75)              |  'D' (68)              |  75 - 68 = 7
 * ''' (39)              |  ' ' (32) [Space]      |  39 - 32 = 7
 *
 * CONCLUSION:
 * To decode any character, we simply subtract 7 from its ASCII integer value.
 *
 * IMPLEMENTATION STRATEGY:
 * ------------------------
 * 1. STREAM PROCESSING: We use a character-by-character stream approach 
 *    (std::cin.get) to ensure that spaces, tabs, and punctuation are captured.
 * 2. NEWLINE PRESERVATION: The shift only applies to the message payload. 
 *    We must detect '\n' and pass it through untouched to maintain the 
 *    original file structure.
 * 3. COMPLEXITY: O(N) time complexity where N is the total number of 
 *    characters in the file. O(1) space complexity.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




namespace algorithms::onlinejudge::strings::decoder
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

        std::string message;
        while(std::getline(std::cin, message)) {
          for(char c : message) {
            char decodedChar = c - 7; // Shift back by 7 in the ASCII space
            std::cout << decodedChar;
          }
          std::cout << std::endl; // Preserve newlines
        }
    }
}