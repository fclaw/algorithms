#include

// https://leetcode.com/problems/3sum
/*
To solve the problem of finding all unique triplets in an array that sum to zero, we can use a combination of sorting and the two-pointer technique. 
The basic idea is to first sort the array, and then use three nested loops 
where the innermost loop is optimized using two pointers to avoid unnecessary comparisons. 
This approach ensures that we can find the solution in 𝑂(𝑛2) time complexity.

there are steps:

1 Sort the array: Sorting helps to easily avoid duplicates and also allows us to use the two-pointer technique efficiently.

2 Iterate through the array: For each element in the array, treat it as a fixed element and try to find a pair of elements 
in the remaining part of the array which sums up to the negative of the fixed element.

3 Two-pointer technique: For the remaining elements after the fixed element, use two pointers to find pairs that sum up to the required value. 
Adjust the pointers based on whether the current sum is less than or greater than the required sum.
Avoid duplicates: After finding a valid triplet, move the pointers to skip over any duplicate elements to ensure that each triplet is unique.
*/
std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
{
    auto n = nums.size();
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res = {};
    for (size_t i = 0; nums[i] <= 0; i++)
    {
        if(i > 0 && nums[i] == nums[i - 1])
          continue;
        size_t left = i + 1;
        size_t right = n - 1;
        int target = -nums[i];

        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                res.push_back({nums[i], nums[left], nums[right]});
                // Move left and right pointers and skip duplicates
                while (left < right && 
                       nums[left] == nums[left + 1]) 
                  ++left;
                while (left < right && 
                       nums[right] == nums[right - 1]) 
                  --right;
                ++left;
                --right;
            } else if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }
    }
    return res;
}