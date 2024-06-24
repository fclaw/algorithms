#include <vector>

namespace leetcode::array::sliding_window
{
    // https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold
    /*
      Given an array of integers arr and two integers k and threshold, 
      return the number of sub-arrays of size k and average greater than or equal to threshold
    */
    int numOfSubarrays(std::vector<int> arr, int k, int threshold)
    {
        int n = arr.size();
        int l = 0;
        int r = k - 1;
        int sum = 0;
        for (size_t i = l; i <= r; i++)
         sum += arr[i];
        int res = 0;
         
        while(r < n)
        {
            if(sum / k >= threshold)
              res++;
            sum -= arr[l++];
            sum += arr[++r];
        }
        return res;
    }
}
