/*
───────────────────────────────────────────────────────────────
🧳 UVa 384 Slurpys, https://onlinejudge.org/external/3/384.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



bool is_slump(const std::string& s, size_t& index) {
  size_t start_index = index;
  // Must start with 'D' or 'E'
  if(index >= s.size() || 
     (s[index] != 'D' && 
      s[index] != 'E')) {
    return false;
  }
  index++;

  // Followed by one or more 'F's
  if(index >= s.size() || 
     s[index] != 'F') {
    index = start_index; // Reset index on failure
    return false;
  }
  while(index < s.size() && 
        s[index] == 'F') {
    index++;
  }

  // Followed by either another slump or a 'G'
  if(index < s.size() && 
     s[index] == 'G') {
    index++;
    return true;
  } else {
    if (is_slump(s, index)) {
      return true;
    } else {
      index = start_index; // Reset index on failure
      return false;
    }
  }
}
bool is_slimp(const std::string& s, size_t& index) {
  size_t start_index = index;
  // Must start with 'A'
  if(index >= s.size() || 
     s[index] != 'A') {
    return false;
  }
  index++;

  // Next character
  if(index >= s.size()) {
    index = start_index; // Reset index on failure
    return false;
  }

  if(s[index] == 'H') { // If it consists of a two character Slimp then its second and last character is an ’H’.
    index++;
    return true;
  } else if(s[index] == 'B') { // ’A’ followed by ’B’ followed by a Slimp followed by a ’C’.
    index++;
    if(is_slimp(s, index)) {
      if(index < s.size() && 
         s[index] == 'C') {
        index++;
        return true;
      } else {
        index = start_index; // Reset index on failure
        return false;
      }
    } else {
      index = start_index; // Reset index on failure
      return false;
    }
  } else {
    if(is_slump(s, index)) { // ’A’ followed by a Slump (see above) followed by a ’C’.
      if(index < s.size() && 
         s[index] == 'C') {
        index++;
        return true;
      } else {
        index = start_index; // Reset index on failure
        return false;
      }
    } else {
      index = start_index; // Reset index on failure
      return false;
    }
  }
}

namespace algorithms::onlinejudge::strings::slurpys
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
        printf("SLURPYS OUTPUT\n");
        while(t_cases--) {
          std::string s;
          while_read(s);
          size_t index = 0;
          if(is_slimp(s, index)) {
            if(index < s.size()) {
              if(is_slump(s, index)) {
                if(index == s.size()) {
                  printf("YES\n");
                  continue;
                }
              }
            }
          }
          printf("NO\n");
        }
        printf("END OF OUTPUT\n");
    }
}