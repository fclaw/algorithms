/*
───────────────────────────────────────────────────────────────
🧳 UVa 10496 Collecting Beepers, rt: s
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




struct Point
{
    int x;
    int y;
    bool operator == (const Point& other) const 
    { return x == other.x && y == other.y; }
};

std::ostream& operator << 
  (std::ostream& out, const Point& point) 
  { return out << "{" << point.x << ", " << point.y << "}"; }

struct PointHash 
{
    std::size_t operator()(const Point& p) const 
    { return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1); }
};

struct PointPairHash 
{
    std::size_t operator()(const std::pair<Point, Point>& pp) const 
    {
        PointHash ph;
        return ph(pp.first) ^ (ph(pp.second) << 1);
    }
};


typedef std::vector<Point> v_point;
typedef std::vector<v_point> vv_point;
typedef std::unordered_map<std::pair<Point, Point>, int, PointPairHash> map_ppi;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

namespace algorithms::onlinejudge::dp::beepers
{
    /** https://onlinejudge.org/external/104/10496.pdf */
    int tc, n, m, k;
    int tcp(const v_point& beepers, int prev, int used, map_ppi dist, vvi& memo)
    {
        if(__builtin_popcount(used) == k + 1)
          return dist[{beepers[prev], beepers[0]}];

        int & best = memo[prev][used];
        if(~best) return best;

        best = INT32_MAX;  
        for(int i = 0; i <= k; ++i)
          if(!(used & (1 << i))) {
            int local_best = dist[{beepers[prev], beepers[i]}] + tcp(beepers, i, used | (1 << i), dist, memo);
            best = std::min(best, local_best);
        }
        return best;
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

        while_read(tc);
        while(tc--)
        {
            while_read(n, m);
            Point start;
            while_read(start.x, start.y);
            while_read(k);
            v_point beepers(k);
            loop(k, [&beepers](int i) {
              while_read(beepers[i].x, beepers[i].y);
            });

            
            map_ppi dist;
            v_point all_points = beepers;
            all_points.push_back(start);
            for(const auto& a : all_points)
              for(const auto& b : all_points) {
                int d = std::abs(a.x - b.x) + std::abs(a.y - b.y);
                dist[{a, b}] = d;
              }
            
            beepers.emplace(beepers.begin(), start);
            int s = (int)beepers.size();
            vvi memo(s + 1, vi(1 << s, -1));
            printf("The shortest path has length %d\n", tcp(beepers, 0, 1, dist, memo));
        }
    }
}