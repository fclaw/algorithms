#include <vector>
#include <bitset>
#include <unordered_map>

namespace algorithms::dp::leetcode
{
    // https://leetcode.com/problems/matchsticks-to-square
    /**
       You are given an integer array matchsticks where matchsticks[i] 
       is the length of the ith matchstick. 
       You want to use all the matchsticks to make one square. 
       You should not break any stick, but you can link them up, 
       and each matchstick must be used exactly one time.
       Return true if you can make this square and false otherwise.

       general hint: 
       The solution to this problem relies on a depth-first search (DFS) algorithm, 
       which attempts to build the square by adding matchsticks one by one 
       to each of the four sides until all matchsticks have been placed

       on length:
       The Total Length of Matchsticks: Before attempting to place matchsticks, 
       we calculate the total length of all matchsticks by summing them. For a square to be possible, 
       this total must be divisible by 4 equally (since a square has four equal sides). 
       If it is not divisible, we know right away that we can't make a square, so we return false.

       on sorting
       Avoiding Useless Work: Two optimizations help us reduce the computation time. 
       First, we sort the matchsticks in descending order, beginning with the longest. 
       This helps because if the longest matchstick is longer than the side of the square, 
       we know it's impossible to form a square and can return false immediately. 
       Second, when trying to place a matchstick on a side that is equal in length to a side we just attempted, 
       we skip that attempt since the order of matchsticks on the sides doesn't matter
    */
    const int SIDES = 4;
    const int MAX_LENGTH = 15;
    int SIZE;
    int SIDE_SIZE;
    //  dfs approach:
    //  Recursive DFS: Using a recursive function dfs(u), we try to place the u(th) matchstick on each side. 
    //  We only proceed with the recursion if adding the matchstick to the current side 
    //  does not exceed the expected length of a side (which is the total length 
    //  of the matchsticks divided by 4). If, at any point, a side becomes too long, 
    //  we backtrack by removing the matchstick from that side 
    //  (edges[i] -= matchsticks[u]) and trying other options. 
    //  If we can place the last matchstick without exceeding the side length, 
    //  we know a square is possible and return true.
    bool dfs(const std::vector<int>& xs, std::bitset<MAX_LENGTH> mask, int side, int c, std::unordered_map<int, bool>& memo)
    {  

        if(c == 4)
          return true;

        if(side > SIDE_SIZE)
           return false;
         
        if(auto i = memo.find((int)mask.to_ulong()); i != memo.end())
          return (*i).second; 

         bool ans = false;
         for(int i = 0; i < SIZE && !mask.all() && !ans; i++)
         {
             if(mask.test(i)) continue;
             mask.set(i);
             if(side + xs[i] == SIDE_SIZE)
                ans |= memo[(int)mask.to_ulong()] = dfs(xs, mask, 0, c + 1, memo);
             ans |= memo[(int)mask.to_ulong()] = dfs(xs, mask, side + xs[i], c, memo);
             mask.set(i, false);
         }
         return ans;
    }

    bool makeSquare(std::vector<int> matchsticks)
    {
        SIZE = matchsticks.size();
        int perimeter = std::reduce(matchsticks.begin(), matchsticks.end());
        if(SIZE < 4 || (perimeter % SIDES))
          return false;
        SIDE_SIZE = perimeter / SIDES;
        std::sort(matchsticks.begin(), matchsticks.end(), std::greater<int>());
        std::bitset<MAX_LENGTH> mask;
        std::unordered_map<int, bool> memo;
        return dfs(matchsticks, mask, 0, 0, memo);
    }
}
