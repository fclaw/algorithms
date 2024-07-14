#include <vector>
#include <stack>

namespace algorithms::array::leetcode
{
    /*
      https://leetcode.com/problems/next-greater-element-ii
      Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), 
      return the next greater number for every element in nums.
      The next greater number of a number x is the first greater number to its traversing-order next in the array, 
      which means you could search circularly to find its next greater number. 
      If it doesn't exist, return -1 for this number.
      i %= nums.length
    */
    std::vector<int> nextGreaterElements(std::vector<int> nums)
    {
        // straightforward approach runtime 88 ms, complexity O(n ^ 2)
        // let's first solve more simpler puzzle as to find the next greater element to the right
        // increasing monotonic stack
        int n = nums.size();
        std::vector res(n, -1);
        std::stack<int> s;

        for (int i = n - 1; i >= 0; i--)
        {
            // remove all elements lesser then the current one 
            // until we reach the first greater or the bottom
            while(!s.empty() && nums[i] >= s.top())
              s.pop();

            // for the current element the top is the next greater one
            if(!s.empty()) res[i] = s.top();

            s.push(nums[i]);
        }
        
        return res;
    }
}