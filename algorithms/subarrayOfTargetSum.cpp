#include <vector>
#include <optional>

namespace algorithms::array
{
     /*
        The problem can be solved in O(n) time by using the two pointers method. 
        The idea is to maintain pointers that point to the first and last value of a subArray. 
        On each turn, the left pointer moves one step to the right, 
        and the right pointer moves to the right as long as the resulting subArray sum is at most x. 
        If the sum becomes exactly x, a solution has been found.
     */
     std::optional<std::tuple<int, int>> 
       getSubArrayOfTargetSum(std::vector<int> nums, int target)
     {
          int n = nums.size();
          int left = 0;
          int right = 1;
          int sum = nums[left] + nums[right];
          std::optional<std::tuple<int, int>> res = std::nullopt;
          while(right < n)
          {
              if(sum == target)
              {
                  res = std::make_optional<std::tuple<int, int>>(left, right);
                  break;
              }

              if(sum > target)
              {
                  sum -= (nums[left] + nums[right]);
                  right--;
                  left++;
              }
              else 
              {
                right++;
                 sum += nums[right];
              }
          }
          return res;
     }      
}