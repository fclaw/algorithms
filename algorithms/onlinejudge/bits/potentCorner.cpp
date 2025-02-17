#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>


typedef std::vector<int> vi;

namespace algorithms::onlinejudge::bits::potent_corner
{
    
    /** https://onlinejudge.org/external/102/10264.pdf, heavy bitmask manipulation 
     * Once the cube is placed correctly, each neighboring vertex is simply derived 
     * by flipping a single bit in the binary representation of a given vertex. 
     * This eliminates the need for manually tracking connections, 
     * making the problem structurally simple despite its dimensional complexity.
     * For an N-dimensional cube, each vertex:
	 • Has N neighbors (since each bit represents a coordinate along an axis).
	 • A neighbor of vertex v is found by flipping one of its N bits (i.e., v ⊕ (1 << i), for i = 0 to N-1).
     * This bitwise approach transforms what might seem like a daunting graph traversal into a straightforward logical process. 
     * With this mindset, the task becomes manageable and even elegant! 
     * */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int dim;
        while(std::cin >> dim)
        {
            int S = 1 << dim;
            vi potencies = vi(S);
            vi weights = vi(S);
            int p;
            for(int i = 0; i < S; i++)
            { std::cin >> p; weights[i] = p; }


            for(int v = 0; v < S; v++)
            {
                int potency = 0;
                for(int i = 0; i < dim; i++)
                  potency += weights[v ^ (1 << i)];
                potencies[v] = potency;
            }

            int ans = 0; 
            for(int v = 0; v < S; v++)
            {
                int tmp = 0;
                for(int i = 0; i < dim; i++)
                {
                    int sum = potencies[v] + potencies[v ^ (1 << i)];
                    tmp = std::max(tmp, sum);
                }
                ans = std::max(ans, tmp);  
            }

            std::cout << ans << std::endl;
        }
    }
}