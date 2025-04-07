#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <iomanip>



typedef std::vector<int> vi;
typedef std::vector<double> vd;

namespace algorithms::onlinejudge::complete_search::tour_de_france
{
    /**  https://onlinejudge.org/external/112/11242.pdf, 
     *   all pairs of front and rear sprockets then sorting  */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int N, M;
        while(std::cin >> N >> M && N)
        {
            vi front_sprockets(N), rear_sprockets(M);
            for(int i = 0; i < N; i++)
              std::cin >> front_sprockets[i];
            for(int i = 0; i < M; i++)
              std::cin >> rear_sprockets[i];
           
            //The drive ratio – the ratio of the angular velocity of the pedals to that
            // of the wheels – is the quotient n/m where n is the number of teeth on the
            // rear sprocket and m is the number of teeth on the front sprocket
            vd ratio;
            for(int front : front_sprockets)
              for(int rear : rear_sprockets)
                ratio.push_back((double)rear / front);
            
            std::sort(ratio.begin(), ratio.end());
            
            double spread = std::numeric_limits<double>::min();
            for(int i = 1; i < ratio.size(); i++)
              spread = std::max(spread, std::round(ratio[i] / ratio[i - 1] * 100.0) / 100.0);

            std::cout << std::fixed << std::setprecision(2) << spread << std::endl;
        }
    }
}