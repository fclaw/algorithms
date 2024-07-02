// Kadane's Algorithm
/* Kadane's Algorithm is an efficient way to find the maximum sum of a contiguous subArray 
  within a one-dimensional array of numbers. It operates in O(n) time complexity, 
  making it very suitable for large datasets.

  This way, at every index i, the problem boils down to finding the maximum of just two numbers, 
  A[i] and (A[i] + local_maximum[i-1]). Thus the maximum subArray problem can be solved 
  by solving these sub-problems of finding local_maximums recursively. 
  Also, note that local_maximum[0] would be A[0] itself.

*/
#include <vector>

namespace algorithms::dp
{
    int maxSumOfSubArray(std::vector<int> xs)
    {
        // localMax(i) = max(A[i], A[i] + localMax(i - 1))
        int n = xs.size();
        int localMax = xs[0];
        int res = INT32_MIN;
        for (auto x : xs)
        {
            localMax = std::max(x, x + localMax);
            if(localMax > res)
              res = localMax;
        }

        return res;
    }
}