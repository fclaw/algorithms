/*
───────────────────────────────────────────────────────────────
🧳 UVa 10051 Tower of Cubes, rt: s
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
#include <set>





enum Face {Def, Front, Back, Left, Right, Top, Bottom};


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

struct Cube { std::unordered_map<Face, int> faces; };

typedef std::vector<int> vi;
typedef std::vector<Cube> v_cube;
typedef std::vector<std::pair<int, Face>> v_pif;

struct Ans
{
    int max_cubes;
    v_pif faces; 
};

Ans def = {0, {}};

bool operator < (const Ans& lhs, const Ans& rhs) { return lhs.max_cubes < rhs.max_cubes; }
bool operator == (const Ans& lhs, const Ans& rhs) { return lhs.max_cubes == rhs.max_cubes; }


typedef std::vector<Ans> v_ans;
typedef std::vector<v_ans> vv_ans;
typedef std::vector<vv_ans> vvv_ans;


namespace algorithms::onlinejudge::dp::tower_of_cubes
{
    /** https://onlinejudge.org/external/100/10051.pdf */
    int n, t_cases = 1;
    const int FN = 6;
    const int MAX_COLOR = 100;
    Ans knapsack(const v_cube& cubes, int i, Face prev_face, int top_colour, bool is_base, vvv_ans& memo)
    {
        if(i == n) return def;

        Ans& best = memo[i][prev_face][top_colour];
        if(!(best == def)) return best;

        // skip the current cube
        best = knapsack(cubes, i + 1, prev_face, top_colour, is_base, memo);

        // add current cube with all possible combination of colours at the bottom, congruent to the current colour
        for(int f = 1; f <= FN; ++f) {
          Face face = static_cast<Face>(f);
          int bottom_colour = cubes[i].faces.at(face);
          if(is_base || (!is_base && bottom_colour == top_colour)) {
            // bool new_is_base = !is_base;
            int op_colour = cubes[i].faces.at(opposite_face.at(face));
            Ans add = knapsack(cubes, i + 1, face, op_colour, false, memo);
            add.max_cubes++;
            int original_cube_index = n - i; // 1-based index in original input
            add.faces.push_back({original_cube_index, opposite_face.at(face)});
            best = std::max(best, add);
          }
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
        

        while(while_read(n)) {
          v_cube cubes(n);
          loop(n, [&cubes] (int i){
            std::unordered_map<Face, int> faces;
            for(int f = 1; f <= FN; ++f)
              while_read(faces[static_cast<Face>(f)]);
            cubes[i] = {faces};
          });
          std::reverse(cubes.begin(), cubes.end());
          vvv_ans memo(n + 1, vv_ans(FN + 1, v_ans(MAX_COLOR + 1, def)));
          Ans ans = knapsack(cubes, 0, Def, 0, true, memo);

          printf("Case #%d\n%d\n", t_cases++, ans.max_cubes);
          for(auto& p : ans.faces)
            std::cout << p.first << " " << face_to_str(p.second) << std::endl;
          std::cout << std::endl;  
        }
    }
}