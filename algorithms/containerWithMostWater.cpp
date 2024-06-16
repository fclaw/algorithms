#include <vector>
#include <algorithm>

namespace leetcode::array
{
    // https://leetcode.com/problems/container-with-most-water
    int maxAreaHelper(std::vector<int>& xs, int left, int right, int volume)
    {
        if(left >= right)
        return volume;

        if(xs[left] < xs[right])
        {
        int left_tmp = left;
        while(++left_tmp < right && 
            xs[left] > xs[left_tmp]);
        int volume_left = (right - left_tmp) * std::min(xs[right], xs[left_tmp]);
        return maxAreaHelper(xs, left_tmp, right, std::max(volume, volume_left));
        }
        else if(xs[left] > xs[right])
        {
            int right_tmp = right;
            while(--right_tmp >= left &&
            xs[right] > xs[right_tmp]);
            int volume_right = (right_tmp - left) * std::min(xs[right_tmp], xs[left]);
            return maxAreaHelper(xs, left, right_tmp, std::max(volume, volume_right));

        }
        else // both left and right are equal
        {
            int left_tmp = left;
            while(++left_tmp < right && 
            xs[left] > xs[left_tmp]);

            int right_tmp = right;
            while(--right_tmp >= left &&
            xs[right] > xs[right_tmp]);
            
            int l_r_volume = (right_tmp - left_tmp) * std::min(xs[right_tmp], xs[left_tmp]);
            return maxAreaHelper(xs, left_tmp, right_tmp, std::max(volume, l_r_volume));
        }
    }

    int maxArea(std::vector<int>& height)
    {
        int init_volume = (height.size() - 1) * std::min(height[0], height[height.size() - 1]);
        return maxAreaHelper(height, 0, height.size() - 1, init_volume);
    }
}