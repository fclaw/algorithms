
#include <cassert>
#include <optional>
#include <vector>
#include <cctype>
#include <unordered_map>

namespace algorithms::graph::onlinejudge::food
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::pair<int, int> cell;
typedef std::vector<char> vc;
typedef std::vector<std::vector<char>> vvc;
typedef std::vector<std::pair<int, int>> dirs;
typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;



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
    bool isBlockedFood(int x, char y) 
    { return !(x + 1 == foodToInt(y)) && x < foodToInt(y); }
    const char start = 'A';
    const char obstacle = '#';
    const int modulo = 20437;
    char curr_food;
    int length = 0;
    std::unordered_map<int, int> foods_length;
    dirs ds = { {0, 1}, /* left */ {0, -1}, /* right */  {1, 0}, /* down */ {-1, 0} /* up */ };
    bool checkBoundary(int r, int c)
    { return r >= 0 && r < N && c >= 0 && c < N; }
    void collectAllFoods(const vvc& grid, cell c, int cf, int l, vvb& visited) 
    {
        for(auto d : ds)
        {
            int y = c.first + d.first;
            int x = c.second + d.second;
            if(!checkBoundary(y, x) || 
               visited[y][x])
              continue;
            if(grid[y][x] == obstacle ||
               (std::isalpha(grid[y][x]) && 
                isBlockedFood(cf, grid[y][x])))
              continue;

            visited[y][x] = true;
            
            int new_cf = cf;
            if(std::isalpha(grid[y][x]) && 
               foodToInt(grid[y][x]) != cf)
            {
                if(auto it = foods_length.find(foodToInt(grid[y][x]));
                  it == foods_length.end())
                  foods_length[foodToInt(grid[y][x])] = l;
                else foods_length[foodToInt(grid[y][x])] = 
                       std::min(foods_length[foodToInt(grid[y][x])], l);   
                new_cf = foodToInt(grid[y][x]);  
            }
            collectAllFoods(grid, {y, x}, new_cf, l + 1, visited);
            visited[y][x] = false;
        }
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int c = 0;
        while(std::cin >> N)
        {
            if(N == 0) break;
            vvc grid;
            vc col;
            char v;
            cell s;
            char last_food;
            loop(i, 0, N)
            {
                loop(j, 0, N)
                {
                    std::cin >> v,
                    col.push_back(v);
                    if(v == start)
                    { s.first = i; s.second = j; }
                    if(std::isalpha(v)) 
                      last_food = std::max(last_food, v);
                }
                grid.push_back(col);
                col.clear();
            }
            vvb visited(N, vb(N, false));
            visited[s.first][s.second] = true;
            collectAllFoods(grid, s, foodToInt('A'), 0, visited);
            for(auto x : foods_length) cout << "food: " << x.first << ", dist: " << x.second << "\n";
            // std::string ans = curr_food == last_food ? std::to_string(collectAllFoods(grid, s, s)) : "Impossible";
            // printf("Case %d: %s\n", ++c, ans.c_str());
        }
    }
}