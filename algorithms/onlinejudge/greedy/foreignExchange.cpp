#include "../debug.h"
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <unordered_map>





struct Person { std::pair<size_t, size_t> loc; };

std::ostream& operator << 
  (std::ostream& out, const Person& p) 
  { return out << "{" << p.loc.first << ", "  << p.loc.second << "}"; }

bool operator < (const Person& x, const Person& y) { return x.loc < y.loc; }


typedef std::vector<Person> vp;
typedef std::unordered_map<size_t, vp> mivp;


namespace algorithms::onlinejudge::greedy::foreign_exchange
{
    /** https://onlinejudge.org/external/107/10763.pdf */
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
         
        size_t N;
        while(std::cin >> N && N)
        {
            mivp weighted;
            vp people(N);
            size_t from, to;
            for(size_t i = 0; i < N; i++) {
              scanf("%zu %zu\n", &from, &to); 
              weighted[from + to].push_back({{from, to}});
            }

            bool possible = true;
            for(auto& [w, ps] : weighted)
            {
                std::sort(ps.begin(), ps.end());
                int i = 0, j = ps.size() - 1;
                size_t cnt = 0;
                while (i < j)
                  if(ps[i].loc.first == ps[j].loc.second &&
                     ps[i].loc.second == ps[j].loc.first)
                  { ++i; --j; ++cnt; }
                  else { possible = false; break; }

                if (2 * cnt != ps.size()) 
                  possible = false; // unpaired leftover
                if(!possible) break;
            }
            std::cout << (possible ? "YES" : "NO") << std::endl;
        }
    }
}