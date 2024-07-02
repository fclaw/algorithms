#include <vector>

namespace algorithms::leetcode::array
{
    // https://leetcode.com/problems/rotate-array
    void rotateArray(std::vector<int>& xs, int k) 
    {
        auto r = k > xs.size() ? k % xs.size() : k;

        std::reverse(xs.begin(), xs.end());
        // left part 
        int left = 0;
        int right = r - 1;
        while(left < right)
        {
            std::swap(xs[left], xs[right]);
            left++;
            right--;
        }
        // right part
        left = r;
        right = xs.size() - 1;
        while(left < right)
        {
            std::swap(xs[left], xs[right]);
            left++;
            right--;
        }
    }
}