#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>




struct Player
{
     std::string n;
     int a;
     int d;
};



typedef std::vector<Player> vp;


namespace algorithms::onlinejudge::complete_search::argentina
{
    /** https://onlinejudge.org/external/118/11804.pdf, 5 nested loops  */
    const int SIZE = 10;
    void choose(int& max_attack, int& max_defense, int la, int ld, std::set<std::string>& attackers, const std::set<std::string>& local)
    {
        if(la > max_attack || 
           (la == max_attack && 
            ld > max_defense))
        {
            max_attack = la;
            max_defense = ld;
            attackers = local;
            return;
        }
        else if(la == max_attack && ld == max_defense && local < attackers)
          attackers = local;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

          
        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
             std::string n;
             int a, d;
             vp ps;
             for(int i = 0; i < 10; i++)
               std::cin >> n >> a >> d,
               ps.push_back({n, a, d});
            

             std::set<std::string> attackers;
             int max_attack = INT32_MIN;
             int max_defense = INT32_MIN;
             for(int i = 0; i < SIZE; i++)
               for(int j = i + 1; j < SIZE; j++)  
                 for(int k = j + 1; k < SIZE; k++)  
                   for(int l = k + 1; l < SIZE; l++)  
                     for(int m = l + 1; m < SIZE; m++)
                     {
                        int la = ps[i].a + ps[j].a + ps[k].a + ps[l].a + ps[m].a;
                        std::set<std::string> local = {ps[i].n, ps[j].n, ps[k].n, ps[l].n, ps[m].n};
                        int ld = 0;
                        for(auto p : ps) if(!local.count(p.n)) ld += p.d;
                        choose(max_attack, max_defense, la, ld, attackers, local);
                     }
  
             std::set<std::string> attackers_vs;
             std::set<std::string> defenders_vs;
             for(auto p : ps)
               if(attackers.count(p.n))
                 attackers_vs.insert(p.n);
               else defenders_vs.insert(p.n);

             std::string ans = "(";
             for(auto s : attackers_vs) ans += s + ", ";
             ans.erase(ans.end() - 2, ans.end());
             ans += ")\n(";
             for(auto s : defenders_vs) ans += s + ", ";
             ans.erase(ans.end() - 2, ans.end());
             ans += ")";
             printf("Case %d:\n%s\n", c++, ans.c_str());

        }
    }
}