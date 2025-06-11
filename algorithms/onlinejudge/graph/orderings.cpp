/*
───────────────────────────────────────────────────────────────
🧳 UVa 872 Ordering, rt: s
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
#include <cctype>



typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;


int char_to_int(char c) { return c - '0' - 49; }

namespace algorithms::onlinejudge::graph::topsort_orderings
{
    /** https://onlinejudge.org/external/8/872.pdf */
    char toupper(char ch) { return static_cast<char>(std::toupper(static_cast<unsigned char>(ch))); }
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
          if(!o.empty()) set_o.insert(o);
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
    
        int t_cases;
        while_read(t_cases);
        std::cin.ignore();
        bool is_first = true;
        while(t_cases--) {
          std::cin.ignore();
          constraints.clear();
          std::string in;
          std::getline(std::cin, in);
          std::stringstream ss_l(in);
          char c;
          std::string letters;
          while(ss_l >> c) letters.push_back(std::tolower(c));
          std::getline(std::cin, in);
          std::stringstream ss_o(in);;
          std::string order;
          while(ss_o >> c) order.push_back(std::isalpha(c) ? std::tolower(c) : c);
          constraints.resize(26, vb(26, true));
          for(int i = 0; i < (int)order.size(); i += 3) {
            if(order[i + 1] == '<')
              constraints[char_to_int(order[i + 2])][char_to_int(order[i])] = false;
            else constraints[char_to_int(order[i])][char_to_int(order[i + 2])] = false;
          }

          std::set<std::string> orderings;
          std::string o;
          backtrack(letters, 0, o, orderings);
          if(!is_first) std::cout << std::endl;
          else is_first = false;
          if(orderings.empty()) printf("NO\n");
          else 
            for(auto o : orderings) {
              std::string s;
              for(char c : o)
              { s += toupper(c); s += ' '; }
              s.pop_back();
              std::cout << s << std::endl;  
            }
        }
    }
}