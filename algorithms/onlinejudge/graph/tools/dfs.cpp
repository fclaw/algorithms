#include <vector>
#include <functional> // for std::function
#include <algorithm>
#include <set>
#include <unordered_map>
#include <set>
#include <stack>
#include <cassert>
#include <stdexcept>


namespace algorithms::onlinejudge::graph::tools
{
    enum State { Unvisited, Explored, Visited };
    enum CutNode { Leaf, Root, Parent, Bridge };

    struct Edge
    {
        const int from;
        const int to;
        Edge(int a, int b) : from(std::min(a, b)), to(std::max(a, b)) {}
    };

    bool operator < (const Edge& lhs, const Edge& rhs) 
    { return lhs.from < rhs.from || (lhs.from == rhs.from && lhs.to < rhs.to); }
     bool operator == (const Edge& lhs, const Edge& rhs) 
     { return lhs.from == rhs.from && lhs.to == rhs.to; }

    std::ostream& operator << (std::ostream& os, const Edge& e) 
    { return os << "{" << e.from << ", " << e.to << "}"; }

    typedef std::vector<int> vi;
    typedef std::vector<bool> vb;
    typedef std::vector<vi> vvi;
    typedef std::vector<State> v_state;
    typedef std::set<CutNode> s_cut_node;
    typedef std::vector<s_cut_node> vs_cut_node;
    typedef std::set<Edge> s_cut_edge;

    int start_vertex = 0;

    struct Unit {};

    std::ostream& operator << (std::ostream& os, const Unit& u) { return os << "{}"; }

    template <typename T = Unit>
    struct Node 
    {
        int node;
        T value;
    };

    Node<> def_node = {0, {}};
 
    Node<> mkDefNode(int v) { return {v, {}}; }

    typedef std::vector<tools::Node<>> v_def_node;
    typedef std::vector<std::vector<tools::Node<>>> vv_def_node;

