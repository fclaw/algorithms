#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <string>
#include <vector>


typedef std::unordered_map<std::string, int> msi; 
typedef std::vector<std::string> vs;
const size_t K = 5;

namespace algorithms::onlinejudge::bst::conformity
{
    /** https://onlinejudge.org/external/112/11286.pdf, 
     * use map to keep track of the frequencies  */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
          int N;
          while(std::cin >> N && N)
          {
              msi popularity;
              for(int i = 0; i < N; i++)
              {
                  vs courses(K);
                  for(int j = 0; j < K; j++)
                    std::cin >> courses[j];
                  std::sort(courses.begin(), courses.end());
                  std::string key;
                  for(auto s : courses) key += s + "#";
                  ++popularity[key];
              }

              int most_popular = 0, total = 0;
              for(auto it : popularity)
                if(it.second > most_popular)
                { most_popular = it.second; }
              
              for (auto it : popularity)
                 if (it.second == most_popular) 
                   total += it.second;  
              
              std::cout << total << std::endl;
          }
    }
}