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




struct Elephant
{
    int w;
    int iq;
    int idx;
};

std::ostream& operator << 
(std::ostream& out, const Elephant& e) 
{ return out << "{" << e.w << ", "  << e.iq << ", " << e.idx << "}"; }


bool operator < (const Elephant& el, const Elephant& er) { return el.iq > er.iq || (el.iq == er.iq && el.w < er.w); }

typedef std::vector<int> vi;
typedef std::vector<Elephant> ve;


namespace algorithms::onlinejudge::dp::elephants
{
    /** https://onlinejudge.org/external/101/10131.pdf */
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
        
        int idx = 1, w, iq;
        ve elephants;
        while(while_read(w, iq)) 
          elephants.push_back({w, iq, idx++});
        std::sort(elephants.begin(), elephants.end());

        int s = (int)elephants.size();
        vi dp(s, 1);
        vi sol(s, -1);

        for(int i = 1; i < s; ++i)
          for(int j = i - 1; j >= 0; --j)
            if(elephants[j].w < elephants[i].w &&
              elephants[j].iq > elephants[i].iq &&
               dp[i] < 1 + dp[j]) 
            { sol[i] = j; dp[i] = 1 + dp[j]; }
   
        vi seq;
        int start_it = std::distance(dp.begin(), std::max_element(dp.begin(), dp.end()));
        while(start_it != -1) {
          seq.push_back(elephants[start_it].idx);
          start_it = sol[start_it];
        }

        printf("%d\n", (int)seq.size());
        for(auto it = seq.rbegin(); it != seq.rend(); ++it) std::cout << *it << std::endl;
    }
}