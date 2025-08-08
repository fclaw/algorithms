

namespace algorithms::onlinejudge::graph::tools::eulerian
{
    using vi = std::vector<int>;
    using vvi = std::vector<vi>;



    
    // This function assumes the graph has an Eulerian path/circuit
    vi hierholzer_u(
      int start,
      // Pass graph by non-const reference to modify it  
      vvi& graph) {
      
      vi current_path;
      current_path.push_back(start);
      vi circuit;

      while (!current_path.empty()) {
        int u = current_path.back();

        // If there are unvisited edges from u
        if(!graph[u].empty()) {
          // Take one edge
          int v = graph[u].back();
          graph[u].pop_back(); // "Use" the edge u->v

          // Find and remove the corresponding reverse edge v->u
          for(size_t i = 0; i < graph[v].size(); ++i) {
            if(graph[v][i] == u) {
              graph[v].erase(graph[v].begin() + i);
              break;
            }
          }

          // Move to the neighbor
          current_path.push_back(v);
        }
        // If there are no more edges from u
        else {
          // We are stuck, so add u to the final circuit
          circuit.push_back(u);
          current_path.pop_back(); // Backtrack
        }
      }
      // --- The reverse is done ONCE at the end ---
      std::reverse(circuit.begin(), circuit.end());
      return circuit;
    }


    vi hierholzer_d(int start, const vvi& graph, int N) {
      vi path, idx(N, 0), st;
      st.push_back(start);
      while(!st.empty()) {
        int u = st.back();
        if (idx[u] < (int)graph[u].size()) {           // still has neighbor
          st.push_back(graph[u][idx[u]]);
          ++idx[u];
        }
        else {
          path.push_back(u);
          st.pop_back();
        }
      }
      std::reverse(path.begin(), path.end());
      return path;
    }
}