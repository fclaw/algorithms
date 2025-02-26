#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>


typedef std::vector<std::string> vs;
typedef std::vector<char> vc;


namespace algorithms::onlinejudge::complete_search::passwords
{
    /** https://onlinejudge.org/external/6/628.pdf, 
     * backtracking, follow the rules in description
     * Complexity Analysis: 
     * - Let l = length of the pattern
     * - Let k = average length of words in the dictionary
     * - '#' can be replaced by any of W words (where W is the number of words)
     * - '0' can be replaced by any digit (0-9), giving 10 choices
     * Total recursive calls:
     * O(l * W^x * 10^y), where: 
     * - x = number of '#' in the pattern
     * - y = number of '0' in the pattern
     * Since both W^x and 10^y grow exponentially, the approach quickly becomes infeasible for many wildcards.
    */
    const char DIGIT = '0';
    const char WORD = '#';
    vc digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    void backtrack(const std::string& pattern, int i, const vs& words, std::string& pass, vs& ans)
    {
        if(i == pattern.size())
        { ans.push_back(pass); return; }

        if(pattern[i] == DIGIT)
          for(auto d : digits)
            pass.push_back(d),
            backtrack(pattern, i + 1, words, pass, ans),
            pass.pop_back();
        else if(pattern[i] == WORD)
          for(std::string w : words)
            pass += w,
            backtrack(pattern, i + 1, words, pass, ans),
            pass.erase(pass.end() - w.length(), pass.end());
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int K;
        while(std::cin >> K)
        {
            vs words(K);
            for(int i = 0; i < K; i++)
              std::cin >> words[i];
            
            int N;
            std::cin >> N;
              
            vs patterns(N);
            for(int j = 0; j < N; j++)
              std::cin >> patterns[j];  
              
            vs passwords;  
            for(auto p : patterns)
            { std::string tmp; backtrack(p, 0, words, tmp, passwords); }
    
            std::cout << "--" << std::endl;
            for(auto p : passwords)
              std::cout << p << std::endl;
        } 
    }
}