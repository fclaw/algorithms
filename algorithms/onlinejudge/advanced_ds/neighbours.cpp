#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::advanced_ds::neighbours
{
    /** https://onlinejudge.org/external/109/10928.pdf, counting out degrees  */
    void countDegrees(const vvi& adjList, vi& degrees, int& min_degree) 
    {
        int tmp = INT32_MAX;
        for(int i = 0; i < adjList.size(); i++)
        {
            if(tmp > adjList[i].size())
              tmp = adjList[i].size();
            degrees[i] = adjList[i].size();
        }
        min_degree = tmp;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int N;
            std::cin >> N;
            std::cin.ignore();
            vvi adjList(N);
            std::string line;
            for(int i = 0; i < N; i++)
            {
                int v;
                vi vertices;
                std::getline(std::cin, line);
                std::stringstream ss(line);
                while(ss >> v) vertices.push_back(--v);
                adjList[i] = vertices;
            }

            vi degrees(N, 0);
            int min_degree;
            countDegrees(adjList, degrees, min_degree);

            bool first = true;
            for (int i = 0; i < degrees.size(); i++)
              if (degrees[i] == min_degree) 
              {
                  if(!first) std::cout << " ";
                   std::cout << i + 1;
                   first = false;
              }
            std::cout << std::endl;
            std::cin.ignore();
        }
    }
}