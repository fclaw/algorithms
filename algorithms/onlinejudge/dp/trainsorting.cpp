/*
  Problem: 11456 - Trainsorting

  Objective:
  -----------
  Given a sequence of train cars, each with a distinct weight, determine the maximum number of cars
  that can be arranged into a valid train configuration. The train must be constructed such that:
    - Heavier cars are placed toward the front,
    - Lighter cars are placed toward the back,
    - All cars must form a strictly decreasing sequence overall.

  Insight:
  --------
  For any car at index `i` (acting as the pivot), we aim to:
    - Add heavier cars in decreasing order **before** it.
    - Add lighter cars in decreasing order **after** it.

  To make the logic easier to process with forward traversal, the input array is **reversed**.
  This means:
    - dp_before[i] calculates the **Longest Decreasing Subsequence (LDS)** ending at `i` (cars before pivot).
    - dp_after[i]  calculates the **Longest Increasing Subsequence (LIS)** ending at `i` (cars after pivot),
      because after reversing, smaller cars appear later in the original sequence.

  The total number of cars we can include with car `i` as the pivot is:
      dp_before[i] + dp_after[i] - 1

  The `-1` avoids double-counting the pivot car.

  Time Complexity: O(n^2), which is acceptable for n ≤ 2000.
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>





typedef std::vector<int> vi;



namespace algorithms::onlinejudge::dp::trainsorting
{
    /** https://onlinejudge.org/external/114/11456.pdf */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        int tc;
        std::cin >> tc;
        while(tc--)
        {
             int n;
             std::cin >> n;
             vi cars(n);
             loop(n, [&cars](int i) { std::cin >> cars[i]; });

             std::reverse(cars.begin(), cars.end()); // reverse for the forward shifting on indices

             vi dp_before(n, 1); // cars added before
             vi dp_after(n, 1); // cars added after

             for(int i = 0; i < n; ++i)
               for(int j = i - 1; j >= 0; --j)
                 if (cars[i] > cars[j] && 
                     dp_after[i] < 1 + dp_after[j])
                   dp_after[i] = 1 + dp_after[j]; // goes after i
                 else if(cars[i] < cars[j] &&
                         dp_before[i] < 1 + dp_before[j]) // goes before i
                   dp_before[i] = 1 + dp_before[j];

             int max_cars = 0;
             for(int i = 0; i < n; ++i)
               max_cars = std::max(max_cars, dp_before[i] + dp_after[i] - 1);
             std::cout << max_cars << std::endl;
        }
    }
}