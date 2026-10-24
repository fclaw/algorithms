/*
───────────────────────────────────────────────────────────────
🧳 UVa 12965 Angry Bids, https://onlinejudge.org/external/129/12965.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"



namespace algorithms::onlinejudge::divide_conquer::angry_bids
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
        stdin_read(t_cases);
        while(t_cases--) {
          int p, c;
          stdin_read(p, c);

          vi producers_bids(p);
          vi consumers_bids(c);
          std::unordered_set<int> candidates_s = {0};
          for(int i = 0; i < p; ++i) {
            stdin_read(producers_bids[i]);
            candidates_s.insert(producers_bids[i]);
          }
          for(int i = 0; i < c; ++i) {
            stdin_read(consumers_bids[i]);
            candidates_s.insert(consumers_bids[i]);
          }

          vi candidates(candidates_s.begin(), candidates_s.end());
          std::sort(candidates.begin(), candidates.end());
          std::sort(producers_bids.begin(), producers_bids.end());
          std::sort(consumers_bids.begin(), consumers_bids.end());

          
          int best_bid = Inf;
          int angry_people = Inf;
          for(int c : candidates) {
            auto p_it = std::upper_bound(producers_bids.begin(), producers_bids.end(), c);
            auto c_it = std::lower_bound(consumers_bids.begin(), consumers_bids.end(), c);
            int angry_consumers = std::distance(consumers_bids.begin(), c_it);
            int angry_producers = std::distance(p_it, producers_bids.end());

            int total_angry_people = angry_producers + angry_consumers;

            if(total_angry_people < angry_people) {
              best_bid = c;
              angry_people = total_angry_people;
            } else if (total_angry_people == angry_people) {  
              if(best_bid > c) { best_bid = c; }
            }
          }
          std::cout << best_bid << " " << angry_people << "\n";
        }
    }
}