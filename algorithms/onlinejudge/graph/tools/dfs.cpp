#include <vector>
#include <functional> // for std::function



namespace algorithms::onlinejudge::graph::tools
{
    enum State { Unvisited, Explored, Visited };

    typedef std::vector<int> vi;
    typedef std::vector<vi> vvi;
    typedef std::vector<State> v_state;

    struct Dfs
    {
        v_state state;
        vi entry_t;
        vi exit_t;
        vi parent;
        int time;
        std::function<void(int)> on_discover;
        std::function<void(int)> after_discover;
        // Tree edge: The edge traversed by DFS, i.e. an edge from a vertex currently with state:
        // EXPLORED to a vertex with state: UNVISITED
        std::function<void(int, int)> process_tree_edge;
        // Back edge: Edge that is part of a cycle, i.e. an edge from a vertex currently with state:
        // EXPLORED to a vertex with state: EXPLORED too. This is an important application of
        // this algorithm. Note that we usually do not count bi-directional edges as having a
        // ‘cycle’ (We need to remember dfs_parent to distinguish this, see the code below).
        std::function<void(int, int)> process_back_edge;
        // Forward/Cross edges from vertex with state: EXPLORED to vertex with state: VISITED
        std::function<void(int, int)> process_forward_edge;
        bool is_finished;
    };

    void dfs(const vvi& adj_list, Dfs& dfs_s, int u)
    {

        if(dfs_s.is_finished) return;

        dfs_s.state[u] = Explored;
        dfs_s.entry_t[u] = dfs_s.time;
        dfs_s.time++;
       
        if(dfs_s.on_discover) dfs_s.on_discover(u);

        for(int v : adj_list[u])
          if(dfs_s.state[v] == Unvisited) {
            if(dfs_s.process_tree_edge) 
              dfs_s.process_tree_edge(u, v);    
            dfs_s.parent[v] = u;
            dfs(adj_list, dfs_s, v);
          } else if(dfs_s.state[v] == Explored) {
            if(v != dfs_s.parent[u] && 
               dfs_s.process_back_edge)
              dfs_s.process_back_edge(u, v);   
          } else if(dfs_s.state[v] == Visited)
            if(dfs_s.process_forward_edge)
              dfs_s.process_forward_edge(u, v);

        dfs_s.state[u] = Visited;
        dfs_s.exit_t[u] = dfs_s.time;
        dfs_s.time++;

        if(dfs_s.after_discover) dfs_s.after_discover(u);
    }
}