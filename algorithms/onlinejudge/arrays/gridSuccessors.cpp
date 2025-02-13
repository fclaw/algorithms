#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>


typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
using dir = std::vector<std::pair<int, int>>;
#define loop(x, s, n) for(int x = s; x < n; x++)
const int STATES_SIZE = 513;
const int GRID_SIZE = 3;

namespace algorithms::onlinejudge::arrays::grid_successors
{
    dir dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < GRID_SIZE && c >= 0 && c < GRID_SIZE; }
    // https://onlinejudge.org/external/115/11581.pdf, simulate the process
    int getState(const vvi& grid)
    {
        int state = 0;
        loop(i, 0, GRID_SIZE)
          loop(j, 0, GRID_SIZE)
            if(grid[i][j] == 1)
              state |= (1 << (i * GRID_SIZE + j));
        return state;
    }
    void transform(const vvi& grid, vvi& tmp)
    {
        loop(i, 0, GRID_SIZE)
          loop(j, 0, GRID_SIZE)
          {
             int val = 0;
             for(auto d : dirs)
             {
                int next_i = i + d.first;
                int next_j = j + d.second;
                bool ok = checkBoundary(next_i, next_j);
                if(ok) val += grid[next_i][next_j];
             }
             tmp[i][j] = val % 2;
          }
    }
    int getMaxStreakOfDistinctGrids(vvi& grid) 
    {
        vi states = vi(STATES_SIZE);
        fill(states.begin(), states.end(), -1);  // Mark all states as unvisited
        vvi tmp = vvi(GRID_SIZE, vi(GRID_SIZE));
        int init_state = getState(grid);
        states[init_state] = 0;
        int incr = 0;
        while(true)
        {
            transform(grid, tmp);
            int s = getState(tmp);
            if(states[s] != -1) break;  // If already seen, we found a cycle
            states[s] = ++incr;  // Store step number
            grid = tmp;
        }
        return --incr;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        std::cin.ignore();
        while(tc--)
        {
            vvi grid = vvi(GRID_SIZE, vi(GRID_SIZE));
            std::string line;
            loop(i, 0, GRID_SIZE)
            {
                std::cin >> line;
                loop(j, 0, GRID_SIZE)
                  grid[i][j] = line[j] - '0';
            }

            int ans = getMaxStreakOfDistinctGrids(grid);
            std::cout << (ans != -1 ? ans : -1) << std::endl;
            std::cin.ignore();
        }
    }
}