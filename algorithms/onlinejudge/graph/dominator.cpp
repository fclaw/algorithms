#include <cstdio>
#include <vector>
#include <iostream>
#include <iomanip>
#include <bitset>

using adj_g = std::vector<std::vector<int>>;

namespace algorithms::onlinejudge::graph
{
     // https://onlinejudge.org/external/119/11902.pdf
     const size_t N = 100; 
     void dfs(adj_g& g, int v, int ex, std::vector<bool>& visited, std::bitset<N>& xs)
     {
          visited[v] = true;
          xs.set(v);
          for (int i = 0; i < (int)g[v].size(); i++)
            if(!visited[g[v][i]] && 
               g[v][i] != ex)
              dfs(g, g[v][i], ex, visited, xs);
     }

     std::vector<std::bitset<N>> allDominators(adj_g g, int v)
     {
          std::vector<bool> visited(v, false);
          std::bitset<N> xs;
          dfs(g, 0, 0, visited, xs);
          
          std::vector<std::bitset<N>> ans;
          ans.push_back(xs);
          for(int i = 1; i < v; i++)
          {
               std::bitset<N> ys;
               std::vector<bool> visited(v, false);
               dfs(g, 0, i, visited, ys);
               ans.push_back(~(xs & ys));
          }
          return ans;
     }

     void printAns(std::vector<std::vector<bool>> xs, int n) 
     {
          printf("+");
         for (int i=1; i<n; i++) printf("--");
            printf("-+\n");
         for (int i=0; i<n; i++) 
         {
            printf("|");
            for (int j=0; j<n; j++) 
            {
                if(xs[i][j]) printf("Y");
                else printf("N");
                printf("|");
             }
             printf("\n+");
            for (int j=1; j<n; j++) printf("--");
            printf("-+\n");
          }
     }

     void submit_11902()
     {
          int TC;
          scanf("%d", &TC);
          int NUM = 1;
          while(TC-- > 0)
          {
               int v;
               scanf("%d", &v);
               adj_g g;
               int l = v;
               while(v-- > 0)
               {
                  int i = 0;
                  std::vector<int> tmp;
                  while(i < l)
                  {
                     int x;
                     scanf("%d", &x);
                     if(x == 1)
                       tmp.push_back(i);
                     i++;
                  };
                  g.push_back(tmp);
               };

               auto xxs = allDominators(g, l);
               std::vector<std::vector<bool>> ans;

               std::for_each(xxs.begin(), xxs.end(),
                [&l, &ans](std::bitset<N> x)
               {
                    auto s = x.to_string();
                    std::reverse(s.begin(), s.end());
                    auto ss = s.substr(0, l);

                    std::vector<bool> tmp;
                    for(auto c : ss)
                      if(c == '1')
                        tmp.push_back(true);
                      else tmp.push_back(false); 
                    ans.push_back(tmp);  
               });
               
               printf("Case %d:\n", NUM);
               printAns(ans, l);
               NUM++;
          }
     }
}