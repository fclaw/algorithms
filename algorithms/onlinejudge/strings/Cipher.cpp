/*
───────────────────────────────────────────────────────────────
🧳 UVa 306 Cipher, https://onlinejudge.org/external/3/306.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;

vi computeKthMapping(const vi& permutation, int k) {

  vi mapping(permutation.size());
  for (int i = 0; i < (int)permutation.size(); ++i) {
    vi cycle;
    int first = i;
    int curr = i;
    while(permutation[curr] - 1 != first) {
      cycle.push_back(curr);
      curr = permutation[curr] - 1;
    }
    cycle.push_back(curr); // Add the last element to complete the cycle

    int cycle_length = cycle.size();
    int new_pos_in_cycle = k % cycle_length;

    mapping[i] = cycle[new_pos_in_cycle];
  }

  return mapping;
}


std::string encode(const std::string& line, const vi& permutation, int k) {
  /**
   * Computes a mapping where each index i represents the original position
   * of a character, and the value represents its destination index after 
   * applying the permutation k times. 
  */
  vi targetIndices = computeKthMapping(permutation, k);
  std::string encoded(permutation.size(), ' '); // Initialize with spaces
  for (int i = 0; i < (int)line.size(); ++i) {
    encoded[targetIndices[i]] = line[i];
  }
  return encoded;
}

namespace algorithms::onlinejudge::strings::cipher
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
        while(scanf("%d\n", &N) && N) {
          // Read the permutation
          vi permutation(N);
          for(int i = 0; i < N; i++) {
            scanf("%d", &permutation[i]);
          }
          int k;
          while(scanf("%d", &k) && k) {
            // Consume the newline/space left over from the last numeric read
            std::cin.ignore();
            std::string message;
            std::getline(std::cin, message);
            std::string ciphered = encode(message, permutation, k);
            printf("%s\n", ciphered.c_str());
          }
          printf("\n");
        }
    }
}