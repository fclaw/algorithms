#include <vector>
#include <functional> // for std::function
#include <algorithm>
#include <set>
#include <unordered_map>


namespace algorithms::onlinejudge::graph::tools
{
    enum State { Unvisited, Explored, Visited };
    enum CutNode { Leaf, Root, Parent, Bridge };

    typedef std::vector<int> vi;
    typedef std::vector<bool> vb;
    typedef std::vector<vi> vvi;
    typedef std::vector<State> v_state;
    typedef std::set<CutNode> s_cut_node;
    typedef std::vector<s_cut_node> vs_cut_node;

    int start_vertex = 0;

    struct Unit {};

    std::ostream& operator << (std::ostream& os, const Unit& u) { return os << "{}"; }

    template <typename T = Unit>
    struct Node 
    {
        const int node;
        T value;
    };

    typedef std::vector<std::vector<tools::Node<>>> vv_def_node;

    // Overload operator<< for Node<T>
    template <typename T>
    std::ostream& operator << (std::ostream& os, const Node<T>& n) 
    { return os << "{node: " << n.node << ", value: " << n.value << "}"; }

    template <typename T = Unit>
    struct Dfs
    {
        v_state state;
        vi entry_t;
        vi exit_t;
        vi parent;
        int time;
        int root_children;
        int root = start_vertex;
        std::function<void(Node<T>&)> on_discover;
        std::function<void(Node<T>&)> on_exit;
        // Tree edge: The edge traversed by DFS, i.e. an edge from a vertex currently with state:
        // EXPLORED to a vertex with state: UNVISITED
        std::function<bool(const Node<T>&, const Node<T>&)> process_tree_edge;
        // Back edge: Edge that is part of a cycle, i.e. an edge from a vertex currently with state:
        // EXPLORED to a vertex with state: EXPLORED too. This is an important application of
        // this algorithm. Note that we usually do not count bi-directional edges as having a
        // ‘cycle’ (We need to remember dfs_parent to distinguish this, see the code below).
        std::function<void(const Node<T>&, const Node<T>&)> process_back_edge;
        // Forward/Cross edges from vertex with state: EXPLORED to vertex with state: VISITED
        std::function<void(const Node<T>&, const Node<T>&)> process_forward_edge;
        std::function<void(const Node<T>&, const Node<T>&)> process_cross_edge;
        bool is_finished;

    };

    template <typename T = Unit>
    Dfs<T> init_dfs(int V) {
      Dfs<T> dfs_s;
      dfs_s.is_finished = false;
      dfs_s.state = tools::v_state(V, tools::Unvisited);
      dfs_s.time = 1;
      dfs_s.entry_t = tools::vi(V);
      dfs_s.exit_t = tools::vi(V);
      dfs_s.parent = tools::vi(V, -1);
      dfs_s.root_children = 0;
      return dfs_s;
    }


    template <typename T = Unit>
    void dfs(const std::vector<std::vector<Node<T>>>& adj_list, Dfs<T>& dfs_s, Node<T>& u)
    {

        if(dfs_s.is_finished) return;

        dfs_s.state[u.node] = Explored;
        dfs_s.entry_t[u.node] = dfs_s.time;
        dfs_s.time++;
       
        if(dfs_s.on_discover) dfs_s.on_discover(u);

        bool should_continue = true;
        for(Node<T> v : adj_list[u.node])
          if(dfs_s.state[v.node] == Unvisited) {
            if(dfs_s.process_tree_edge) 
              should_continue = dfs_s.process_tree_edge(u, v);
            
            if(!should_continue) continue; // ← Skip DFS if not allowed

            dfs_s.parent[v.node] = u.node;
            if (dfs_s.parent[u.node] == -1)  // u is root
              dfs_s.root_children++;
            dfs(adj_list, dfs_s, v);
          } else if(dfs_s.state[v.node] == Explored) {
            if(v.node != dfs_s.parent[u.node] && 
               dfs_s.process_back_edge)
              dfs_s.process_back_edge(u, v);
          } else if(dfs_s.state[v.node] == Visited) {
            if(dfs_s.entry_t[v.node] > dfs_s.entry_t[u.node])
              if(dfs_s.process_forward_edge)
                dfs_s.process_forward_edge(u, v);
            if(dfs_s.entry_t[v.node] < dfs_s.entry_t[u.node])
              if(dfs_s.process_cross_edge)
                dfs_s.process_cross_edge(u, v);      
          }

        dfs_s.state[u.node] = Visited;
        dfs_s.exit_t[u.node] = dfs_s.time;
        dfs_s.time++;

        if(dfs_s.on_exit) dfs_s.on_exit(u);
    }

    
    vi reachable_ancestor;
    vi tree_out_degree;
    vs_cut_node cut_nodes;

