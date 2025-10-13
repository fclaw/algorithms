/*
───────────────────────────────────────────────────────────────
🧳  UVa 10491 Cows and Cars, https://onlinejudge.org/external/104/10491.pdf, rt: s
    2 ways: either pick a cow first, then switch to a car; or pick a car first, and then switch to another car
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


namespace algorithms::onlinejudge::maths::cows_and_cars
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

        int cows, cars, shows;
        while(scanf("%d %d %d", &cows, &cars, &shows) == 3) {
          // pick_cow
          double pick_cow_p = (double)cows / (cows + cars);
          double switch_car_p = (double)cars / (cows + cars - shows - 1); // 1 accounts for the door which is initially chosen
          double total_cow_first = pick_cow_p * switch_car_p;
          // pick car
          double pick_car_p = (double)cars / (cows + cars);
          double switch_cow_p = (double)(cars - 1) / (cows + cars - shows - 1);
          double total_car_first = pick_car_p * switch_cow_p;
          printf("%.5f\n", total_cow_first + total_car_first);
        }
    }
}