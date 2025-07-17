/*
───────────────────────────────────────────────────────────────
🧳 UVa 10051 Tower of Cubes, rt: s
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
#include <set>



using vi = std::vector<int>;

namespace tools = algorithms::onlinejudge::graph::tools;

enum Face {Front, Back, Left, Right, Top, Bottom};

constexpr int Faces = 6;

std::unordered_map<Face, Face> opposite_face = 
{ {Front, Back}, 
  {Back, Front},
  {Left, Right}, 
  {Right, Left},
  {Top, Bottom}, 
  {Bottom, Top}};


std::string face_to_str(Face face) 
{
    switch(face) {
        case Front:  return "front";
        case Back:   return "back";
        case Left:   return "left";
        case Right:  return "right";
        case Top:    return "top";
        case Bottom: return "bottom";
        default:     return "unknown";
    }
}

struct Cube
{
    int id;
    Face top_face;
    int colour; // color of the top face
    int op_colour; // color of the bottom face
    int weight;
};

std::ostream& operator << (std::ostream& os, const Cube& cube) 
{ return os << "{cube_id: " << cube.id << ", face: " << cube.top_face << ", colour: " << cube.colour << ", opposite colour: " << cube.op_colour << "}"; }

using map = std::unordered_map<int, Cube>;

namespace algorithms::onlinejudge::graph::tower_of_cubes
{
    /** https://onlinejudge.org/external/100/10051.pdf */
    int N, t_case = 1;
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

        bool first_case = true; // Flag to track if this is the first test case
        while(while_read(N) && N) {

          // --- THE FIX ---
          if(!first_case) {
            std::cout << std::endl; // Print the blank line separator BEFORE this case
          }
          first_case = false; // It's no longer the first case
        
          int node = 0;
          map node_to_cube;
          for(int cube_idx = 1; cube_idx <= N; ++cube_idx) {
            // Read the 6 face colors for the current cube
            int colors[Faces];
            for(int i = 0; i < Faces; ++i) std::cin >> colors[i];
            
            // For each of the 6 possible orientations...
            for (int top_face_idx = 0; top_face_idx < Faces; ++top_face_idx) {
              Face top_face = static_cast<Face>(top_face_idx);
              int top_clr = colors[top_face];
              int bottom_clr = colors[opposite_face[top_face]];
              node_to_cube[node++] = { cube_idx, top_face, top_clr, bottom_clr, cube_idx };
            }
        }

          int V = node;
          tools::Graph<> graph(V);
          for(int i = 0; i < V; ++i) {
            for(int j = 0; j < V; ++j) {
              if(i == j) continue;
              int cube_i = node_to_cube[i].id;
              int cube_j = node_to_cube[j].id;
              if(cube_i != cube_j) {
                int top_clr = node_to_cube[i].colour;
                int bottom_clr = node_to_cube[j].op_colour;
                int w_i = node_to_cube[i].weight;
                int w_j = node_to_cube[j].weight;
                // match the colour of the top face of the heaviest cube 
                // with colour on the opposite face to the top face of the lighter one
                if(w_i > w_j && top_clr == bottom_clr) {
                  graph[i].push_back(tools::mkDefNode(j));
                }
              }
            }
          }
          
          tools::TopSortKahn khan = tools::top_sort_kahn(V, graph);
          // dp[i] will store the LENGTH of the longest path ending at node i.
          vi dp(V, 1); // Initialize all paths to length 1 (the box itself)
          // parent[i] will store the predecessor of node i on its current longest path.
          // This is needed to reconstruct the final path.
          vi parent(V, -1);

          //Iterate through the nodes in the order given by the topological sort.
          for(int u : khan.top_sort) {   
            // For each neighbor v of u...
            for(const auto& neigh : graph[u]) {
              int v = neigh.node;     
              //Check if the path through u creates a longer path to v.
              if(dp[u] + 1 > dp[v]) {
                // We found a better path to v!
                dp[v] = dp[u] + 1;
                parent[v] = u; // The best way to get to v is now from u.
              }
            }
          }


          // 1. Find the length of the longest path and where it ends.
          int max_len = 0;
          int end_node = -1;
          for(int i = 0; i < V; ++i) {
            if(dp[i] > max_len) {
              max_len = dp[i];
              end_node = i;
            }
          }

          // 2. Reconstruct the path by backtracking using the parent array.
          vi path;
          int current_node = end_node;
          while(current_node != -1) {
            path.push_back(current_node);
            current_node = parent[current_node];
          }

          printf("Case #%d\n%d\n", t_case++, max_len);
          for(auto& p : path) {
            Cube cube = node_to_cube[p];
            printf("%d %s\n", cube.id, face_to_str(cube.top_face).c_str());
          }
        }  
    }
}