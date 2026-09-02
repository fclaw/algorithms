/*
───────────────────────────────────────────────────────────────
🧳 UVa 10923 Seven Seas, https://onlinejudge.org/external/109/10923.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;


constexpr int ROWS = 9;
constexpr int COLS = 8;
constexpr int MAX_MOVE = 9;

struct State
{
    /**
     * 1. ships_pos (Player Ship Coordinates)
     * --------------------------------------
     * The (row, col) coordinates of Mario's ship 'S' on the 9 x 8 board.
     * Boundaries: 0 <= row < 9, 0 <= col < 8.
     */
    ii ships_pos;

    /**
     * 2. enemies (Active Enemy Ships Coordinates)
     * -------------------------------------------
     * A list of (r, c) positions of all SURVIVING enemy ships 'E'.
     * (There are at most 9 enemy ships in total: 1 <= enemies.size() <= 9).
     * 
     * 💡 Why coordinates are required (not just an integer count):
     * On each turn, every enemy ship moves deterministically towards the player 
     * using vector math: (sgn(player_r - enemy_r), sgn(player_c - enemy_c)).
     * We need their exact (r, c) locations to simulate their movement!
     * 
     * Win Condition: enemies.empty() (All enemies destroyed!).
     */
    vii enemies;

    /**
     * 3. grid_wrecks (Rocks & Permanent Shipwrecks)
     * ---------------------------------------------
     * The 9 x 8 board containing fixed obstacles:
     *   - '#' : Natural Rocks (from original input)
     *   - 'X' : Permanent Shipwrecks (created when enemy ships crash)
     * 
     * Rule: Any enemy ship that steps onto '#' or 'X' is destroyed!
     */
    vvi obstacles;

    /**
     * 4. moves (Turn Counter / Depth)
     * -------------------------------
     * The number of turns taken so far.
     * 
     * Win Condition Rule: Must destroy all enemies in LESS THAN 10 steps (moves <= 9).
     * If moves == 10 and enemies still exist ===> Prune / Dead branch!
     */
    int moves;
};

// Strictly the 8 directions:
const int dr[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
const int dc[8] = {-1,  0,  1, -1, 1, -1, 0, 1};

bool in_grid(int r, int c) { return r >= 0 && r < ROWS && c >= 0 && c < COLS; };

bool is_occupied_by_enemy(ii pos, vii enemies) {
  return std::find(enemies.begin(), enemies.end(), pos) != enemies.end();
}

/**
 * Calculates the direction unit vector (dr, dc) for an enemy ship 
 * to move 1 step directly towards the player's ship.
 * 
 * Each component is strictly -1, 0, or +1 based on sign:
 *   dr = sgn(ship_row - enemy_row)
 *   dc = sgn(ship_col - enemy_col)
 */
ii get_delta(ii ship_pos, ii enemy_pos) {
  int dr = (ship_pos.first > enemy_pos.first) - 
           (ship_pos.first < enemy_pos.first);
  int dc = (ship_pos.second > enemy_pos.second) - 
           (ship_pos.second < enemy_pos.second);  
  return {dr, dc};
}

std::string can_defeat(ii ship, const vii& enemies, const vvi& obstacles) {

  std::queue<State> queue;
  queue.push({ship, enemies, obstacles, 0});

  bool is_all_enemies_beaten = false;

  while(!queue.empty()) {
    State state = queue.front(); queue.pop();
    ii ships_pos = state.ships_pos;
    vii& enemies = state.enemies;
    vvi& obstacles = state.obstacles;
    int moves = state.moves;
    
    if(enemies.empty()) {
      is_all_enemies_beaten = true;
      break;
    }

    if(moves > MAX_MOVE) {
      continue;
    }

    //
    for(int i = 0; i < 8; ++i) {
      int new_ship_row =  ships_pos.first + dr[i];
      int new_ship_col = ships_pos.second + dc[i];
      ii new_ship_pos = {new_ship_row, new_ship_col};
      if(in_grid(new_ship_row, new_ship_col) && 
         !is_occupied_by_enemy(new_ship_pos, enemies) &&
         !obstacles[new_ship_row][new_ship_col]) {
        bool is_ship_caught = false;
        std::set<ii> new_enemies;
        vii new_wreckages;
        for(int i = 0; i < (int)enemies.size(); ++i) {
          ii old_enemy_pos = enemies[i];
          ii delta = get_delta(new_ship_pos, old_enemy_pos);
          ii new_enemy_pos = old_enemy_pos;
          new_enemy_pos.first += delta.first;
          new_enemy_pos.second += delta.second;
          // check whether the ship is caught
          if(new_enemy_pos == new_ship_pos) {
            is_ship_caught = true;
            break;
          }
          if(obstacles[new_enemy_pos.first][new_enemy_pos.second]) {
            continue;
          } else if (new_enemies.count(new_enemy_pos) > 0) {
            new_enemies.erase(new_enemy_pos); // Both ships destroyed!
            new_wreckages.push_back(new_enemy_pos); // Leaves a permanent wreck
          } else {
            new_enemies.insert(new_enemy_pos);
          }
        }
        if(is_ship_caught) {
          continue; // Prune dead branch instantly
        }
        vvi new_obstacles = obstacles;
        for(ii pos : new_wreckages) {
          new_obstacles[pos.first][pos.second] = 1;
        }
        vii v_new_enemies(new_enemies.begin(), new_enemies.end());
        queue.push({new_ship_pos, v_new_enemies, new_obstacles, 1 + moves});
      }
    }
  }

  return is_all_enemies_beaten ? "I'm the king of the Seven Seas!" : "Oh no! I'm a dead man!";
}


namespace algorithms::onlinejudge::advanced_topics::seven_seas
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

        int t_cases;
        std::cin >> t_cases;
        while(t_cases--) {
          char cell;
          ii ship;
          vii enemies;
          vvi obstacles(ROWS, vi(COLS));
          for(int r = 0; r < ROWS; ++r) {
            for(int c = 0; c < COLS; ++c) {
              std::cin >> cell;
              if(cell == 'S') {
                 ship.first = r;
                 ship.second = c;
              } else if (cell == 'E') {
                enemies.push_back({r, c});
              } else if (cell == '#') {
                obstacles[r][c] = 1;
              }
            }
          }
          printf("%s\n", can_defeat(ship, enemies, obstacles).c_str());
        }
    }
}