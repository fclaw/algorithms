
 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 10080 Gopher II, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/mcbm.cpp"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;

constexpr double eps = 1e-6; // epsilon for floating point comparison

using dd = std::pair<double, double>;

struct Entity
{
    int id;
    dd pos;
};

using v_gopher = std::vector<Entity>;
using v_hole = std::vector<Entity>;

// All inputs are std::pair<int, int>
double euclidean(const dd& p1, const dd& p2) {
  double dx = std::abs(p1.first - p2.first);
  double dy = std::abs(p1.second - p2.second);
  return dx * dx + dy * dy;
}


namespace algorithms::onlinejudge::graph::gopher_ii
{
    /** https://onlinejudge.org/external/100/10080.pdf */
    int gophers_n, holes_n;
    double time, speed;
    dd pos;
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
        
        while(while_read(gophers_n, holes_n, time, speed)) {
          v_gopher gophers(gophers_n);
          v_hole holes(holes_n);
          for(int gopher_id = 0; gopher_id < gophers_n; ++gopher_id) {
            while_read(pos);
            gophers[gopher_id] = {gopher_id, pos};
          }
          for(int hole_id = 0; hole_id < holes_n; ++hole_id) {
            while_read(pos);
            holes[hole_id] = {hole_id, pos};
          }

          int R_SIZE = gophers_n;
          int L_SIZE = holes_n;

          mcmb::vvi graph(R_SIZE);
          for(const auto& gopher : gophers) {
            for(const auto& hole : holes) {
              double dist_gopher_hole_sq = euclidean(gopher.pos, hole.pos);
              if(std::sqrt(dist_gopher_hole_sq) <= time * speed + eps) {
                graph[gopher.id].push_back(hole.id);
              }
            }
          }

          int gophers_in_hole = 0;
          mcmb::kuhn kuhn_s(L_SIZE);
          for(int gopher_id = 0; gopher_id < R_SIZE; ++gopher_id) {
            kuhn_s.visited.assign(R_SIZE, false);
            bool is_gopher_saved = mcmb::try_kuhn(gopher_id, graph, kuhn_s);
            if(is_gopher_saved) gophers_in_hole++;
          }
          std::cout << (gophers_n - gophers_in_hole) << std::endl;
        }
    }
}