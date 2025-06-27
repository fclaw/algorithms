/*
───────────────────────────────────────────────────────────────
🧳 UVa 10067 Playing with Wheels, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/bfs.cpp"

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
#include <queue>
#include <set>



struct Number {
    std::array<int, 4> digits;  // digits[0] is the first digit, ..., digits[3] is the fourth
    Number(int i, int j, int k, int l) : digits{{i, j, k, l}} {}
    void press_left_arrow(int d) {
      --d; digits[d] = (digits[d] + 9) % 10; // Convert from 1-based to 0-based index
    }
    void press_right_arrow(int d) {
      --d; digits[d] = (digits[d] + 1) % 10;
    }
    bool operator == (const Number& other) const {
      return digits == other.digits;
    }
    bool operator < (const Number& other) const {
      return digits < other.digits;
    }
};

int encode(const Number& n) { return n.digits[0]*1000 + n.digits[1]*100 + n.digits[2]*10 + n.digits[3]; }

struct State
{
    Number num;
    int dist;
};

constexpr int MAX = 10000;

namespace algorithms::onlinejudge::graph::playing_with_wheels
{
    /** https://onlinejudge.org/external/100/10067.pdf */
    int t_cases;
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
        
        while_read(t_cases);
        while(t_cases--) {
          std::vector<bool> visited(MAX, false);
          std::vector<bool> forbidden(MAX, false);
          int i, j, k, l;
          while_read(i, j, k, l);
          Number source(i, j, k, l);
          while_read(i, j, k, l);
          Number sink(i, j, k, l);
          int n;
          while_read(n);
          loop(n, [&] (int i) {
            while_read(i, j, k, l);
            forbidden[encode(Number(i, j, k, l))] = true;
          });

          std::queue<State> queue;
          queue.push({source, 0});
          visited[encode(source)] = true;
          int min_dist = -1;
          while(!queue.empty()) {
            State state = queue.front(); queue.pop();
            Number num = state.num;
            if(num == sink)
            { min_dist = state.dist; break; }
            for(int i = 1; i <= 4; ++i) {
              Number tmp = num;
              tmp.press_left_arrow(i);
              int tmp_encoded = encode(tmp);
              if(!visited[tmp_encoded] && 
                 !forbidden[tmp_encoded]) {
                visited[tmp_encoded] = true;
                queue.push({tmp, state.dist + 1});    
              }
              tmp = num;
              tmp.press_right_arrow(i);
              tmp_encoded = encode(tmp);
              if(!visited[tmp_encoded] && 
                 !forbidden[tmp_encoded]) {
                visited[tmp_encoded] = true;
                queue.push({tmp, state.dist + 1});    
              }
            }
          }
          std::cout << min_dist << std::endl;
        }
    }
}