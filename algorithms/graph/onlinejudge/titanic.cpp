#include <vector>
#include <tuple>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <cassert>
#include "../edmonds_karp.cpp"

namespace algorithms::graph::onlinejudge::titanic
{

typedef int capacity;
typedef std::tuple<int, int, capacity> edge;
typedef std::vector<edge> graph;
typedef std::vector<int> ve;

namespace mf = algorithms::graph::max_flow;


    /** https://onlinejudge.org/external/113/11380.pdf */
    /** To model the flow graph, we use the following thinking steps.we first
     *  connect non ‘∼’ cells together with large capacity (1000 is enough for this problem). This
     *  describes the possible movements in the grid. We set vertex capacities of ‘*’
     *  and ‘.’ cells to 1 to indicate that they can only be used once. Then, we set vertex capacities
     *  of ‘@’ and ‘#’ to a large value (inf) to indicate that they can be used several times.
     *  Create a source vertex s and sink vertex t. Source s is linked to all ‘*’
     *  cells in the grid with capacity 1 to indicate that there is one person to be saved. All ‘#’
     *  cells in the grid are connected to sink t with capacity P to indicate that the large wood can
     *  be used P times. Now, the required answer—the number of survivor(s)—equals to the max
     *  flow value between source s and sink t of this flow graph. As the flow graph uses vertex 
     *   capacities, we need to use the vertex splitting technique */
    int maxSurvivors(int V, const graph& g, const ve& people, const ve& woods, capacity wc) 
    {
        mf::MAX_V = V;
        mf::source = 0;
        mf::sink = V - 1;
        mf::residual_graph.resize(mf::MAX_V);
        for(auto& x : mf::residual_graph)
          x.resize(mf::MAX_V);

        for(int i = 0; i < mf::MAX_V; i++)
          for(int j = 0; j < mf::MAX_V; j++)
            mf::residual_graph[i][j] = 0;
        
        for(edge t : g)
        {
            int from = std::get<0>(t);
            int to = std::get<1>(t);
            capacity cap = std::get<2>(t);
            mf::residual_graph[from][to] = cap;
        }

        for(auto p : people) mf::residual_graph[mf::source][p] = 1;
        for(auto w : woods) mf::residual_graph[w][mf::sink] = wc;

        mf::edmonds_karp();
        return mf::max_flow;
    }
}

/** People staying on floating ice. People want to move from here as the floating ice cannot carry
 *  them for long time. Once a people move from here, the floating ice will get drowned. People can
 *  move to any of the four directions (north, east, west and south) 
 *  usage: 1, capacity: 1 */
const char ppl = '*';
/** Water. People cannot go or move through them as water is extremely cold and not good enough for swimming 
 *  usage: 0, capacity: 0 */
const char water = '~';
/** Floating ice. People can move to a floating ice. But floating ices are so light that they cannot
 * float for long time, so people should move from here as soon as possible and once a people move 
 * from here, the floating ice will get drowned. 
 * usage: 1, capacity: 1 */
const char floating_ice = '.';
/** Large iceberg. People can move here but cannot stay here as they are extremely cold. These
 * icebergs will remain floating all the time. Note that, no two people can stay on floating ice or 
 * large iceberg at the same time 
 *  usage: inf, capacity: 1 */
const char iceberg = '@';
/** Large wood. This place is safe. People can move and stay here until the helping ships arrive.
 * A large wood will get drowned if more than P people stay on it at the same time. 
 *  usage: inf, capacity: P */
const char wood = '#';

const int inf = 5 * 1e+05;

enum Cell { Water, People, FloatingIce, Iceberg, Wood };
namespace titanic = algorithms::graph::onlinejudge::titanic;

typedef std::vector<std::vector<std::pair<int, Cell>>> mtx;
typedef std::unordered_map<int, int> se;

int SEA_N, SEA_M;

std::vector<std::pair<int, int>> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
bool checkBoundary(int y, int x) { return y >= 0 && y < SEA_M && x >= 0 && x < SEA_N; }


void mkEdge(const mtx& sea, titanic::graph& g, int r, int c, titanic::ve& people, titanic::ve& woods, se& items, int& vertices)
{
    int v = std::get<0>(sea[r][c]);
    Cell vty = std::get<1>(sea[r][c]);
    if(vty == Water) return;
    else if(vty == People)
    {
        people.push_back(v);
        for(auto d : dirs)
        {
            int y = r + d.first;
            int x = c + d.second;
            int u = std::get<0>(sea[y][x]);
            int uty = std::get<1>(sea[y][x]);
            if(!checkBoundary(y, x) || 
               uty == Water)
              continue;
            if(uty != People)
              g.push_back({v, u, 1});
        }
    }
    else
    {
        int y;
        int x;
        for(auto d : dirs)
        {
            int y = r + d.first;
            int x = c + d.second;
            int u = std::get<0>(sea[y][x]);
            int uty = std::get<1>(sea[y][x]);
            if(!checkBoundary(y, x) ||
               uty == Water ||
               uty == People)
               continue;
            if(uty == FloatingIce || 
               vty == FloatingIce)
              g.push_back({v, u, 1});
            else g.push_back({v, u, inf});
        }
        if(vty == FloatingIce)
          items.insert({v, vertices++});
        if(vty == Wood) woods.push_back(v);
    }
}

void submit_titanic(std::optional<char*> file)
{
    if(file.has_value())
      assert(freopen(file.value(), "r", stdin) != NULL);
    int rows, cols, wc;
    while(std::cin >> rows >> cols >> wc)
    {
        titanic::graph g;
        titanic::ve people;
        titanic::ve woods;
        se items; // splitted items
        mtx sea;
        int r = rows;
        int vertices  = 1;
        SEA_N = cols;
        SEA_M = rows;
        while(--r >= 0)
        {
            std::string line;
            std::cin >> line;
            std::vector<std::pair<int, Cell>> cs;
            for(auto c : line)
            {
                Cell cl;
                if(c == ppl) cl = People;
                if(c == water) cl = Water;
                if(c == floating_ice) cl = FloatingIce;
                if(c == iceberg) cl = Iceberg;
                if(c == wood) cl = Wood;
              int vertex = c == water ? 0 : vertices++;
              cs.push_back({vertex, cl});
            }
            sea.push_back(cs);
        }

        for(int r = 0; r < rows; r++)
          for(int c = 0; c < cols; c++) 
            mkEdge(sea, g, r, c, people, woods, items, vertices);

        // split floating ices
        for(auto& t : g)
        {
            int from = std::get<0>(t);
            int to = std::get<1>(t);
            titanic::capacity cap = std::get<2>(t);
            if(auto it = items.find(from); 
               it != items.end())
            {
                int u = (*it).second;
                std::get<1>(t) = u;
                g.push_back({u, to, cap});
            }
        }

        printf("%d\n", titanic::maxSurvivors(++vertices, g, people, woods, wc));
    }
}