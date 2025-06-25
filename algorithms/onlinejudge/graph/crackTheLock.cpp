/*
───────────────────────────────────────────────────────────────
🧳 UVa 12160 Unlock the Lock, rt: s
───────────────────────────────────────────────────────────────
*/

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
#include <cmath>
#include <queue>



int str_to_int(const std::string& s) 
{
    int num = 0;
    for (char c : s)
      num = num * 10 + (c - '0');
    return num;
}


typedef std::vector<int> vi;

constexpr int MAX = 10000;

bool visited[MAX];
int dist[MAX];

namespace algorithms::onlinejudge::graph::crack_the_lock
{
    /** https://onlinejudge.org/external/121/12160.pdf */
    std::string lock_s, code_s;
    int n, t_case = 1;
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
        
        while(while_read(lock_s, code_s, n)) {
          int lock = str_to_int(lock_s);
          int code = str_to_int(code_s);
          if(!lock && !code && !n) break;
          vi buttons(n);
          std::string s;
          loop(n, [&] (int i) {
            while_read(s);
            buttons[i] = str_to_int(s);
          });
          
          memset(visited, false, sizeof(visited));
          memset(dist, -1, sizeof(dist));
          std::queue<int> queue;
          queue.push(lock);
          dist[lock] = 0;
          while(!queue.empty()) {
            int d = queue.front(); queue.pop();
            visited[d] = true;
            if(d == code) break;
            for(int b : buttons) {
              int nd = (d + b) % MAX;
              if(!visited[nd]) {
                visited[nd] = true;
                dist[nd] = dist[d] + 1;
                queue.push(nd);
              }
            }
          }
          std::string ans = dist[code] != -1 ? std::to_string(dist[code]) : "Permanently Locked";
          printf("Case %d: %s\n", t_case++, ans.c_str());
        }
    }
}