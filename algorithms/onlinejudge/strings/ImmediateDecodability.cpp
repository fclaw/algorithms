/*
───────────────────────────────────────────────────────────────
🧳 UVa 644 Immediate Decodability, https://onlinejudge.org/external/6/644.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


const std::string separator = "9";


bool isPrefix(const std::string& prefix, const std::string& full_str) {
    // A prefix cannot be longer than the full string!
    if (prefix.length() > full_str.length()) return false;

    // Compare full_str starting at index 0, for a length of prefix.length(), against prefix
    return full_str.compare(0, prefix.length(), prefix) == 0;
}

bool check_immediate_decodability(std::vector<std::string>& records) {

   auto cmp = 
          [](const std::string& lhs, 
             const std::string& rhs) {
            return lhs.length() < rhs.length();
          };
   std::sort(records.begin(), records.end(), cmp);

   for(int i = 0; i < (int)records.size(); ++i) {
     for(int j = 0; j < (int)records.size(); ++j) {
       if(i == j) continue;
       if(isPrefix(records[i], records[j])) {
          return false;
       }
     }
   }


   return true;
}


namespace algorithms::onlinejudge::strings::immediate_decodability
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

        int set = 1;
        std::string record;
        std::vector<std::string> records;
        while(std::cin >> record) {
          if(record == separator) {
            std::string ans = "is immediately decodable";
            if(!check_immediate_decodability(records)) {
              ans = "is not immediately decodable";
            }
            printf("Set %d %s\n", set++, ans.c_str());
            records.clear();
          }
          records.push_back(record);
        }
    }
}