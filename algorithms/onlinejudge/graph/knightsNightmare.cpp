/*
───────────────────────────────────────────────────────────────
🧳 UVa 10426 Knights’ Nightmare, rt: s
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


typedef std::pair<int, int> pii;
typedef std::vector<pii> vpii;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;


constexpr int L = 4;
constexpr int N = 8;

const int knight_dx[N] = { -2, -1, 1, 2,  2,  1, -1, -2 };
const int knight_dy[N] = {  1,  2, 2, 1, -1, -2, -2, -1 };




namespace algorithms::onlinejudge::graph::knights_nightmare
{
    /** https://onlinejudge.org/external/104/10426.pdf */
    int R, C;
    std::string t_case;
    bool in_board(int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; }
    void do_bfs(int knight, pii source, pii beast, bool is_dormant, vvvi& dist) {
      dist[knight][source.first][source.second] = 0;
      std::queue<pii> queue;
      queue.emplace(source);
      while(!queue.empty()) {
        pii pos = queue.front(); queue.pop();
        int r = pos.first;
        int c = pos.second;
        for(int n = 0; n < N; ++n) {
          int nr = r + knight_dx[n];
          int nc = c + knight_dy[n];
          if(!in_board(nr, nc)) continue;
          pii new_pos = {nr, nc};
          // Skip already visited
          if(~dist[knight][nr][nc]) continue;
          // Skip the beast’s cell if it's awake
          if(!is_dormant && new_pos == beast) continue;
          dist[knight][nr][nc] = dist[knight][r][c] + 1;
          queue.emplace(new_pos);
        }
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
        
        while(while_read(t_case)) {
          while_read(R, C);
          vpii knights(L);
          for(int l = 0; l < L; ++l) {
            pii pos;
            while_read(pos);
            --pos.first; --pos.second;
            knights[l] = pos;
          }

          pii beast;
          while_read(beast);
          --beast.first; --beast.second;

          int min_time = INT32_MAX;
          for(int l = 0; l < L; ++l) {
            int who_wakes = 0;
            vvvi dist(L, vvi(R, vi(C, -1)));
            who_wakes |= (1 << l);
            do_bfs(l, knights[l], beast, true, dist);
            for(int l = 0; l < L; ++l)
              if(!(who_wakes & (1 << l)))
                do_bfs(l, knights[l], beast, false, dist);

            for(int r = 0; r < R; ++r) {
              for(int c = 0; c < C; ++c) {
                int count = 0;
                int loc_time = 0;  
                for(int l = 0; l < L; ++l) {
                  if(~dist[l][r][c]) ++count;
                  loc_time += dist[l][r][c];
                }
                if(count == L) min_time = std::min(min_time, loc_time);
              }
            }
          }
          std::string ans = min_time != INT32_MAX ? "Minimum time required is " + std::to_string(min_time) + " minutes." : "Meeting is impossible.";
          printf("%s\n%s\n", t_case.c_str(), ans.c_str());
        }
    }
}