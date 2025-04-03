#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <bitset>
#include <algorithm>




typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<vi> vvi;
typedef std::unordered_set<int> si;
typedef std::vector<std::pair<int, int>> vpii;
typedef std::vector<std::pair<bool, int>> vpbi;


namespace algorithms::onlinejudge::complete_search::graph_colouring
{
   
    /** https://onlinejudge.org/external/1/193.pdf, Max Independent Set, input is small */
    const size_t MAX = 101;
    enum Colour { WHITE, BLACK };
    vvi solution;
    void dfs(const vvi& graph, int u, vb& visited, vi& nodes)
    {
        visited[u] = true;
        for(int v : graph[u])
          if(!visited[v])
            nodes.push_back(v),
            dfs(graph, v, visited, nodes);
    }
    bool checkNeighbours(const vvi& graph, int u, const vpbi& visited)
    {
        bool all_white = true;
        for(int neigh : graph[u])
          if(visited[neigh].first && 
             visited[neigh].second == BLACK)
          { all_white = false; break; }   
        return all_white;
    }
    // Remove conflicts before merging
    vi filterValidBlacks(const vvi& graph, const vi& branch, const vi& local) 
    {
        auto isValidBlackNode = 
          [&graph](int node, const vi& local) 
          {
              for(int neigh : graph[node])
              if(std::find(local.begin(), local.end(), neigh) != local.end())
                return false; // Conflict detected
              return true;
          };

        vi filtered;
        for(int node : branch) 
          if(isValidBlackNode(node, local)) 
            filtered.push_back(node);
        return filtered;
    }
    vi backtrack(const vvi& graph, int u, vpbi visited, Colour colour)
    {
        vi local;
        visited[u] = {true, colour};
        for(int v : graph[u])
          if(!visited[v].first)
          {
             vi b_branch, w_branch;
             if(colour == WHITE &&
                checkNeighbours(graph, v, visited))
             {
                vpbi b_visited = visited;
                b_visited[v] = {true, BLACK};
                b_branch = backtrack(graph, v, b_visited, BLACK);
             }
             vpbi w_visited = visited;
             w_visited[v] = {true, WHITE};
             w_branch = backtrack(graph, v, w_visited, WHITE);
             
             // Step 2: Process branches
             b_branch = filterValidBlacks(graph, b_branch, local);
             w_branch = filterValidBlacks(graph, w_branch, local);

             // Step 3: Compare branches and merge
             if(b_branch.size() > w_branch.size()) 
               local.insert(local.end(), b_branch.begin(), b_branch.end());
             else if (b_branch.size() < w_branch.size()) 
                local.insert(local.end(), w_branch.begin(), w_branch.end());
            else 
                local.insert(
                  local.end(), 
                  (b_branch < w_branch) ? b_branch.begin() : w_branch.begin(), 
                  (b_branch < w_branch) ? b_branch.end() : w_branch.end());
            }
          
        // Add current node if it's black
        if(colour == BLACK) local.push_back(u);
        return local;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            solution.clear();
            int V, E;
            std::cin >> V >> E;
            vvi graph(V);
            int u, v;
            for(int i = 0; i < E; i++)
            {
                std::cin >> u >> v;
                --u; --v;
                graph[u].push_back(v);
                graph[v].push_back(u);
            }

            vvi components;
            vb visited(V, false);
            for(int v = 0; v < V; v++)
              if(!visited[v])
              {
                  vi nodes;
                  nodes.push_back(v);
                  dfs(graph, v, visited, nodes);
                  components.push_back(nodes);
              }

            for(auto xs : components)
            {
                if(xs.size() == 1) 
                { solution.push_back(xs); continue; }

                 // first node white
                vpbi visited(V, {false, WHITE});
                // si w_blacks;
                vi w_blacks = backtrack(graph, xs.front(), visited, WHITE);
                std::sort(w_blacks.begin(), w_blacks.end());
                w_blacks.erase(std::unique(w_blacks.begin(), w_blacks.end() ), w_blacks.end());

                // // black
                std::fill(visited.begin(), visited.end(), std::make_pair(false, WHITE));
                vi b_blacks = backtrack(graph, xs.front(), visited, BLACK);
                std::sort(b_blacks.begin(), b_blacks.end());
                b_blacks.erase(std::unique(b_blacks.begin(), b_blacks.end() ), b_blacks.end());

                if(w_blacks.size() > b_blacks.size())
                  solution.push_back(vi(w_blacks.begin(), w_blacks.end()));
                else solution.push_back(vi(b_blacks.begin(), b_blacks.end()));
            }

            int size = 0;
            std::string s;
            vi tmp;
            for(auto set : solution)
            {
                size += set.size();
                for(int v : set)
                  tmp.push_back(v + 1);
            }
            std::sort(tmp.begin(), tmp.end());
            for(int x : tmp) s += std::to_string(x) + " ";
            if(size == 0) printf("Error!\n");
            else { s.pop_back(); std::cout << size << std::endl << s << std::endl; }
            std::cin.ignore();
        }
    }
}