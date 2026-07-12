/*
───────────────────────────────────────────────────────────────
🧳 UVa 11056 Formula 1, https://onlinejudge.org/external/110/11056.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



struct Record
{
    std::string pilot;
    int min;
    int sec;
    int ms;
    bool operator < (const Record& other) const {
      // 1. Compare times using std::tie (constant time, highly optimized)
      auto t1 = std::tie(min, sec, ms);
      auto t2 = std::tie(other.min, other.sec, other.ms);
        
      if (t1 != t2) {
        return t1 < t2; // Returns true if this time is faster (smaller)
      }

      // 2. Tie-breaker: Case-Insensitive Lexicographical Comparison
      size_t len1 = pilot.length();
      size_t len2 = other.pilot.length();
      size_t min_len = std::min(len1, len2);

      for (size_t i = 0; i < min_len; ++i) {
        // Safety cast to unsigned char as discussed in our ASCII lessons!
        char c1 = std::tolower((unsigned char)pilot[i]);
        char c2 = std::tolower((unsigned char)other.pilot[i]);
            
        if (c1 != c2) {
          return c1 < c2;
        }
      }

      // If all characters match up to the shorter length, the shorter string comes first
      return len1 < len2;
    }
};


using v_record = std::vector<Record>;


namespace algorithms::onlinejudge::strings::formula_1
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

        int racers_n;
        while(std::cin >> racers_n) {
          std::cin.ignore();
          std::string in;
          v_record records;
          for(int i = 0; i < racers_n; ++i) {
            std::getline(std::cin, in);
            std::stringstream ss(in);
            std::string item, marker;
            Record record;
            while(ss >> item >> marker) {
              if(marker == ":") {
                record.pilot = item;
              } else if (marker == "min") {
                record.min = std::stoi(item);
              } else if (marker == "sec") {
                record.sec = std::stoi(item);
              } else {
                record.ms = std::stoi(item);
              }
            }
            records.push_back(record);
          }

          std::sort(records.begin(), records.end());

          int row = 1;
          int S = (int)records.size();
          for(int i = 0; i < S; i += 2) {
            printf("Row %d\n", row++);
            printf("%s\n", records[i].pilot.c_str());
            if(i + 1 < S) {
              printf("%s\n", records[i + 1].pilot.c_str());
            }
          }
          printf("\n");
        }
    }
}