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
typedef std::vector<vbox> vvbox;
typedef std::unordered_map<int, std::unordered_map<int, vvbox>> mvvbox;

    // https://leetcode.com/problems/remove-boxes
    /** You are given several boxes with different colors represented by different positive numbers.
     *  You may experience several rounds to remove boxes until there is no box left. 
     *  Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), 
     *  remove them and get k * k points. Return the maximum points you can get. 
     *  objective function: f(i, j) = n 
     *  some shrewd observation drawn from https://medium.com/@haohsiangchung/leetcode-remove-boxes-ae7f2d1e1c90 */
    int BOX_SIZE;
    mvvbox ways;     

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
        Box box = getBox(boxes, pos, r);
        vbox xs;
        int target = boxes[pos];
        back_loop(i, r, pos)
          if(i < BOX_SIZE && 
             boxes[i] == target)
          {
             Box b = getBox(boxes, i, r);
             i = b.left;
             xs.push_back(b);
          }
        return xs;
    }

    vvbox getCombinations(const vi& boxes, int pos, int r)
    {
        if(auto it_pos = ways.find(pos);
           it_pos != ways.end())
          if(auto it_r = (*it_pos).second.find(r);
             it_r != (*it_pos).second.end())
            return ways[pos][r];

        Box box = getBox(boxes, pos, r);
        vvbox acc;
        for(auto b : getBoxes(boxes, box.right, r))
        {
           vvbox xxs = getCombinations(boxes, b.left, r);
           for(auto& xs : xxs) { xs.push_back(box); acc.push_back(xs); }
        }
        if(acc.size() == 0) acc.push_back({box});
        return ways[pos][r] = acc;
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
            int streak = 0;
            vvbox xxs = getCombinations(boxes, i, r);
            for(auto xs : xxs) 
            {
                int cnt = xs[0].count, s = 0;
                int rest = getMax(boxes, xs[0].right + 1, r, memo);
                loop(j, 1, xs.size())
                  cnt += xs[j].count,
                  s += getMax(boxes, xs[j].right + 1, xs[j - 1].left, memo);
                streak = std::max(streak, cnt * cnt + s + rest);  
            }
            points = std::max( points, std::max(streak, box.count * box.count + getMax(boxes, box.right + 1, r, memo)));
        }
        return memo[l][r] = points;
    }
    int removeBoxes(const vi& boxes) 
    { 
        BOX_SIZE = boxes.size(); 
        table memo = vvi(BOX_SIZE + 1, vi(BOX_SIZE + 1, -1));
        return getMax(boxes, 0, BOX_SIZE, memo); 
    }
}