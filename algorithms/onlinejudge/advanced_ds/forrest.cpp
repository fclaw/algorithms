#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <bitset>
#include <string>
#include <sstream>
#include <vector>



typedef std::vector<int> vi;


namespace algorithms::onlinejudge::advanced_ds::forrest
{
    /** https://onlinejudge.org/external/5/599.pdf
     * v−e = number of connected components, 
     * keep a bitset of size 26 to count the number of vertices that
     * have some edge. Note: Also solvable with Union-Find */
    const size_t N = 26;
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        std::cin.ignore();  // Ignore the newline after reading T
        while(tc--)
        { 
            int edges = 0;
            std::bitset<N> connection;
            std::string line;
            // Read edges until a line with only nodes appears
            while (std::getline(std::cin, line) && line[0] == '(')
            {
                edges++;
                int from = line[1] - 'A'; 
                int to = line[3] - 'A';
                if(!connection.test(from)) connection.set(from);
                if(!connection.test(to)) connection.set(to);
            }

            std::getline(std::cin, line);
            std::stringstream ss(line);
            char node;
            vi vertices;
            while (ss >> node) 
              if (node != ',') 
              { vertices.push_back(node - 'A'); }

            int acorns = 0;
            for(auto v : vertices)
              if(!connection.test(v)) acorns++;

            /** For each test case your program should print 
             * the number of trees and the number of acorns, in a sentence, for example:
             * There are x tree(s) and y acorn(s).
             * where x and y are the numbers of trees and acorns, respectively.
             * Notes: A forest may have no trees and all acorns, all trees and no acorns, 
             * or anything in between, so keep your eyes open and don’t miss the forest for the trees */
            int trees = (vertices.size() - edges) - acorns;
            printf("There are %d tree(s) and %d acorn(s).\n", trees, acorns);
        }  
    }
}