#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <unordered_set>



typedef std::vector<std::string> vs;
typedef std::vector<vs> vvs;
typedef std::unordered_map<std::string, std::unordered_set<std::string>> mss;



namespace algorithms::onlinejudge::complete_search::leaders
{

    /** https://onlinejudge.org/external/104/10475.pdf, generate and prune; try all */
    vvs ans;
    mss prohibited;
    int T, P, S;
    void backtrack(const vs& topics, int i, int s, vs xs)
    {
      if(s == S) { ans.push_back(xs); return; }
 
      for(int j = i; j < T; j++)
      {
          bool hasConflict = false;
          for (const auto& x : xs)
            if((prohibited.find(x) != 
                prohibited.end() && 
                prohibited[x].count(topics[j])) || 
               (prohibited.find(topics[j]) != 
                prohibited.end() && 
                prohibited[topics[j]].count(x)))
            { hasConflict = true; break; }

          if(hasConflict) continue;
          vs tmp = xs;
          tmp.push_back(topics[j]);
          backtrack(topics, j + 1, s + 1, tmp);
      }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            ans.clear();
            prohibited.clear();
            scanf("%d %d %d\n", &T, &P, &S);
            vs topics(T);
            for(int i = 0; i < T; i++)
            {
                 std::cin >> topics[i];
                 std::transform(topics[i].begin(), topics[i].end(), topics[i].begin(), ::toupper);
            }
            
              std::cin.ignore();
            std::sort(topics.begin(),topics.end(),[](const std::string& a,const std::string& b){
                if(a.length() == b.length()) return a < b;
                return a.length() > b.length();
             });
            for(int i = 0; i < P; i++)
            {
                std::string l;
                std::getline(std::cin, l);
                std::stringstream ss(l);
                std::string s1, s2;
                ss >> s1 >> s2;
                std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
                std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
                prohibited[s1].insert(s2);
                prohibited[s2].insert(s1);
            }

            backtrack(topics, 0, 0, {});
            printf("Set %d:\n", c++);
            for(auto ss : ans)
            {
                for(int i = 0; i < ss.size(); i++)
                { std::cout << ss[i]; if(i != ss.size() - 1) std::cout << " "; }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
}