    template <typename T>
    using Graph = std::vector<std::vector<Node<T>>>;

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
        int& root = start_vertex;
        std::function<void(Node<T>&)> on_discover;
        std::function<void(Node<T>&)> on_leaving;
        // Tree edge: The edge traversed by DFS, i.e. an edge from a vertex currently with state:
        // EXPLORED to a vertex with state: UNVISITED
        std::function<bool(const Node<T>&, const Node<T>&)> process_tree_edge;
        // Back edge: Edge that is part of a cycle, i.e. an edge from a vertex currently with state:
        // EXPLORED to a vertex with state: EXPLORED too. This is an important application of
        // this algorithm. Note that we usually do not count bi-directional edges as having a
        // ‘cycle’ (We need to remember dfs_parent to distinguish this, see the code below).
        std::function<void(const Node<T>&, const Node<T>&)> process_back_edge;
        /* Forward/Cross edges from vertex with state: EXPLORED to vertex with state: VISITED (only for Directed Graphs)
           Edge classification in DFS (Directed Graphs):
            - Forward Edge:
                An edge from a node `u` to a descendant `v` in the DFS tree,
                but not the edge that first discovered `v`.
                Example: u → v, where `v` is in the subtree of `u`, but not directly.

            - Cross Edge:
                An edge from a node `u` to a previously visited node `v` that is
                neither an ancestor nor a descendant in the DFS tree.
                It connects different DFS branches or finished subtrees.
                Example: u → v, where DFS has already finished processing `v`.

            Note: These edge types do not apply to undirected graphs.
        */
        std::function<void(const Node<T>&, const Node<T>&)> process_forward_edge;
        std::function<void(const Node<T>&, const Node<T>&)> process_cross_edge;
        bool is_finished;

    };

    const int sentinel = -1;

    template <typename T = Unit>
    Dfs<T> init_dfs(int V) {
      Dfs<T> dfs_s;
      dfs_s.is_finished = false;
      dfs_s.state = tools::v_state(V, tools::Unvisited);
      dfs_s.time = 1;
      dfs_s.entry_t = tools::vi(V);
      dfs_s.exit_t = tools::vi(V);
      dfs_s.parent = tools::vi(V, sentinel);
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
        for(Node<T> v : adj_list[u.node]) {
          if(dfs_s.state[v.node] == Unvisited) {
            if(dfs_s.process_tree_edge) 
              should_continue = dfs_s.process_tree_edge(u, v);
            
            if(!should_continue) continue; // ← Skip DFS if not allowed

            dfs_s.parent[v.node] = u.node;
            if (dfs_s.parent[u.node] == sentinel)  // u is root
              dfs_s.root_children++;
            dfs(adj_list, dfs_s, v);
          } else if(dfs_s.state[v.node] == Explored) {
            if(dfs_s.process_back_edge)
              dfs_s.process_back_edge(u, v);
          } else if(dfs_s.state[v.node] == Visited) {
            if(dfs_s.entry_t[v.node] > dfs_s.entry_t[u.node])
              if(dfs_s.process_forward_edge)
                dfs_s.process_forward_edge(u, v);
            if(dfs_s.entry_t[v.node] < dfs_s.entry_t[u.node])
              if(dfs_s.process_cross_edge)
                dfs_s.process_cross_edge(u, v);      
          }
        }

        dfs_s.state[u.node] = Visited;
        dfs_s.exit_t[u.node] = dfs_s.time;
        dfs_s.time++;

        if(dfs_s.on_leaving) dfs_s.on_leaving(u);
    }

    
    vi reachable_ancestor;
    vi tree_out_degree;
    vs_cut_node cut_nodes;
    s_cut_edge cut_edges;


    void init_cut_points(int V) {
      reachable_ancestor.clear();
      tree_out_degree.clear();
      cut_nodes.clear();
      cut_edges.clear();
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
        // subtree of u hits one of ancestors v 
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
    void detect_cut_points(int v, Dfs<T>& dfs) {

        // Root cut-node case
        if(v == dfs.root) {
          if(dfs.root_children > 1)
            cut_nodes[v].insert(Root);
          return;
        }

        // Parent cut-node
        int p = dfs.parent[v];
        if (p != sentinel && 
            p != dfs.root && 
            reachable_ancestor[v] == p)
          cut_nodes[p].insert(Parent);

        // Bridge cut-node
        if(reachable_ancestor[v] == v) {
          if(dfs.parent[v] != dfs.root && 
             dfs.parent[v] != sentinel)
            cut_nodes[dfs.parent[v]].insert(Bridge);
          if(tree_out_degree[v] > 0) {
            cut_nodes[v].insert(Bridge);
          }
          
          // This line detects bridges  
          if(dfs.parent[v] != sentinel) cut_edges.insert({dfs.parent[v], v});
        }

        // Update reachable_ancestor of parent
        if (dfs.parent[v] != sentinel) {
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


    const v_dir dirs_8 = {
        {-1,  0}, // up
        { 1,  0}, // down
        { 0, -1}, // left
        { 0,  1}, // right
        {-1, -1}, // upper-left
        {-1,  1}, // upper-right
        { 1, -1}, // lower-left
        { 1,  1}  // lower-right
    };

    template <typename T, typename F = char>
    struct GridGraph {
      Graph<T> adj;
      std::unordered_map<int, T> vertex_value;
      std::function<T(F)> cell_to_value;
    };

    template <typename T, typename F = char>
    GridGraph<T> init_grid_graph(int R, int C) {
      Graph<T> graph;
      std::unordered_map<int, T> vertex_value;
      return GridGraph<T>{graph, vertex_value};
    }


    template <typename T, typename F = char>
    void grid_to_adj_list(
      GridGraph<T, F>& g,
      const std::vector<std::vector<F>>& grid,
      v_dir directions = dirs_4,
      bool bidirectional = false,
      bool scroll_x = false,
      bool scroll_y = false) {

        if(!g.cell_to_value)
          throw std::runtime_error("grid_to_adj_list: cell_to_value not set!");

        int rows = grid.size();
        if (rows == 0) return;
        int cols = grid[0].size();

        g.adj.resize(rows * cols);

        auto wrap = 
          [&](int r, int c) -> std::pair<int, int> {
            if(scroll_y) r = (r + rows) % rows;
            if(scroll_x) c = (c + cols) % cols;
            return {r, c};
          };

        auto in_bounds = 
          [&](int r, int c) {
            return (!scroll_y ? (r >= 0 && r < rows) : true) &&
                   (!scroll_x ? (c >= 0 && c < cols) : true);
          };

        for(int r = 0; r < rows; ++r) {
          for(int c = 0; c < cols; ++c) {
            int u = r * cols + c;
            g.vertex_value[u] = g.cell_to_value(grid[r][c]);
            for(const Dir& d : directions) {
              int nr = r + d.r_shift, nc = c + d.c_shift;
              if(!in_bounds(nr, nc)) continue;
              auto [wr, wc] = wrap(nr, nc);
              int v = wr * cols + wc;
              g.adj[u].push_back(Node<T>{v, g.cell_to_value(grid[wr][wc])});
              if(bidirectional) {
                g.adj[v].push_back(Node<T>{u, g.cell_to_value(grid[r][c])});
              }
            }
          }
        }
    }

    // strongly connected components
    // we are mostly concerned with back and cross edges
    // cross edges that point vertices
    // from previous strongly connected components of the graph cannot help us, because
    // there can be no way back from them to v, but otherwise cross edges are fair game.
    // Forward edges have no impact on reachability over the depth-first tree edges, and
    // hence can be disregarded
    template<typename T = Unit>
    struct SCC
    {
        //  Define low[v] to be the oldest vertex known to be in the same strongly connected
        // component as v. This vertex is not necessarily an ancestor, but may also
        // be a distant cousin of v because of cross edges
        vi low;
        vi components;
        int count;
        std::stack<int> active_comp;
        SCC(int V) : count(0) {
          low.resize(V);
          components.resize(V);
          for(int v = 0; v < V; ++v) {
            low[v] = v;
            components[v] = sentinel;
          }
        }
    };

    template<typename T = Unit>
    void handle_back_edge(
      Dfs<T>& dfs,
      SCC<T>& scc,
      const Node<T>& u, 
      const Node<T>& v) {
        if(dfs.entry_t[v.node] < 
           dfs.entry_t[scc.low[u.node]])
          scc.low[u.node] = v.node;
    }

    template<typename T = Unit>
    void handle_cross_edge(
      Dfs<T>& dfs,
      SCC<T>& scc,
      const Node<T>& u, 
      const Node<T>& v) {
        if(scc.components[v.node] == sentinel) {
          if(dfs.entry_t[v.node] < 
             dfs.entry_t[scc.low[u.node]])
            scc.low[u.node] = v.node;
        }
    }
    template<typename T = Unit>
    void handle_on_discover(SCC<T>& scc, Node<T>& u) 
    { scc.active_comp.push(u.node); }

    // A new strongly connected component is found whenever the lowest reachable
    // vertex from v is v. If so, we can clear the stack of this component. Otherwise, we
    // give our parent the benefit of the oldest ancestor we can reach and backtrack
    template<typename T = Unit>
    void handle_on_leaving(
      SCC<T>& scc, 
      Dfs<T>& dfs, 
      Node<T>& u) {
      
      assert(!scc.active_comp.empty() && "handle_on_leaving:stack is empty!!");  

      if(scc.low[u.node] == u.node && 
         !scc.active_comp.empty()) 
        pop_component(scc, u.node);
      if(dfs.parent[u.node] != sentinel) {  
        if(dfs.entry_t[scc.low[u.node]] < 
           dfs.entry_t[scc.low[dfs.parent[u.node]]])
          scc.low[dfs.parent[u.node]] = scc.low[u.node];   
      } 
    }

    int stack_top(std::stack<int>& stack) {
      int t = stack.top();
      stack.pop();
      return t;
    }

    template<typename T = Unit>
    void pop_component(SCC<T>& scc, int u) {
      int p; // vertex placeholder;
      scc.count++;
      scc.components[u] = scc.count;
      while((p = stack_top(scc.active_comp)) != u) scc.components[p] = scc.count;
    }
}