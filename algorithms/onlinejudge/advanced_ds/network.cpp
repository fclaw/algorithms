#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include "../../advanced_ds/unionFind.cpp"


namespace ad = algorithm::advanced_ds;


namespace algorithms::onlinejudge::advanced_ds::network
{
    /** https://onlinejudge.org/external/7/793.pdf , trivial; application of disjoint sets */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
       
        int tc;
        scanf("%d\n", &tc);
        while(tc--)
        {
            int N;
            scanf("%d\n", &N);
            ad::UnionFind network(N);
            std::string line;
            int yes = 0, no = 0;
            while(std::getline(std::cin, line) && !line.empty())
            {
                std::stringstream ss(line);
                int from, to;
                char op;
                ss >> op >> from >> to;
                if(op == 'c') network.unionSet(--from, --to);
                else if(network.isSameSet(--from, --to)) yes++;
                else no++;
            }
            /** The program prints two integer numbers to the standard output 
             * on the same line, in the order: ‘successful answers, unsuccessful answers’, */
            printf("%d,%d\n", yes, no);
            if(tc) std::cout << std::endl;
        }
    }
}