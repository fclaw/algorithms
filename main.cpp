#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <optional>
#include <cmath>
#include <tuple>
#include <unordered_map>
#include <set>
#include <stack>
#include <climits>
#include <cstdio>


// algorithms folder
#include "algorithms/uniquePathsWithObstacles.cpp"
#include "algorithms/middleNode.cpp"
#include "algorithms/3sum.cpp"
#include "algorithms/coinChange.cpp"
#include "algorithms/graph.cpp"
#include "algorithms/minPathSum.cpp"
#include "algorithms/dp/leetcode/dungeonGame.cpp"
#include "algorithms/overlapIntervals.cpp"
#include "algorithms/nthNode.cpp"
#include "algorithms/swapPairs.cpp"
#include "algorithms/threeSumClosest.cpp"
#include "algorithms/coinChangeII.cpp"
#include "algorithms/longestPalindrome.cpp"
#include "algorithms/pascalTriangle.cpp"
#include "algorithms/maxProfit.cpp"
#include "algorithms/minCostClimbingStairs.cpp"
#include "algorithms/dp/leetcode/longestPalindromeSubstring.cpp"
#include "algorithms/subarrayOfTargetSum.cpp"
#include "algorithms/numOfSubarrays.cpp"
#include "algorithms/minTravelCost.cpp"
#include "algorithms/maxSubStringLength.cpp"
#include "algorithms/addChildSum.cpp"
#include "algorithms/dp/leetcode/maximalSquare.cpp"
#include "algorithms/waysToPoint.cpp"
#include "algorithms/convertStrings.cpp"
#include "algorithms/paintFence.cpp"
#include "algorithms/dp/minMovesOnChessboard.cpp"
#include "algorithms/dp/uniqueWaysOfCoins.cpp"
#include "algorithms/dp/leetcode/stringInterleaving.cpp"
#include "algorithms/dp/sumOfSubsetToTarget.cpp"
#include "algorithms/dp/leetcode/maxSumAfterPartitioning.cpp"
#include "algorithms/dp/knapsack.cpp"
#include "algorithms/dp/leetcode/longestCommonSubsequence.cpp"
#include "algorithms/dp/leetcode/findTargetSumWays.cpp"
#include "algorithms/dp/leetcode/maxProduct.cpp"
#include "algorithms/dp/cuttingRod.cpp"
#include "algorithms/tree/traversal.cpp"
#include "algorithms/array/leetcode/nextGreaterElements.cpp"
#include "algorithms/dp/leetcode/lengthOfLongestSubsequence.cpp"
#include "algorithms/dp/leetcode/minimumTotal.cpp"
#include "algorithms/array/leetcode/dailyTemperatures.cpp"
#include "algorithms/primesAndFactors.cpp"
#include "algorithms/dp/leetcode/longestPalindromeSubseq.cpp"
#include "algorithms/dp/leetcode/minStepsOn2KeysKeyboardRec.cpp"
#include "algorithms/dp/leetcode/burstBalloons.cpp"
#include "algorithms/tree/leetcode/distanceK.cpp"
#include "algorithms/bitsManipulation.cpp"
#include "algorithms/subsetToTarget.cpp"
#include "algorithms/ 8Queens.cpp"
#include "algorithms/dp/leetcode/canPartition.cpp"
#include "algorithms/dp/leetcode/minimizeTheDifference.cpp"
#include "algorithms/dp/leetcode/lengthOfLIS.cpp"
#include "algorithms/dp/leetcode/deleteAndEarn.cpp"
#include "algorithms/dp/coinsCanonicalWays.cpp"
#include "algorithms/dp/tsp.cpp"
#include "algorithms/dp/leetcode/maxSatisfaction.cpp"
#include "algorithms/array/leetcode/mergeSortedArray.cpp"
#include "algorithms/array/leetcode/canonicalSubsets.cpp"
#include "algorithms/array/leetcode/subsetsWithDup.cpp"
// codeforces
#include "algorithms/codeforces/erasingZeroes.cpp"
#include "algorithms/codeforces/goodPrefixes.cpp"
#include "algorithms/codeforces/hitTheLottery.cpp"
#include "algorithms/codeforces/fairDivision.cpp"
#include "algorithms/codeforces/twoArraysAndSwaps.cpp"
#include "algorithms/codeforces/redAndBlue.cpp"
// online judge
#include "algorithms/onlinejudge/dp/wedding.cpp"
#include "algorithms/onlinejudge/dp/sdi.cpp"
#include "algorithms/onlinejudge/dp/howDoYouAdd.cpp"
#include "algorithms/onlinejudge/dp/chestOfDrawers.cpp"


int main()
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- subset with dup---\n";

    std::vector<int> set = {1,9,8,3,-1,0};
    auto ans = algorithms::array::leetcode::subsetsWithDup(set);

    for ( const auto &row : ans )
    {
        for ( const auto &s : row ) 
          std::cout << std::setw(5) << s << ' ';
        std::cout << std::endl;
    }  
}