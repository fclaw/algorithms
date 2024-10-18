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
typedef std::vector<std::pair<int, int>> vp;
typedef std::vector<std::vector<int>> table;
typedef std::vector<Box> vbox;

    // https://leetcode.com/problems/remove-boxes
    /** You are given several boxes with different colors represented by different positive numbers.
     *  You may experience several rounds to remove boxes until there is no box left. 
     *  Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), 
     *  remove them and get k * k points. Return the maximum points you can get. 
     *  objective function: f(i, j) = n 
     *  some shrewd observation drawn from https://medium.com/@haohsiangchung/leetcode-remove-boxes-ae7f2d1e1c90 */
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
        back_loop(i, r, pos)
          if(i < boxes.size() && 
             boxes[i] == target)
          {
             Box b = getBox(boxes, i, r);
             i = b.left;
             xs.push_back(b);
          }
        return xs;
    }

    int getMax(const vi& boxes, int l, int r, table& memo)
    {
        if(l >= r) return 0;

        int &points = memo[l][r];
        if(~points) return memo[l][r];

        points = 0;
        loop(i, l, r)
        {
            Box box = getBox(boxes, i, r);
            int cnt = box.count, streak = 0, acc = 0;
            vbox xs = getBoxes(boxes, box.right, r);
            xs.push_back(box);
            loop(j, 0, xs.size() - 1)
            {
                int curr_cnt = xs[j].count + xs.back().count;
                int curr_max = getMax(boxes, xs.back().right + 1, xs[j].left, memo);
                int rest = getMax(boxes, xs[j].right + 1, r, memo);
                int acc_rest = getMax(boxes, xs.front().right + 1, r, memo);
                cnt += xs[j].count;
                streak = std::max(streak, std::max(curr_cnt * curr_cnt + curr_max + rest, cnt * cnt + curr_max + acc + acc_rest));
                if(j + 1 < xs.size()) acc += getMax(boxes, xs[j + 1].right + 1, xs[j].left, memo);
            }
            points = std::max( points, std::max(streak, box.count * box.count + getMax(boxes, box.right + 1, r, memo)));
            i = box.right + 1;
        }
        return memo[l][r] = points;
    }
    int removeBoxes(const vi& boxes) 
    { table memo = vvi(boxes.size() + 1, vi(boxes.size() + 1, -1)); return getMax(boxes, 0, boxes.size(), memo); }
}