/*
───────────────────────────────────────────────────────────────
🧳 UVa 473 Raucous Rockers, https://onlinejudge.org/external/4/473.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;


int dp(int idx, int disk_time_so_far, int disk_time, int disk_n, const vi& songs, vvvi& cache) {
    // Base Case: No more songs or no more disks left
    if (idx == (int)songs.size() || disk_n == 0) {
        return 0;
    }

    if (~cache[idx][disk_n][disk_time_so_far]) {
        return cache[idx][disk_n][disk_time_so_far];
    }

    // Choice 1: Skip the current song
    int best = dp(idx + 1, disk_time_so_far, disk_time, disk_n, songs, cache);

    // Choice 2: Put on the CURRENT disk (use <=, not <)
    if (disk_time_so_far + songs[idx] <= disk_time) {
        best = std::max(best, 1 + dp(idx + 1, disk_time_so_far + songs[idx], disk_time, disk_n, songs, cache));
    }

    // Choice 3: Open a NEW disk (if we have another disk available)
    if (disk_n > 1 && songs[idx] <= disk_time) {
        best = std::max(best, 1 + dp(idx + 1, songs[idx], disk_time, disk_n - 1, songs, cache));
    }

    return (cache[idx][disk_n][disk_time_so_far] = best);
}


int get_max_songs(const vi& songs, int disk_time, int disk_n) {
  vvvi cache(songs.size() + 5, vvi(disk_n + 5, vi(disk_time + 10, -1)));
  return dp(0, 0, disk_time, disk_n, songs, cache);
}


namespace algorithms::onlinejudge::advanced_topics::raucous_rockers
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
        std::cin >> t_cases;
        bool is_first_case = true;
        while(t_cases--) {

          if(is_first_case) {
            is_first_case = false;
          } else {
            std::cout << "\n";
          }

          int songs_n, disk_time, disks_n;
          while_read(songs_n, disk_time, disks_n);
          vi songs(songs_n);
          std::string s;
          for(int i = 0; i < songs_n; ++i) {
            std::cin >> s;
            if(i < songs_n - 1) {
              s.pop_back();
            }
            songs[i] = std::stoi(s);
          }
          printf("%d\n", get_max_songs(songs, disk_time, disks_n));
        }
    }
}