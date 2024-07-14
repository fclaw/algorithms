#include <vector>
#include <iostream>

namespace algorithms::bits
{

    /*
      The following code declares an int variable x that can contain a subset of {0,1,2,...,31}. 
      After this, the code adds the elements 1, 3, 4, and 8 to the set and prints the size of the set.
      The bit representation of the set {1,3,4,8} is 00000000000000000000000100011010
    */
    void powerOfSet(std::vector<int> set)
    {
        int x = 0;
        for(auto el : set)
          x |= (1 << el);
        std::cout << __builtin_popcount(x) << "\n";
    }
}