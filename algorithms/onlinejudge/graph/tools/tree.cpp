#pragma once

#include <numeric>


namespace algorithms::onlinejudge::graph::tools::tree
{
    template<typename T = int>
    T def = std::numeric_limits<T>::max();
    template<typename T = int>
    struct Tree
    {
        int node;
        T val;
        Tree* left = nullptr; 
        Tree* right = nullptr;
        Tree() {
          this->node = -1;
          this->val = def<T>;
        }
        Tree(T val, int node = -1) {
        this->node = node;
        this->val = val;
        }
    };

  
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
}