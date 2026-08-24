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


// #define DEBUG 

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

std::string get_min_path_required(int R, int S, const vvi& graph, const vvi& switches) {

   std::queue<State> queue;
   vvb visited(R, vb(1 << R, false));
   // init
   queue.push({0, (1 << 0), {}});
   visited[0][1 << 0] = true;
   
   // ans
   int min_steps = -1;
   std::string path;
  
   while(!queue.empty()) {
     State state =  queue.front(); queue.pop();
     int curr_room = state.room;
     int lit_rooms = state.lit_rooms;
     auto actions_so_far = state.actions;

     
    #ifdef DEBUG
    std::cerr << "========================================\n";
    std::cerr << "📍 Room: " << (state.room + 1) 
            << " | 💡 Lit Rooms: " << std::bitset<10>(state.lit_rooms) 
            << " | 👣 Steps: " << actions_so_far.size() << "\n";
    std::cerr << "Actions so far:\n";

    for (size_t i = 0; i < actions_so_far.size(); ++i) {
        std::cerr << "  " << (i + 1) << ". " << actions_so_far[i] << "\n";
    }
    std::cerr << "========================================\n";
    #endif


     if(curr_room == R - 1) {
       if(lit_rooms == (1 << (R - 1))) {
          min_steps = (int)actions_so_far.size();
          for(auto a : actions_so_far) {
            path += a + "\n";   
          }
          path.pop_back();
          break;
       }
     }

     // try all combination of switches
     int SIZE = (int)switches[curr_room].size();
     for(int com = 0; com < (1 << SIZE); ++com) {
       auto new_actions_so_far = actions_so_far;
       int new_lit_rooms = lit_rooms;
       bool is_light_off_in_curr_room = false;
       for(int i = 0; i < SIZE; ++i) {
         if((com & (1 << i))) {
           int val = switches[curr_room][i];
           int bit = 1 << val;
           auto s_room = std::to_string(val + 1);
           if(!(new_lit_rooms & bit)) {
            // turn the light on
            new_actions_so_far.push_back("- Switch on light in room " + s_room + ".");
           } else {
             if(val != curr_room) {
               new_actions_so_far.push_back("- Switch off light in room " + s_room + ".");
             } else {
               is_light_off_in_curr_room = true;
             }
           }
           if(val != curr_room || 
              !is_light_off_in_curr_room) { // Mr. Black never stays in a dark room
             new_lit_rooms ^= bit; // toggle
           }
         }
       }

       // stay 
       if(!visited[curr_room][new_lit_rooms]) {
         visited[curr_room][new_lit_rooms] = true;
         queue.push({curr_room, new_lit_rooms, new_actions_so_far});
       }

       // move
       for(int room : graph[curr_room]) {
         if((new_lit_rooms & (1 << room)) && 
            !visited[room][new_lit_rooms]) {
          auto s_room = std::to_string(room + 1);
          visited[room][new_lit_rooms] = true;
          new_actions_so_far.push_back("- Move to room " + s_room + ".");
          queue.push({room, new_lit_rooms, new_actions_so_far});
         }
       }
     }
   }

   if(!(~min_steps)) {
     return "The problem cannot be solved.";
   } else {
     return "The problem can be solved in " + std::to_string(min_steps) + " steps:\n" + path;
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
        bool is_first = true;
        while(std::cin >> R >> D >> S && R) {

          if(is_first) {
            is_first = false;
          } else {
            std::cout << std::endl;
          }

          if(D == 0 && S == 0) {
            printf("Villa #%d\nThe problem can be solved in 0 steps:\n", t_case++);
            continue;
          }

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
          printf("Villa #%d\n%s\n", t_case++, get_min_path_required(R, S, graph, switches).c_str());
        }
    }
}
