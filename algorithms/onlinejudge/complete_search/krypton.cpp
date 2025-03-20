#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>




namespace algorithms::onlinejudge::complete_search::krypton
{
    /** https://onlinejudge.org/external/1/129.pdf, 
     * backtracking, string processing check, 
     * a bit of output formatting */
    int N, K, S = 4;
    bool isValid(const std::string& s)
    {
        for(int i = 1; i <= s.size() / 2; i++)
        {
            std::string left = s.substr(s.size() - i * 2, i);
            std::string right = s.substr(s.size() - i);
            if(left == right)
              return false;
        }
        return true;
    }
    char toChar(int i ) { return static_cast<char>('A' + i); }
    std::string ans;
    void backtrack(int& k, std::string& s)
    {
        if(k == K) { ans = s; return; }
        for(int i = 0; i < N; i++)
          if(k + 1 <= K && 
             isValid(s + toChar(i)))
          {
              s.push_back(toChar(i));
              k += 1;
              backtrack(k, s);
              s.pop_back();
          }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        while(std::cin >> K >> N && N && K)
        {
            ans = {};
            std::string s;
            int cnt = 0;
            backtrack(cnt, s);
            int c = 0;
            for(int i = 0; i < ans.length(); i++)
            {
                std::cout << ans[i];
                if(i == ans.length() - 1 || i % 64 == 63) 
                  std::cout << std::endl;
                else if(i % 4 == 3) std::cout << " ";
            }
            std::cout << ans.size() << std::endl;
        }
    }
}