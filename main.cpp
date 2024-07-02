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
#include "algorithms/burstBalloons.cpp"
#include "algorithms/jumpGame.cpp"
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
// codeforces
#include "algorithms/codeforces/erasingZeroes.cpp"
#include "algorithms/codeforces/goodPrefixes.cpp"


int main()
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Paint fence ---\n";

    std::cout << algorithms::dp::countWaysToPaintFence(2, 4);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- longest palindrome subsequence ---\n";
    std::string case1 = 
       "ibvjkmpyzsifuxcabqqpahjdeuzaybqsrsmbfplxycsafogotliyvhxjtkrbzqxlyfwujzhkdafheb"
        "vsdhkkdbhlhmaoxmbkqiwiusngkbdhlvxdyvnjrzvxmukvdfobzlmvnbnilnsyrgoygfdzjlymhprc"
        "pxsnxpcafctikxxybcusgjwmfklkffehbvlhvxfiddznwumxosomfbgxoruoqrhezgsgidgcfzbtdft"
        "jxeahriirqgxbhicoxavquhbkaomrroghdnfkknyigsluqebaqrtcwgmlnvmxoagisdmsokeznjsnwp"
        "xygjjptvyjjkbmkxvlivinmpnpxgmmorkasebngirckqcawgevljplkkgextudqaodwqmfljljhrujo"
        "erycoojwwgtklypicgkyaboqjfivbeqdlonxeidgxsyzugkntoevwfuxovazcyayvwbcqswzhytlmtm"
        "rtwpikgacnpkbwgfmpavzyjoxughwhvlsxsgttbcyrlkaarngeoaldsdtjncivhcfsaohmdhgbwkuem"
        "cembmlwbwquxfaiukoqvzmgoeppieztdacvwngbkcxknbytvztodbfnjhbtwpjlzuajnlzfmmujhcggp"
        "dcwdquutdiubgcvnxvgspmfumeqrofewynizvynavjzkbpkuxxvkjujectdyfwygnfsukvzf";
    std::string case2 = 
       "xm9btf9vhsagz2okvlab1yhz8apkxuor5v42yewdpjo5ie0wjtvuvrjdnx05kajr7z4hw54airzej1pcfq"
       "sf4r7gboae3u09t9u0hcl8np5c3oof3tan6trns9vcxp2rwo3pde0wkiwhz24oe2a3w5wtcl8bed3fms32h"
       "11pqot4hw25lc5p9dtjwwbe2i9x6hyacrxzvs827kjh5iuep32fj9kvsr9ro5emfi274gwf70vtaaqzu03x"
       "hfralqphamgnqpwzuakg9o9ha9p0xm49wpit4ty8p4mfahnmgsojn5ir9dak1xce191cax393nsiujnct8u"
       "9wtibsdbqb5i7gion4b2pw5v4hzmszyo5xxm2ekasqtsusdunccrtcx92m3igdie7mbatanoazmrl6dogqf"
       "ioghmza3vg0i76td8rvc2lcb6oi5kpyd4izyxamc4q218f7vv6khkcdtshie9nb3is32r8zopht43b7dajk"
       "p5bapy0ye9acjgjmegc4xfu1662lhm69zia521ujaiy605w7l5qm57out6qhumd89ck7k2knogpg1zhvbnn"
       "omna1ype7buyjyr1dgqqidbo0wtxkxkfkcotenpx45ttu9zne7qtk7zx26wv5p27xfu3ebwt5c3s9kgosbx"
       "dbft6477nfhzwp4y6n4220lt56b7fpeb4a2j1anuxktanofiemd8n7st2bon6h97v6lj6ewa7v8w12mgsbn"
       "68o7df33g89wd45oz4xkd3fxe2up3cs4bneo3snf91fbcpjoyq0ssz8w7973ro44524qtjtujlfdgek7wq6"
       "b2w2b3fd6s0x2mrpmvsyr5z0c7stges7wl0cigqbqjki106tp1z6yu0mzjt1zpolkw4yw584au9jlg2dn5k"
       "5dgka2kgcaqz1fyatzjw0i743gf0tyvp22dvfdwius4uq3vli8ie1cotl3ezams5bd8ygxd55vyp5hc89hwupltd";
    std::string case3 = "xabay";
    std::string case4 = 
       "jrjnbctoqgzimtoklkxcknwmhiztomaofwwzjnhrijwkgmwwuazcowsk"
       "jhitejnvtblqyepxispasrgvgzqlvrmvhxusiqqzzibcyhpnruhrgbzs"
       "mlsuacwptmzxuewnjzmwxbdzqyvsjzxiecsnkdibudtvthzlizralpao"
       "wsbakzconeuwwpsqynaxqmgngzpovauxsqgypinywwtmekzhhlzaeatb"
       "zryreuttgwfqmmpeywtvpssznkwhzuqewuqtfuflttjcxrhwexvtxjih"
       "unpywerkktbvlsyomkxuwrqqmbmzjbfytdddnkasmdyukawrzrnhdmae"
       "fzltddipcrhuchvdcoegamlfifzistnplqabtazunlelslicrkuuhoso"
       "yduhootlwsbtxautewkvnvlbtixkmxhngidxecehslqjpcdrtlqswmyg"
       "hmwlttjecvbueswsixoxmymcepbmuwtzanmvujmalyghzkvtoxynyusb"
       "pzpolaplsgrunpfgdbbtvtkahqmmlbxzcfznvhxsiytlsxmmtqiudyjl"
       "nbkzvtbqdsknsrknsykqzucevgmmcoanilsyyklpbxqosoquolvytefh"
       "vozwtwcrmbnyijbammlzrgalrymyfpysbqpjwzirsfknnyseiujadovn"
       "gogvptphuyzkrwgjqwdhtvgxnmxuheofplizpxijfytfabx";
    std::cout << algorithms::leetcode::dp::longestSubstringPalindrome(case2) << std::endl;
}