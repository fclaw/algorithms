#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>

#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr);

typedef std::vector<double> vd;

namespace algorithms::onlinejudge::arrays::newspaper
{
    // https://onlinejudge.org/external/113/11340.pdf
    const size_t N = 260;
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            vd characters = vd(N, 0);
            int m;
            std::cin >> m;
            while(m--)
            {
                char c;
                double p;
                std::cin >> c >> p;
                characters[(unsigned char)c] = p;
            }
            int l;
            double total = 0;
            std::cin >> l;
            // Fixes the input buffer issue
            std::cin.ignore();
            while(l--)
            {
                std::string line;
                if(!std::getline(std::cin, line) || line.empty()) continue;
                for(char c : line)
                  total += characters[(unsigned char)c];
            }
            std::cout << std::fixed << std::setprecision(2) << total / 100.0 << "$\n";
        }
    }
}