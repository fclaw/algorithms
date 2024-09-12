#include <vector>
#include <unordered_map>

namespace algorithms::graph::atcoder::walk
{

using adjMatrix = std::vector<std::vector<int>>;
using adjList = std::vector<std::vector<int>>;
using ll = long long;
using ull = unsigned long long;
using memo = std::unordered_map<int, std::unordered_map<ull, ull>>;
using table = std::vector<std::vector<ull>>;

    /**
     * https://atcoder.jp/contests/dp/tasks/dp_r
     * There is a simple directed graph G with N vertices, numbered  1,2, .. ,N 
     * For each i and j (1 ≤ i, j ≤ N), you are given an integer a(i,j) 
     * that represents whether there is a directed edge from Vertex i to j.
     * If a(i,j) = 1, there is a directed edge from Vertex i to j; otherwise 0.
     * Find the number of different directed paths of length 
     * K in G, modulo 10(9) + 7. We will also count a path that traverses the same edge multiple times. 
     * NOTE: due to a huge constraint on K both top-down and bottom-up approaches fail. 
     * there must be a complete different tack still unbeknown to me * */
    const int modulo = 1e+09 + 7;
    int V;
    ull calculatePaths(const adjList& adj_list, int u, ull k, memo& mt)
    {
        if(k == 0)
          return 1;

        if(auto it_f = mt.find(u); 
           it_f != mt.end())
          if(auto it_s = (*it_f).second.find(k); 
             it_s != (*it_f).second.end())
            return (*it_s).second;

        ull paths = 0;  
        for(int v : adj_list[u])
          paths += calculatePaths(adj_list, v, k - 1, mt);
        return mt[u][k] = paths;
    }

    adjList convert(const adjMatrix& adj_matrix)
    {
        adjList adj_list(adj_matrix.size());
        for (int i = 0; i < adj_matrix.size(); i++) 
          for (int j = 0; j < adj_matrix[i].size(); j++)
            if (adj_matrix[i][j] != 0) adj_list[i].push_back(j);
        return adj_list;
    }
    /**
     * 
     *   for every k
     *    for every v 
     *       for u : adj_list[v]
     *          dp[k][v] += dp[k - 1][u]
     * 
     */
    int dp(const adjList& adj_list, int v, ull k)
    {
        table dp = table(k + 1, std::vector<ull>(v, 0));

        for(int i = 0; i < v; i++)
          dp[0][i] = 1;

        for(int i = 1; i <= k; i++)
          for(int j = 0; j < v; j++)
            for(int u : adj_list[j])
              dp[i][j] += dp[i - 1][u];

        ull ans = 0;
        for(int i = 0; i < v; i++)
          ans += dp[k][i];
        return ans % modulo;
    }

    ull pathsKLength(int v, const adjMatrix& adj_matrix, ull k) { return dp(convert(adj_matrix), v, k); }
}