#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>
#include <unordered_set>
#include <map>


namespace algorithms::onlinejudge::skiena::crypt_kicker
{

typedef std::multimap<int, std::string> mis;
typedef std::unordered_set<std::string> ss;

    /** https://onlinejudge.org/external/8/843.pdf */
    int getIndex(char letter) { return letter - 97; };
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int words;
        std::cin >> words;
        std::string w;
        mis dictionary;
        for(int i = 0; i < words; i++)
          std::cin >> w,
          dictionary.insert({w.length(), w});
        
        std::string message;
        while(std::getline(std::cin, message))
        {
        }
    }
}