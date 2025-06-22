#include <vector>


namespace algorithms::onlinejudge::graph::tools
{

    typedef std::vector<int> vi;
    // Union-Find Disjoint Sets Library written in OOP manner, using both path compression and union by rank heuristics
    // courtesy of Competitive Programming 4
    class UnionFind {                                // OOP style
      private: 
        vi p, rank, setSize;                  // vi p is the key part
        int numSets;
        int V;
      public:
        UnionFind(int N) {
          p.assign(N, 0); 
          for (int i = 0; i < N; ++i) p[i] = i;
          rank.assign(N, 0);                           // optional speedup
          setSize.assign(N, 1);                        // optional feature
          numSets = N;                                 // optional feature
          V = N;
        }
        int findSet(int i) 
        { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
        bool isSameSet(int i, int j) 
        { return findSet(i) == findSet(j); }
        void unionSet(int i, int j) {
          if(!isSameSet(i, j)) {
            int x = findSet(i);
            int y = findSet(j);                        // find both rep items
            if(rank[x] > rank[y]) 
              std::swap(x, y);                              // keep x 'shorter' than y
            p[x] = y;                                  // set x under y
            if(rank[x] == rank[y]) ++rank[y];          // optional speedup
            setSize[y] += setSize[x];                  // combine set sizes at y
            --numSets;                                 // a union reduces numSets
          }
        }
        int numDisjointSets() { return numSets; }
        int sizeOfSet(int i) { return setSize[findSet(i)]; }
        vi getMembers(int el) {
          int rep = this->findSet(el);
          tools::vi members;
          // To get all the members of the set of `e.from`, iterate over all nodes and find the ones in the same set
          for(int v = 0; v < V; ++v) {
            if(this->findSet(v) == rep)
              members.push_back(v);
          }
          return members;
        }
    };
}