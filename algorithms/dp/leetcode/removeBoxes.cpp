#include <vector>
#include <unordered_map>
#include <algorithm>

namespace algorithms::dp::leetcode::boxes
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> table;

    // https://leetcode.com/problems/remove-boxes
    /** You are given several boxes with different colors represented by different positive numbers.
     *  You may experience several rounds to remove boxes until there is no box left. 
     *  Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), 
     *  remove them and get k * k points. Return the maximum points you can get. 
     *  objective function: f(i, j) = n 
     *  some shrewd observation drawn from https://medium.com/@haohsiangchung/leetcode-remove-boxes-ae7f2d1e1c90 */
    int maxScore(const vi& boxes, int l, int r, int k, table& memo)
    {
        if(l >= r) return 0;

        int &score = memo[l][r][k];
        if(~score) return memo[l][r][k];

        score = INT32_MIN;
        int colour = boxes[l], cnt = 1;
        while(++l < r && boxes[l] == colour) { ++cnt; }
        --l;
        score = (cnt + k) * (cnt + k) + maxScore(boxes, l + 1, r, 0, memo);
        loop(j, l + 1, r)
          if(boxes[j] == colour)
            score = std::max(score, maxScore(boxes, l + 1, j, 0, memo) + maxScore(boxes, j, r, k + cnt, memo));  
        return score;
    }
    int removeBoxes(const vi& boxes) 
    { table memo = table(boxes.size() + 1, vvi(boxes.size() + 1, vi(boxes.size() + 1, -1))); return maxScore(boxes, 0, boxes.size(), 0, memo); }
}