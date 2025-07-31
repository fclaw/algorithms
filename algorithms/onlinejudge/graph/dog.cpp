
 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 670 The dog task, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/mcbm.cpp"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;


constexpr double speed_factor = 2.0; // factor to speed up the dog
constexpr double eps = 1e-6; // epsilon for floating point comparison

using ii = std::pair<int, int>;

// left set is the segments
struct Segment
{
    int id;
    ii start;
    ii end;
    Segment(int _id, ii _start, ii _end) :
      id(_id), start(_start), end(_end) {}
};


// right set is the places
struct Place
{
    int id;
    ii pos;
    Place(int _id, ii _pos) : 
      id(_id), pos(_pos) {}
};


using v_segment = std::vector<Segment>;
using v_place = std::vector<Place>;
using ll = long long;

// All inputs are std::pair<int, int>
double euclidean(const ii& p1, const ii& p2) {
  ll dx = std::abs(p1.first - p2.first);
  ll dy = std::abs(p1.second - p2.second);
  return dx * dx + dy * dy;
}


namespace algorithms::onlinejudge::graph::dog
{
    /** https://onlinejudge.org/external/6/670.pdf */
    int t_cases, n, m;
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
          while_read(n, m);

          ii point;
          std::vector<ii> points;
          for(int i = 0; i < n; ++i) {
            while_read(point);
            points.emplace_back(point);
          }

          v_segment segments;
          for(int i = 1; i < (int)points.size(); ++i) {
            ii start = points[i - 1];
            ii end = points[i];
            segments.emplace_back(i - 1, start, end);
          }

          v_place places;
          for(int i = 0; i < m; ++i) {
            int x, y;
            while_read(x, y);
            places.emplace_back(i, ii(x, y));
          }

          int R_SIZE = segments.size();
          int L_SIZE = places.size();

          mcmb::vvi graph(R_SIZE);
          for(const auto& seg : segments) {
            for(const auto& place : places) {
              double dist_AP_sq = euclidean(seg.start, place.pos);
              double dist_PB_sq = euclidean(place.pos, seg.end);
              double dist_AB_sq = euclidean(seg.start, seg.end);
              double dog_walk = std::sqrt(dist_AP_sq) + std::sqrt(dist_PB_sq);
              double master_walk = std::sqrt(dist_AB_sq);
              if(dog_walk <= speed_factor * master_walk + eps) {
                graph[seg.id].push_back(place.id);
              }
            }
          }

          mcmb::kuhn kuhn_s(L_SIZE);
          for(int seg_id = 0; seg_id < R_SIZE; ++seg_id) {
            kuhn_s.visited.assign(R_SIZE, false);
            mcmb::try_kuhn(seg_id, graph, kuhn_s);
          }

          std::unordered_map<int, int> segments_with_places;
          for(int i = 0; i < L_SIZE; ++i) {
            if(~kuhn_s.match[i]) {
              segments_with_places[kuhn_s.match[i]] = i;
            }
          }

          std::vector<ii> route = {segments.front().start};
          for(auto seg : segments) {
            if(segments_with_places.count(seg.id)) {
              int place_id = segments_with_places[seg.id];
              auto place = places[place_id];
              route.emplace_back(place.pos);
            }
            route.emplace_back(seg.end);
          }

          std::string route_str;
          for(const auto& p : route) {
            route_str += std::to_string(p.first) + " " + std::to_string(p.second) + " ";
          }
          route_str.pop_back(); // remove last space
          printf("%d\n%s\n", (int)route.size(), route_str.c_str());
          if(t_cases) std::cout << std::endl;
        }
    }
}