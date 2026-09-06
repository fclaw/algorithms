/*
───────────────────────────────────────────────────────────────
🧳  Treasure Hunt, https://open.kattis.com/problems/treasurehunt, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int INF = (int)1e9; // Maximum number of nodes in the graph


using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;


/**
 * Terrain types mapped directly to their stamina cost to ENTER:
 *   - Plain    ('.' / 'S' / 'G') : Costs 1 stamina point
 *   - Forest   ('F')             : Costs 2 stamina points
 *   - Mountain ('M')             : Costs 3 stamina points
 *   - River    ('#')             : Impassable (infinite cost)
 **/
enum Terrain { PLAIN = 1, FOREST = 2, MOUNTAIN = 3, RIVER = INF }; // Terrain types with associated stamina costs, INF represents impassable terrain (RIVER)


struct State
{
    /**
     * 1. row, col (Current Coordinates)
     * -----------------------------
     * 2D position on the N x M grid (0 <= row < N, 0 <= col < M).
     * Starts at 'S' and ends at 'G'.
     */
    ii pos;

    /**
     * 2. stamina_left (Remaining Stamina Today)
     * -----------------------------------------
     * The stamina remaining on the CURRENT day (0 to K).
     * If stamina_left is not enough to enter the next cell, 
     * the hunter must camp and rest, resetting stamina to K on the next day!
     */
    int stamina_left;

    /**
     * 3. days (Total Days Elapsed / Cost Function g(n))
     * -------------------------------------------------
     * The number of days spent so far to reach this position.
     * The journey begins on Day 1.
     * This is the primary objective value we want to minimize!
     */
    int days;

    /**
     * 4. Priority Queue Min-Heap Comparator
     * -------------------------------------
     * 1. Primary Goal   : FEWER days popped first.
     * 2. Tie-Breaker    : If days are equal, MORE remaining stamina popped first!
     *                     (Having more stamina left on the same day is strictly better).
     */
    bool operator < (const State& other) const {
        return days > other.days; // Min-Heap on days
    }
};


  // Directional offsets: 0: Top, 1: Right, 2: Bottom, 3: Left
  const int dr[] = {-1, 0, 1, 0};
  const int dc[] = {0, 1, 0, -1};

int find_min_days(const std::vector<std::vector<Terrain>>& treasure_map, int ROW, int COL, int STAMINA, const ii& start, const ii& goal) {

  std::priority_queue<State> queue;
  vvvi day(ROW, vvi(COL, vi(STAMINA + 1, INF))); // Tracks the maximum stamina left when visiting each cell
    
    // init
    queue.push({start, STAMINA, 1}); // Start on Day 1 with full stamina
    day[start.first][start.second][STAMINA] = 1; // stamina
    
    while(!queue.empty()) {
      State state = queue.top(); queue.pop();
      ii pos = state.pos;
      int stamina_left = state.stamina_left;
      int days_so_far = state.days;

      // If we reached the goal, return the number of days spent
      if(pos == goal) {
        return days_so_far;
      }
    
      if(days_so_far > day[pos.first][pos.second][stamina_left]) {
        continue;
      }

      // Explore all four possible directions (up, down, left, right)
      for(int d = 0; d <= 3; ++d) {
        int new_row = pos.first + dr[d];
        int new_col = pos.second + dc[d];
    
        // Check bounds
        if(new_row < 0 || new_row >= ROW || new_col < 0 || new_col >= COL) continue;
    
        Terrain terrain_cost = treasure_map[new_row][new_col];
        if(terrain_cost == RIVER || 
           STAMINA < terrain_cost) {
          continue; // Skip impassable terrain
        }
    
        int new_stamina_left = stamina_left;
        int new_days_so_far = days_so_far;
        // CASE A: We have enough stamina to move TODAY:
        if (new_stamina_left >= terrain_cost) {
          new_stamina_left -= terrain_cost;
        } 
        // CASE B: Not enough stamina today -> Must CAMP overnight and move TOMORROW:
        else {
          new_days_so_far++; // Starts a new day!
          new_stamina_left = STAMINA - terrain_cost;      // Stamina was replenished to K, then spent C
        }
        
        // Only proceed if this path offers more remaining stamina than previously recorded
        if(new_days_so_far < day[new_row][new_col][new_stamina_left]) {
          day[new_row][new_col][new_stamina_left] = new_days_so_far;
          queue.push({{new_row, new_col}, new_stamina_left, new_days_so_far});
        }
      }
    }
    
    return -1; // If the goal is unreachable
}

namespace algorithms::kattis::bfs_dijkstra::treasure_hunt
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

        int ROW, COL, STAMINA;
        while(std::cin >> ROW >> COL >> STAMINA && ROW) {
          std::vector<std::vector<Terrain>> treasure_map(ROW, std::vector<Terrain>(COL));
          ii start, goal;
          for(int r = 0; r < ROW; ++r) {
            for(int c = 0; c < COL; ++c) {
              char cell;
              std::cin >> cell;
              switch(cell) {
                case '.': treasure_map[r][c] = PLAIN; break;
                case 'F': treasure_map[r][c] = FOREST; break;
                case 'M': treasure_map[r][c] = MOUNTAIN; break;
                case '#': treasure_map[r][c] = RIVER; break;
                case 'S': treasure_map[r][c] = PLAIN; start.first = r; start.second = c; break;
                case 'G': treasure_map[r][c] = PLAIN; goal.first = r; goal.second = c; break;
              }
            }
          }

          printf("%d\n", find_min_days(treasure_map, ROW, COL, STAMINA, start, goal));
        }
    }
}