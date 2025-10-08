/*
───────────────────────────────────────────────────────────────
🧳 UVa 991 Safe Salutations, https://onlinejudge.org/external/9/991.pdf, rt: s
   https://oeis.org/A000108: Catalan numbers: C(n) = binomial(2n,n)/(n+1) = (2n)!/(n!(n+1)!)
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "../../timeout.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>




namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

using ull = unsigned long long;
using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vi = std::vector<int>;
using vll = std::vector<long long>;


constexpr int Radius = 10;
constexpr long long MOD = 1000000007LL;



struct Handshake
{
    int id;
    ii from_person;
    ii to_person;
};

using v_hs = std::vector<Handshake>;


/**
 * Calculates the orientation of the ordered triplet (p, q, r).
 * @return 0 --> p, q and r are collinear
 *         1 --> Clockwise
 *         2 --> Counter-Clockwise
 */
int orientation(ii p, ii q, ii r) {
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for a detailed explanation of the formula.
    int val = (q.second - p.second) * (r.first - q.first) -
              (q.first - p.first) * (r.second - q.second);

    if (val == 0) return 0; // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or Counter-Clockwise
}

/**
 * Given three collinear points p, q, r, the function checks if
 * point q lies on line segment 'pr'.
 */
bool on_segment(ii p, ii q, ii r) {
    return (q.first <= std::max(p.first, r.first) && q.first >= std::min(p.first, r.first) &&
            q.second <= std::max(p.second, r.second) && q.second >= std::min(p.second, r.second));
}


/**
 * Determines if two handshakes (line segments) cross each other,
 * given the Cartesian coordinates of the people.
 *
 * @param h1 The first handshake (line segment p1-q1).
 * @param h2 The second handshake (line segment p2-q2).
 * @return True if the handshakes cross, false otherwise.
 */
bool is_handshakes_crossing(const Handshake& h1, const Handshake& h2) {
    ii p1 = h1.from_person;
    ii q1 = h1.to_person;
    ii p2 = h2.from_person;
    ii q2 = h2.to_person;

    // Find the four orientations needed
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case: If the orientations change, the lines cross.
    if (o1 != o2 && o3 != o4) {
        return true;
    }

    // --- Special Cases for Collinear Points ---
    // These check if one segment lies partially on the other.

    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && on_segment(p1, p2, q1)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && on_segment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && on_segment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && on_segment(p2, q1, q2)) return true;
    
    // If none of the cases apply, the segments do not intersect.
    return false;
}


bool check_crossings(const Handshake& hs, const v_hs& handshakes) {
  bool is_crossing = false;
  for(auto& h : handshakes)
    is_crossing |= is_handshakes_crossing(hs, h);
  return is_crossing;
}

ull backtrack(int mask, int n, const vii& circle, v_hs& handshakes, std::set<vi>& visited) {
  if(__builtin_popcount(mask) == n) {
    vi hs_ids;
    for(auto& h : handshakes)
      hs_ids.push_back(h.id);
    std::sort(hs_ids.begin(), hs_ids.end());  
    if(visited.find(hs_ids) == visited.end()) {
      visited.insert(hs_ids);
      return 1;
    }
    return 0;
  }

  ull ways = 0;
  for(int i = 0; i < n; ++i) {
    if((mask & (1 << i))) continue;
    int new_mask = mask | (1 << i);
    for(int j = 0; j < n; ++j) {
      if(i == j) continue;
      if(!(new_mask & (1 << j))) {
        Handshake hs;
        hs.id = 0 | (1 << i) | (1 << j);
        hs.from_person = circle[i];
        hs.to_person = circle[j];
        if(!check_crossings(hs, handshakes)) {
            handshakes.push_back(hs);
            ways += backtrack(new_mask | (1 << j), n, circle, handshakes, visited);
            handshakes.pop_back();
        }
      }
    }
  }
  return ways;
}

double degree_to_radians(int degrees) {
  return degrees * M_PI / 180.0;
}

vii generate_circle(int shift) {
  vii circle;
  ii curr_person;
  int degrees = 0;
  while(degrees < 360) {
    double radians = degree_to_radians(degrees);
    int x = Radius * std::cos(radians);
    int y = Radius * std::sin(radians);
    curr_person = ii(x, y);
    circle.push_back(curr_person);
    degrees += shift;
  }
  return circle;
}

namespace algorithms::onlinejudge::maths::safe_salutations
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        vll catalan = arithmetics::catalan_all(10, MOD);

        int n_pairs;
        bool first = true;
        while(scanf("%d", &n_pairs) == 1) {
        //   vii circle = generate_circle(360 / (2 * n_pairs));
        //   v_hs handshakes;
        //   std::set<vi> visited;
        //   ull ways = run_with_timeout(std::chrono::seconds(300), backtrack, 0, (int)circle.size(), circle, std::ref(handshakes), std::ref(visited));
          if(first) first = false;
          else printf("\n");
          printf("%llu\n", catalan[n_pairs]);
        }
    }
}