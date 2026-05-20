/*
───────────────────────────────────────────────────────────────
🧳 UVa 488 Triangle Wave, https://onlinejudge.org/external/4/488.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



void generateWaves(int amplitude, int frequency) {
  for(int f = 0; f < frequency; ++f) {
    for(int a = 1; a < amplitude; ++a)  {
      std::cout << std::string(a, a + '0') << std::endl;
    }
    std::cout << std::string(amplitude, amplitude + '0') << std::endl;
    for(int a = amplitude - 1; a > 0; --a) {
      std::cout << std::string(a, a + '0') << std::endl;
    }
    if(f < frequency - 1 
       && amplitude > 0) 
      std::cout << std::endl;
  }
}


namespace algorithms::onlinejudge::strings::triangle_wave
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
        std::cin.ignore();
        while(t_cases--) {
          int amplitude, frequency;
          scanf("%d %d", &amplitude, &frequency);
          std::cin.ignore();
          generateWaves(amplitude, frequency);
          if(t_cases) std::cout << std::endl;
        }

    }
}