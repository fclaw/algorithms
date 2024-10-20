#include <vector>
#include <unordered_map>
#include <algorithm>

namespace algorithms::dp::leetcode::boxes
{

struct Box
{
    int count;
    int left;
    int right;
};


#define loop(x, s, n) for(int x = s; x < n; x++)
#define back_loop(x, s, n) for(int x = s; x > n; x--)
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::vector<int>> table;
typedef std::vector<Box> vbox;

    // https://leetcode.com/problems/remove-boxes
    /** You are given several boxes with different colors represented by different positive numbers.
     *  You may experience several rounds to remove boxes until there is no box left. 
     *  Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), 
     *  remove them and get k * k points. Return the maximum points you can get. 
     *  objective function: f(i, j) = n 
     *  some shrewd observation drawn from https://medium.com/@haohsiangchung/leetcode-remove-boxes-ae7f2d1e1c90 */
    int BOX_SIZE;
    Box getBox(const vi& boxes, int p, int r)
    {
        int l = 0;
        int cnt_l = 0, cnt_r = 0;
        int i = p - 1;
        // left
        while(i >= l && boxes[i] == boxes[p]) { ++cnt_l; --i; }
        // right
        int j = p + 1;
        while(j < r && boxes[j] == boxes[p]) { ++cnt_r; ++j; }
        return Box{ 1 + cnt_r + cnt_l, ++i, --j };
    }

    vbox getBoxes(const vi& boxes, int pos, int r)
    {
        vbox xs;
        int target = boxes[pos];
        loop(i, pos + 1, r) 
          if(boxes[i] == target)
          {
             Box b = getBox(boxes, i, r);
             i = b.right + 1;
             xs.push_back(b);
          }
        return xs;
    }

    int maxScore(const vi& boxes, int l, int r, table& memo)
    {
        if(l >= r) return 0;

        int &streak = memo[l][r];
        if(~streak) return memo[l][r];

        streak = 0;
        loop(i, l, r)
        {
            Box box = getBox(boxes, i, r);
            i = box.right + 1;
            int local = 0;
            int acc_in = 0;
            int acc_cnt = box.count;
            Box prev = box;
            vbox bs = getBoxes(boxes, box.right, r);
            for(auto b : bs)
            {
                int in = maxScore(boxes, box.right + 1, b.left, memo);
                int left = maxScore(boxes, b.right + 1, r, memo);
                int cnt = box.count + b.count;
                acc_cnt += b.count;
                acc_in += maxScore(boxes, prev.right + 1, b.left, memo);
                prev = b;
                local = std::max(local, std::max(cnt * cnt + in + left, acc_cnt * acc_cnt + acc_in + left));
            }
            streak = std::max(streak, std::max(local, box.count * box.count + maxScore(boxes, box.right + 1, r, memo)));
        }
        return memo[l][r] = streak;
    }
    int removeBoxes(const vi& boxes) 
    { BOX_SIZE = boxes.size(); table memo = vvi(BOX_SIZE + 1, vi(BOX_SIZE + 1, -1)); return maxScore(boxes, 0, BOX_SIZE, memo); }
}