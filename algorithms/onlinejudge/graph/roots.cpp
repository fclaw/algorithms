 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 10459 The Tree Root, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;

struct Diameter
{
    int length;
    vi path;
    bool operator < (const Diameter& other) const {
      return length < other.length;
    }
};


struct Point 
{
    int idx;
    int dist;
    bool operator < (const Point& other) const {
      return dist < other.dist;
    }
};

Point find_first_point(int node, int parent, const vvi& tree) {
  Point point = {node, 0};
  for(int neigh : tree[node]) {
    if(neigh == parent) continue;
    Point neigh_point = find_first_point(neigh, node, tree);
    neigh_point.dist += 1;
    point = std::max(point, neigh_point);
  }
  return point;
}

Diameter detect_diameter(int node, int parent, const vvi& tree) {
  Diameter diameter = {0, {node}};
  for(int neigh : tree[node]) {
    if(neigh == parent) continue;
    Diameter neigh_diameter = detect_diameter(neigh, node, tree);
    neigh_diameter.length += 1;
    neigh_diameter.path.push_back(node);
    diameter = std::max(diameter, neigh_diameter);
  }
  return diameter;
}

std::set<int> find_best_roots(const std::pair<int, int>& range, const vi& path) {
  int cnt = 0, idx = 0;
  std::set<int> roots;
  while(idx < (int)path.size()) {  
    if(cnt >= range.first && 
       cnt <= range.second) {
      roots.insert(path[idx]);
    }
    ++idx;
    ++cnt;
  }
  return roots;
}

void add_leaves(int r, int depth, int node, int parent, const vvi& tree, std::set<int>& leaves) {
  bool is_leaf = true;
  for(int neigh : tree[node]) {
    if(neigh == parent) continue;
    is_leaf = false;
    add_leaves(r, depth + 1, neigh, node, tree, leaves);
  }
  if(is_leaf && depth >= r) 
    leaves.insert(node);
}


std::set<int> find_worst_roots(int r, const std::set<int>& best_roots, const vvi& tree) {
  std::set<int> worst_roots;
  for(int root : best_roots)
    add_leaves(r, 0, root, -1, tree, worst_roots);
  return worst_roots;
}


namespace algorithms::onlinejudge::graph::roots
{
    /** https://onlinejudge.org/external/104/10459.pdf */
    int V;
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

        while(while_read(V)) {
          vvi tree(V);
          for(int v = 0; v < V; ++v) {
            int n;
            while_read(n);
            vi children(n);
            for(int i = 0; i < n; ++i) {
              while_read(children[i]);
              --children[i];
            }
            tree[v] = children;
          }
          
          // diameter
          auto point = find_first_point(tree.front().front(), -1, tree);
          Diameter diameter = detect_diameter(point.idx, -1, tree);
          int dl = diameter.length;
          std::pair<int, int> best_root_range;
          if(!(dl % 2)) { 
            best_root_range.first = dl / 2;
            best_root_range.second = dl / 2;
          } else {
            best_root_range.first = dl / 2;
            best_root_range.second = dl / 2 + 1;
          }

          std::set<int> best_roots = find_best_roots(best_root_range, diameter.path);
          std::set<int> worst_roots = find_worst_roots((dl + 1) / 2, best_roots, tree);
          std::string best_roots_s;
          for(int r : best_roots) {
            best_roots_s += std::to_string(r + 1) + " ";
          }
          std::string worst_roots_s;
          for(int r : worst_roots) {
            worst_roots_s += std::to_string(r + 1) + " ";
          }
          best_roots_s.pop_back();
          worst_roots_s.pop_back();
          printf("Best Roots  : %s\nWorst Roots : %s\n", best_roots_s.c_str(), worst_roots_s.c_str());
        }
    }
}