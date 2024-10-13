#include <cassert>
#include <optional>
#include <vector>
#include <cctype>
#include <queue>
#include <iostream>
#include <tuple>
#include <unordered_map>


namespace algorithms::graph::onlinejudge::food
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef unsigned long long ll;
typedef std::pair<int, int> cell;
typedef std::vector<char> vc;
typedef std::vector<std::vector<char>> vvc;
typedef std::vector<std::pair<int, int>> dirs;
typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;
typedef std::vector<vvb> vvvb;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
typedef std::queue<std::tuple<cell, int, int>> qs;
typedef std::unordered_map<int, cell> mi;


    /** https://onlinejudge.org/external/114/11487.pdf, 
     * state: row, col, current food, length; transition: 4 dirs 
     * For this problem, we are interested in the 3-rd example and we will be focusing on ‘Yogi Bear’.
     * Yogi Bear is in the middle of some forest. The forest can be modeled as a square grid of size N × N.
     * Each cell of the grid consists of one of the following: 
     * . an empty space, # an obstacle, [A-Z] an English alphabet
     * There will be at least 1 alphabet and all the letters in the grid will be distinct. If there are n letters,
     * then it will be from the first n alphabets. Suppose n = 3, that means there will be exactly 1 A, 1 B and 1 C.
     * The letters actually represent foods lying on the ground. Yogi starts from position ‘A’ and sets off
     * with a basket in the hope of collecting all other foods. Yogi can move to a cell if it shares an edge with
     * the current one. For some superstitious reason, Yogi decides to collect all the foods in order (1 constraint) . 
     * That is, he first collects A, then B, then C and so on until he reaches the food with the highest alphabet value.
     * Another philosophy he follows is that if he lands on a particular food he must collect it (2 constraint)
     * Help Yogi to collect all the foods in minimum number of moves so that he can have a long sleep in the winter. 
     * You are also required to find the total number of shortest paths he can take that meets the above constraints
     * Constraints: collect foods in alphabetical order, if a food is met it must be collected */
    int N;
    int foodToInt(char c) { return (int)c - 65; }
    const char start = 'A';
    const char obstacle = '#';
    const int modulo = 20437;
    bool canPass(int cf, int gf) { return cf + 1 == gf || cf >= gf; }
    dirs ds = { {0, -1}, /* right */ {-1, 0}, /* up */ {0, 1}, /* left */ {1, 0} /* down */ };
    bool checkBoundary(int r, int c)
    { return r >= 0 && r < N && c >= 0 && c < N; }
    int n_ways;
    vvvi ways;
    mi food_coords;
    vi food_dist;
    void bfs(const vvc& grid, qs& state, int target, vvvb& visited) 
    {

        if(state.empty()) return;
        std::tuple<cell, int, int> s = state.front(); state.pop();
        int c_r = std::get<0>(s).first;
        int c_c = std::get<0>(s).second;
        int dist = std::get<2>(s);
        int cf = std::get<1>(s);

        visited[c_r][c_c][cf] = true;
        for(auto d : ds)
        {
            int r = c_r + d.first;
            int c = c_c + d.second; 

            if(!checkBoundary(r, c) ||
                visited[r][c][cf] ||
                grid[r][c] == obstacle)
              continue;
            
            if(std::isalpha(grid[r][c]) &&
               !canPass(cf, foodToInt(grid[r][c])))
            {
                int food = foodToInt(grid[r][c]) - 1;
                cell coord = (*food_coords.find(food)).second;
                if(!visited[coord.first][coord.second][food])
                  visited[coord.first][coord.second][food] = true,
                  state.push({coord, food, 0});
            }
            else if(cf + 1 == foodToInt(grid[r][c]))
            {
                food_dist[cf + 1] = dist + 1;
                if(!visited[r][c][cf + 1] && 
                   cf + 1 != target)
                  visited[r][c][cf + 1] = true, 
                  state.push({{r, c}, cf + 1, 0});
                visited[r][c][cf] = true;
            }
            else 
            {
                if(food_dist[cf + 1] == INT32_MAX || (food_dist[cf + 1] != INT32_MAX && dist < food_dist[cf + 1]))
                  ways[cf][r][c] += 1;
                state.push({{r, c}, cf, dist + 1});
            }
        }
        bfs(grid, state, target, visited);
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int c = 0;
        while(std::cin >> N && N)
        {
            vvc grid;
            char v;
            cell s;
            char last_food = 'A';
            food_coords.clear();
            food_dist.clear();
            loop(i, 0, N)
            {
                vc col;
                loop(j, 0, N)
                {
                    std::cin >> v,
                    col.push_back(v);
                    if(v == start)
                    { s.first = i; s.second = j; }
                    if(std::isalpha(v))
                      food_coords.insert({foodToInt(v), {i, j}}),
                      last_food = std::max(last_food, v);
                }
                grid.push_back(col);
            }

            n_ways = 1;
            int MAX_FOOD = foodToInt(last_food);
            ways = vvvi(MAX_FOOD + 1, vvi(N, vi(N, 0)));
            vvvb visited = vvvb(N, vvb(N, vb(MAX_FOOD + 1, false)));
            visited[s.first][s.second][foodToInt(start)] = true;
            food_dist = vi(MAX_FOOD + 1, INT32_MAX);
            qs state;
            state.push({s, foodToInt(start), 0});
            bfs(grid, state, foodToInt(last_food), visited);

            int path = 0;
            loop(i, 1, MAX_FOOD + 1)
              if(food_dist[i] != INT32_MAX) 
                path += food_dist[i];
              else { path = INT32_MAX; break; }
  
            if(path != INT32_MAX)
              loop(i, 0, MAX_FOOD)
              {
                 int w = 0;
                 cell dest = (*food_coords.find(i + 1)).second;
                 for(auto d : ds)
                   if(checkBoundary(dest.first + d.first, dest.second + d.second))
                      w += ways[i][dest.first + d.first][dest.second + d.second];
                 n_ways *= (w != 0 ? w : 1);
                 n_ways %= modulo;
              }

            std::string ans = "Impossible";
            if(path != INT32_MAX) ans = std::to_string(path) + " " + std::to_string(n_ways);
            printf("Case %d: %s\n", ++c, ans.c_str());
        }
    }
}