#include <cstdio>
#include <string>
#include <unordered_map>


namespace algorithms::codeforces
{
    
    std::string solve_236_a(std::string s, std::unordered_map<char, int>& freq)
    {
        int cnt = 0;
        for(auto c : s)
        {
            if(auto i = freq.find(c); i != freq.end())
              continue;
          
            freq[c]++;
            cnt += 1;
        }
        return cnt % 2 == 0 ? "CHAT WITH HER!" : "IGNORE HIM!";
    }

    void submit_236_a()
    {
        char tmp[100];
        scanf("%s", tmp);
        std::string str(tmp);
        std::unordered_map<char, int> freq;
        printf("%s", solve_236_a(str, freq).c_str());
    }
}