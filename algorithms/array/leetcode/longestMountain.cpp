#include <vector>

namespace algorithms::array::leetcode
{
    //https://leetcode.com/problems/longest-mountain-in-array
    /**
     *  You may recall that an array arr is a mountain array if and only if:
     * 1 arr.length >= 3
     * 2 There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
     *   arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
     *   arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
     *   Given an integer array arr, return the length of the longest subArray, 
     *   which is a mountain. Return 0 if there is no mountain subArray.
     */
    int longestMountain(std::vector<int> arr)
    {
    }
}