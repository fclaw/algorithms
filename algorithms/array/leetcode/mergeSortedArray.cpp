#include <vector>
#include <iostream>

namespace algorithms::array::leetcode
{
    // https://leetcode.com/problems/merge-sorted-array
    /*
       You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, 
       and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
       Merge nums1 and nums2 into a single array sorted in non-decreasing order.
       The final sorted array should not be returned by the function, 
       but instead be stored inside the array nums1. 
       To accommodate this, nums1 has a length of m + n, 
       where the first m elements denote the elements that should be merged, 
       and the last n elements are set to 0 and should be ignored. nums2 has a length of n.

       time complexity: O(n + m)
    */
    void merge2Arrays(std::vector<int>& xs, int m, std::vector<int> ys, int n)
    {
        if(m == 0)
        {
            xs.swap(ys);
            return;
        }

        if(n == 0)
          return;

        int s = xs.size();
        int i = m - 1; // the last element in xs
        int j = n - 1; // the last element in ys
        int k = s; // the last element in the combined array
        
        while(true)
        {
            if(i < 0 || j < 0)
              break;

            if(xs[i] > ys[j])
              std::swap(xs[i--], xs[--k]);
            else
              xs[--k] = ys[j--];
        }

        while(j >= 0)
          xs[--k] = ys[j--];
    }
}