    void init_cut_nodes(int V) {
      reachable_ancestor.clear();
      tree_out_degree.clear();
      cut_nodes.clear();
      reachable_ancestor.resize(V);
      tree_out_degree.resize(V);
      cut_nodes.resize(V);
      for(auto& v : cut_nodes) v.insert(Leaf);
    }

    void init_ancestor(int v) { reachable_ancestor[v] = v; }
    void incr_tree_out_degree(int v) { tree_out_degree[v]++; }

    template <typename T = Unit>
    void set_ancestor(int u, int v, Dfs<T>& dfs) {
      if(dfs.entry_t[v] < dfs.entry_t[reachable_ancestor[u]] && dfs.parent[u] != v)
        reachable_ancestor[u] = v;
    }

    // ---- 3 possibilities -----

    // Root cut-nodes – If the root of the DFS tree has two or more children, it must
    // be an articulation vertex. No edges from the subtree of the second child can
    // possibly connect to the subtree of the first child.

    // Bridge cut-nodes – If the earliest reachable vertex from v is v, then deleting
    // the single edge (parent[v], v) disconnects the graph. Clearly parent[v] must
    // be an articulation vertex, since it cuts v from the graph. Vertex v is also an
    // articulation vertex unless it is a leaf of the DFS tree. For any leaf, nothing
    // falls off when you cut it.

    // Parent cut-nodes – If the earliest reachable vertex from v is the parent of v,
    // then deleting the parent must sever v from the tree unless the parent is the root.

    // The routine below systematically evaluates each of the three conditions as we
    // back up from the vertex after traversing all outgoing edges. We use entry time[v]
    // to represent the age of vertex v. The reachability time time v calculated below
    // denotes the oldest vertex that can be reached using back edges. Getting back to
    // an ancestor above v rules out the possibility of v being a cut-node:
    template <typename T = Unit> 
    void detect_cut_node(int v, Dfs<T>& dfs) {

        // Root cut-node case
        if(v == dfs.root) {
          if(dfs.root_children > 1)
            cut_nodes[v].insert(Root);
          return;
        }

        // Parent cut-node
        int p = dfs.parent[v];
        if (p != -1 && 
            p != dfs.root && 
            reachable_ancestor[v] == p)
          cut_nodes[p].insert(Parent);

        // Bridge cut-node
        if(reachable_ancestor[v] == v) {
          if(dfs.parent[v] != dfs.root)  
            cut_nodes[dfs.parent[v]].insert(Bridge);
          if(tree_out_degree[v] > 0)
            cut_nodes[v].insert(Bridge);
        }

        // Update reachable_ancestor of parent
        if (dfs.parent[v] != -1) {
          int time_v = dfs.entry_t[reachable_ancestor[v]];
          int time_parent = dfs.entry_t[reachable_ancestor[dfs.parent[v]]];
          if (time_v < time_parent) reachable_ancestor[dfs.parent[v]] = reachable_ancestor[v];
        }
    }

    struct Dir
    {
        int r_shift;
        int c_shift;
    };

    typedef std::vector<Dir> v_dir;

    // Default DAG directions: only right and down
    const v_dir dirs_4 = 
      { {-1, 0}, // up
        {1, 0},  // down
        {0, -1}, // left
        {0, 1}   // right
      };

    template <typename T, typename F = char>
    struct GridGraph {
      std::vector<std::vector<Node<T>>> adj;
      std::unordered_map<int, T> vertex_value;
      std::function<T(F)> cell_to_value;
    };

    template <typename T, typename F = char>
    void grid_to_adj_list(
      GridGraph<T, F>& g,
      const std::vector<std::vector<F>>& grid,
      v_dir directions = dirs_4,
      bool bidirectional = false) {

        int rows = grid.size();
        if (rows == 0) return;
        int cols = grid[0].size();

        g.adj.resize(rows * cols);

        auto in_bounds = [&](int r, int c) 
        { return r >= 0 && r < rows && c >= 0 && c < cols; };

        for(int r = 0; r < rows; ++r) {
          for(int c = 0; c < cols; ++c) {
            int u = r * cols + c;
            g.vertex_value[u] = g.cell_to_value(grid[r][c]);

            for(const Dir& d : directions) {
              int nr = r + d.r_shift, nc = c + d.c_shift;
              if(in_bounds(nr, nc)) {
                int v = nr * cols + nc;
                g.adj[u].push_back(Node<T>{v, g.cell_to_value(grid[nr][nc])});
                if(bidirectional) g.adj[v].push_back(Node<T>{u, g.cell_to_value(grid[r][c])});
              }
            }
          }
        }
    }
}