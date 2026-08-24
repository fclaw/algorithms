/*
───────────────────────────────────────────────────────────────
🧳 UVa 321 The New Villa, https://onlinejudge.org/external/3/321.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 


using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vb = std::vector<bool>;
using vvb = std::vector<vb>;


struct State
{
    int room;      // Current room Mr. Black is in (0-indexed: 0 to r-1)
    int lit_rooms; // Bitmask of currently illuminated rooms (bit i = 1 means room i is ON)
    std::vector<std::string> actions; // Step-by-step history of moves taken

    /**
     * Start State:
     *   room = 0 (Hallway)
     *   lit_rooms = (1 << 0) [Only Hallway is lit]
     * 
     * Goal State:
     *   room = r - 1 (Bedroom)
     *   lit_rooms = (1 << (r - 1)) [Only Bedroom is lit]
     */
};

const std::string turn_off = "- Switch off light in room ";
const std::string turn_on = "- Switch on light in room ";
const std::string move = "- Move to room ";

std::string get_min_path_required(int R, int S, const vvi& graph, const vvi& switches) {

   int hallway = 0;
   int bedroom = R - 1;
   int target_lit = 1 << (R - 1);

   std::queue<State> queue;
   vvb visited(R, vb(1 << R, false));
   // init
   queue.push({hallway, (1 << 0), {}});
   visited[hallway][1 << 0] = true;
   
   // ans
   int min_steps = -1;
   std::string path;
  
   while(!queue.empty()) {
     State state =  queue.front(); queue.pop();
     int curr_room = state.room;
     int lit_rooms = state.lit_rooms;
     auto actions_so_far = state.actions;

     if(curr_room == bedroom) {
       if(lit_rooms == target_lit) {
         min_steps = (int)actions_so_far.size();
         for(int i = 0; i < min_steps; ++i) {
           path += actions_so_far[i];
           if(i + 1 < min_steps) {
            path += "\n";
           }
         }
         break;
        }
     }

    // ============================================================
    // 1. ATOMIC ACTION: Flip ONE switch in current room (Cost: 1 step)
    // ============================================================
     auto toggle_actions = actions_so_far;
     for(int s : switches[curr_room]) {
       int bit = 1 << s;
       auto s_room = std::to_string(s + 1);
       if(!(lit_rooms & bit)) {
         // turn the light on
         int new_lit_rooms = lit_rooms;
         new_lit_rooms ^= bit;
         if(!visited[curr_room][new_lit_rooms]) {
           toggle_actions.push_back(turn_on + s_room + ".");
           visited[curr_room][new_lit_rooms] = true;
           queue.push({curr_room, new_lit_rooms, toggle_actions});
           toggle_actions.pop_back();
         }
       } else {
         if(s != curr_room) {
           int new_lit_rooms = lit_rooms;
           new_lit_rooms ^= bit;
           if(!visited[curr_room][new_lit_rooms]) {
             toggle_actions.push_back(turn_off + s_room + ".");
             visited[curr_room][new_lit_rooms] = true;
             queue.push({curr_room, new_lit_rooms, toggle_actions});
             toggle_actions.pop_back();
           }
         }
       }
     }

    // ============================================================
    // 2. ATOMIC ACTION: Move to an adjacent room (Cost: 1 step)
    // ============================================================
     auto move_actions = actions_so_far;
     for(int room : graph[curr_room]) {
       if((lit_rooms & (1 << room)) && 
          !visited[room][lit_rooms]) {
         auto s_room = std::to_string(room + 1);
         visited[room][lit_rooms] = true;
         move_actions.push_back(move + s_room + ".");
         queue.push({room, lit_rooms, move_actions});
         move_actions.pop_back(); // backtrack
       }
     }
   }

   if(!(~min_steps)) {
     return "The problem cannot be solved.";
   } else {
     return "The problem can be solved in " + std::to_string(min_steps) + " steps:" + (min_steps > 0 ? "\n" : "") + path;
   }
}


namespace algorithms::onlinejudge::advanced_topics::new_villa
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
        
        // R stands for rooms, D stands for doors connecting rooms, S - for switches
        int R, D, S, t_case = 1;
        while(std::cin >> R >> D >> S && R) {

          vvi graph(R);
          int from, to;
          vvi switches(R);
          for(int d = 0; d < D; ++d) {
            std::cin >> from >> to;
            --from; --to;
            graph[from].push_back(to);
            graph[to].push_back(from);
          }
          int switch_room, toggle;
          for(int s = 0; s < S; ++s) {
            std::cin >> switch_room >> toggle;
            --switch_room; --toggle;
            switches[switch_room].push_back(toggle);
          }


          printf("Villa #%d\n%s\n\n", t_case++, get_min_path_required(R, S, graph, switches).c_str());
        }
    }
}
