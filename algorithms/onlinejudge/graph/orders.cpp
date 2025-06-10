/*
───────────────────────────────────────────────────────────────
🧳 UVa 124 Following Orders, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dfs.cpp"

#include <optional>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>



typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;

int char_to_int(char c) { return c - '0' - 49; }

namespace algorithms::onlinejudge::graph::orders
{
    /** https://onlinejudge.org/external/1/124.pdf */
    vvb constraints;
    bool isspace(char ch) { return std::isspace(static_cast<unsigned char>(ch)); }
    bool satisfy(const std::string& o) {
      if(o.size() < 2) return true;
      char last = o.back();
      for(int i = 0; i < (int)o.size() - 1; ++i) {
        char c = o[i];
        if(!constraints[char_to_int(c)][char_to_int(last)])
          return false;  
      }
      return true;
    }
    void backtrack(const std::string& letters, int used, std::string& o, std::set<std::string>& set_o)
    {
        if(!satisfy(o)) return;

        if(__builtin_popcount(used) == 
           (int)letters.size()) {
          set_o.insert(o);
          return;
        }

        for(int i = 0; i < (int)letters.size(); ++i)
          if(!(used & (1 << i))) {
            o += letters[i];
            backtrack(letters, used | (1 << i), o, set_o);
            o.pop_back();
          }
    }
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
    
        std::string in;
        bool is_first = true;
        while(std::getline(std::cin, in)) {
          if(!is_first) std::cout << std::endl;
          else is_first = false;
          constraints.clear();
          std::stringstream ss_l(in);
          char c;
          std::string letters;
          while(ss_l >> c) letters.push_back(c);
          std::getline(std::cin, in);
          std::stringstream ss_o(in);;
          std::string order;
          while(ss_o >> c) order.push_back(c);
          constraints.resize(26, vb(26, true));
          for(int i = 0; i < (int)order.size(); i += 2)
            constraints[char_to_int(order[i + 1])][char_to_int(order[i])] = false;
          std::set<std::string> orderings;
          std::string o;
          backtrack(letters, 0, o, orderings);
          for(auto o : orderings) std::cout << o << std::endl;
        }
    }
}