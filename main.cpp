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

using namespace std;


// function selectionSort(arr):
//     n = length of arr  // Length of the array
    
//     for i from 0 to n - 2:  // Outer loop from the first element to the second-to-last
//         minIndex = i  // Assume the first element of the unsorted section is the minimum
        
//         // Find the smallest element in the unsorted section
//         for j from i + 1 to n - 1:
//             if arr[j] < arr[minIndex]:  // Find a smaller element
//                 minIndex = j  // Update the index of the smallest element
                
//         // Swap the smallest element with the first element of the unsorted section
//         if minIndex != i:  // Only swap if the smallest element is not already in place
//             swap(arr[i], arr[minIndex])

void selection(std::vector<int>& array) {
    size_t length = array.size();
    for (size_t i = 0; i < length - 1; i++)
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < length; j++)
        {
            if (array[j] < array[minIndex])
            {
                minIndex = j;
            }
            
        }
        if(minIndex != i)
        {
            std::swap(array[i], array[minIndex]);
        }
    }
}

void merge_sort(std::vector<int>& array, size_t l, size_t r) 
{

    auto merge = [](std::vector<int>& array, size_t l, size_t m, size_t r) 
    {
        size_t left_length = m - l + 1;
        size_t right_length = r - m;
        int left_tmp[left_length];
        int right_tmp[right_length];

        for (size_t i = 0; i < left_length; i++)
        {
            left_tmp[i] = array[l + i];
        }
        
        for (size_t j = 0; j < right_length; j++)
        {
            right_tmp[j] = array[m + 1 + j];
        }

        size_t i = 0; // left array
        size_t j = 0; // right array
        size_t k = l;

        while(i < left_length && j < right_length)
        {
            if(left_tmp[i] <= right_tmp[j])
            {
                array[k] = left_tmp[i];
                i++;

            }
            else {
                array[k] = right_tmp[j];
                j++;
            }
            k++;
        }

        while(i < left_length) 
        {
            array[k] = left_tmp[i];
            i++;
            k++;   
        }

        while(j < right_length) 
        {
            array[k] = right_tmp[j];
            j++;
            k++;   
        }
    };

    if(l >= r) 
    {
        return;
    } else 
    {
        size_t q = (int)floor((l + r) / 2); // divide step
        merge_sort(array, l, q); // sub-problem of size n/2
        merge_sort(array, q + 1, r); // sub-problem of size n/2
        merge(array, l, q, r); // combine step
    }
}


void recursive_insertion_sort(std::vector<int>& array, size_t n) 
{
    if(n == 0)
    {
        return;
    }
    else
    {
        recursive_insertion_sort(array, n - 1); // recursive call
        size_t k = n - 1;
        while(k > 0)
        {
            if(array[k - 1] > array[k])
            {
                std::swap(array[k - 1], array[k]);
                k--;
            }
            else 
            {
                break;
            }
        }
    }
}


bool palindrome_number(int n)
{
    auto reverseNumber = [](int n) 
    {
        int reversed = 0;
        while (n > 0) 
        {
          int digit = n % 10;  // Extract the last digit
          reversed = reversed * 10 + digit;  // Add the digit to the reversed number
          n /= 10;  // Remove the last digit
        }
        return reversed;
    };
    if (n < 0) {
        return false;  // Negative numbers are not palindromes due to the negative sign
    }

    int reversed = reverseNumber(n);
    return reversed == n;
}

int binary_search(std::vector<int> array, size_t l, size_t r, int v)
{
    if(l >= r)
      return -1;
    else 
    {
        size_t m = floor((l + r) / 2);
        if(array[m] == v)
          return m;
        else if(array[m] > v)
          return binary_search(array, l, m, v); // T(n/2)
        else
          return binary_search(array, m + 1, r, v); // T(n/2)
    }
}

// given a set S of n integers and another integer v
// determines whether S contains two elements that sum to exactly v
// time complexity should be logarithmic -> n * lgn
std::optional<std::tuple<size_t, size_t>> sumOfTwoNumbers(const std::vector<int>& array, int target)
{
    std::unordered_map<int, int> map;
    for (int i = 0; i < array.size(); ++i) {
        int complement = target - array[i];
        if (map.find(complement) != map.end()) {
            return std::make_tuple(map[complement], i);
        }
        map[array[i]] = i;
    }
    return std::nullopt;
}

 
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
{
    if(list1 == nullptr && list2 == nullptr)
      return nullptr;
    else 
    {
      ListNode* fst_ptr = list1;
      ListNode* snd_ptr = list2;
      ListNode* list = new ListNode();
      ListNode* tmp = list;
      
      while(fst_ptr != nullptr &&
            snd_ptr != nullptr)
      {
        if(fst_ptr->val <= snd_ptr->val)
        {
            tmp->val = fst_ptr->val;
            tmp->next = new ListNode();
            tmp = tmp->next;
            fst_ptr = fst_ptr->next;
        }
        else
        {
            tmp->val = snd_ptr->val;
            tmp->next = new ListNode();
            tmp = tmp->next;
            snd_ptr = snd_ptr->next;
        }
      }

      if(fst_ptr != nullptr)
      {
        tmp->val = fst_ptr->val;
        tmp->next = fst_ptr->next;
      }
        
      if(snd_ptr != nullptr)
      {
        tmp->val = snd_ptr->val;
        tmp->next = snd_ptr->next;
      }

      return list;
    }
}

int removeDuplicates(vector<int>& nums)
{
    auto curr = nums.begin();
    auto ptr = nums.begin();
    int cnt = 1;
    while(++curr != nums.end())
    {
        if(*curr != *ptr)
        {
            *(++ptr) = *curr;
            ++cnt;
        }
    }

    return cnt;
}


// [7,1,5,3,6,4]
// buy on the first day (7), sell on the second day(1): -6, 
// buy on the first day (7), sell on the third day(5): -2, 
// buy on the first day (7), sell on the fourth day(3): -4,
// buy on the first day (7), sell on the fifth day(6): -1,
// buy on the first day (7), sell on the sixth day(4): -3,
// max profit if buy on the first day and sell on fifth day
// straightforward solution: pick up an element from an outer loop, traverse beginning from the next element to the left and collect max
std::optional<std::tuple<int, int>> maxProfitStraightforward(vector<int>& prices) 
{
    int max_profit = 0;
    int buy_day;
    int sell_day;
    for (size_t i = 0; i < prices.size(); i++)
    {
        for (size_t j = i + 1; j < prices.size(); j++)
        {
            if(max_profit < prices[j] - prices[i])
            {
                max_profit = max(max_profit, prices[j] - prices[i]);
                buy_day = i + 1;
                sell_day = j + 1;
            }
        }
    }
    return max_profit > 0 ? std::make_optional(std::make_tuple(buy_day, sell_day)) : std::nullopt;
}


// [7,1,5,3,6,4]
// left: [7, 1, 5]
// right: [3, 6, 4]
// middle: [5, 3]
// base case 0, 1
// f = max(f(right)) f(left))
std::optional<std::tuple<int, int>> maxProfitRecursive(vector<int>& prices)
{
    return std::nullopt;
}

int removeElement(vector<int>& nums, int val)
{
    int forward_ptr = 0;
    int backward_ptr = nums.size() - 1;
    while(nums.size() > 0 && 
        forward_ptr <= backward_ptr)
    {
        if(nums[forward_ptr] == val)
        {
            while(backward_ptr >= forward_ptr && 
                nums[backward_ptr] == val)
                backward_ptr--;
            if(backward_ptr > forward_ptr)
            { std::swap(nums[forward_ptr], nums[backward_ptr]); 
              forward_ptr++; 
            }
        }
        else 
        { forward_ptr++; }
    }
    return forward_ptr == 0 ? forward_ptr : forward_ptr;
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
{
}

 struct TreeNode 
 {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
  
std::vector<int> treePath(TreeNode* root)
{
   
  auto findPathSums = [](auto&& findPathSums, TreeNode* node, int currentSum, std::vector<int>& pathSums) 
  {
    if (node == nullptr)
        return; // If the node is null, return
    currentSum += node->val; // Add the current node's value to the path sum
    // If this is a leaf node (no children), store the path sum
    if (node->left == nullptr && 
        node->right == nullptr) 
    {
        pathSums.push_back(currentSum);
    } else 
    {
        // Recursively find path sums for left and right children
        findPathSums(findPathSums, node->left, currentSum, pathSums);
        findPathSums(findPathSums, node->right, currentSum, pathSums);
    }
  };

  std::vector<int> paths = {};
  findPathSums(findPathSums, root, 0, paths);
  return paths;
}

int minDepth(TreeNode* root)
{
    auto findPaths = [](auto&& findPathSums, TreeNode* node, int currentSum, std::vector<int>& paths) 
  {
    if (node == nullptr)
        return; // If the node is null, return
    currentSum += 1; // Add the current node's value to the path sum
    // If this is a leaf node (no children), store the path sum
    if (node->left == nullptr &&
        node->right == nullptr) 
    {
        paths.push_back(currentSum);
    } else 
    {
        // Recursively find path sums for left and right children
        findPathSums(findPathSums, node->left, currentSum, paths);
        findPathSums(findPathSums, node->right, currentSum, paths);
    }
  };

  std::vector<int> paths = {};
  findPaths(findPaths, root, 0, paths);
  std::min_element(paths.begin(), paths.end());
  return 1;
}

vector<int> inorderTraversal(TreeNode* root)
{
    auto traverse = [](auto&& traverse, TreeNode* node, std::vector<int>& xs)
    {
        if (node == nullptr)
          return;
        else if(node->left == nullptr && 
                node->right == nullptr)
          xs.push_back(node->val);
        else
        {
           traverse(traverse, node->left, xs);
           xs.push_back(node->val);
           traverse(traverse, node->right, xs);
        }  
    };
    std::vector<int> xs = {};
    traverse(traverse, root, xs);
    return xs;
}

vector<int> postorderTraversal(TreeNode* root)
{
    auto traverse = [](auto&& traverse, TreeNode* node, std::vector<int>& xs)
    {
        if (node == nullptr)
          return;
        else if(node->left == nullptr && 
                node->right == nullptr)
          xs.push_back(node->val);
        else
        {
           traverse(traverse, node->left, xs);
           traverse(traverse, node->right, xs);
           xs.push_back(node->val);
        }  
    };
    std::vector<int> xs = {};
    traverse(traverse, root, xs);
    return xs;
}

vector<int> preorderTraversal(TreeNode* root)
{
    auto traverse = [](auto&& traverse, TreeNode* node, std::vector<int>& xs)
    {
        if (node == nullptr)
          return;
        else if(node->left == nullptr && 
                node->right == nullptr)
          xs.push_back(node->val);
        else
        {
           xs.push_back(node->val);
           traverse(traverse, node->left, xs);
           traverse(traverse, node->right, xs);
        }  
    };
    std::vector<int> xs = {};
    traverse(traverse, root, xs);
    return xs;
}

bool treesEquality(TreeNode* first, TreeNode* second)
{
    if(first == nullptr && 
       second == nullptr)
       return true;
    else 
    {
        return first->val == second->val && 
               treesEquality(first->left, second->left) && 
               treesEquality(first->right, second->right);
    }
}

bool isSubtree(TreeNode* root, TreeNode* sub)
{
    if(root == nullptr)
      return false;
    else if(treesEquality(root, sub))
      return true;
    else
      return isSubtree(root->left, sub) || 
             isSubtree(root->right, sub);
}

int diameterOfBinaryTree(TreeNode* root, int& diameter)
{
    if(root == nullptr)
      return 0;
    else 
    {
        auto left = diameterOfBinaryTree(root->left, diameter);
        auto right  = diameterOfBinaryTree(root->right, diameter);
        diameter = max(diameter, left + right);
        return 1 + max(left, right);
    } 
}

TreeNode* invertTree(TreeNode* root) 
{
    if(root == nullptr)
      return nullptr;
    else
    {
        auto tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
}

int treeDepth(TreeNode* root)
{
    if(root == nullptr)
      return 0;
    else
    {
        auto left = 1 + treeDepth(root->left);
        auto right = 1 + treeDepth(root->right);
        return max(left, right);
    }
}

void deepestLeavesSum(TreeNode* root, int depth, int& sum, int level)
{
    if(root == nullptr)
      return;

    if(level == depth)
      sum += root->val;

    deepestLeavesSum(root->left, depth, sum, level + 1);
    deepestLeavesSum(root->right, depth, sum, level + 1);
}

// https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/
std::tuple<int, int> averageOfSubtree(TreeNode* root, int& x)
{
    if(root == nullptr)
      return std::make_tuple(0, 0);

    auto left = averageOfSubtree(root->left, x);
    auto right = averageOfSubtree(root->right, x);
    auto val = root->val + std::get<0>(left) + std::get<0>(right);
    auto cnt = 1 + std::get<1>(left) + std::get<1>(right);
    if (floor(val / cnt) == root->val)
      x += 1;
    return std::make_tuple(val, cnt);
}

// https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/description/
void bstToGstHelper(TreeNode* root, int& curr)
{
    if(root == nullptr)
      return;
    bstToGstHelper(root->right, curr);
    auto tmp = root->val;
    root->val += curr;
    curr += tmp;
    bstToGstHelper(root->left, curr);  
}

TreeNode* bstToGst(TreeNode* root) 
{
    int node_val = 0;
    bstToGstHelper(root, node_val);
    return root;
}

// https://leetcode.com/problems/delete-leaves-with-a-given-value/

// tree: 1 -> 2. target: 2
// what is on node 2:
//  nullptr = removeLeafNodesHelper(nullptr, 2) --> left 
//  nullptr = removeLeafNodesHelper(nullptr, 2) --> right
//  thus the call on node 2 returns nullptr
//  we are certain that this call produces nullptr -> removeLeafNodesHelper(2, 2)

TreeNode* removeLeafNodesHelper(TreeNode* root, int target)
{
    if(root == nullptr)
      return nullptr;  
    auto left_node = removeLeafNodesHelper(root->left, target);
    auto right_node = removeLeafNodesHelper(root->right, target);
    if(left_node == nullptr &&
       right_node == nullptr &&
       root->val == target)
      return nullptr;
    else 
    {
        root->left = left_node;
        root->right = right_node;
        return root;
    }
}

// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
    if(root == nullptr)
      return nullptr;
    if(root->val == p->val || 
       root->val == q->val)
      return root;
    auto right = lowestCommonAncestor(root->right, p, q);
    auto left = lowestCommonAncestor(root->left, p, q);
    if(right != nullptr && 
        left != nullptr)
      return root;
    else if(right != nullptr && 
            left == nullptr)
      return right;
    else if(right == nullptr &&
             left != nullptr) 
      return left;
    else return nullptr;
}

// https://leetcode.com/problems/move-zeroes/description
void moveZeroes(vector<int>& nums) 
{
    int ptr_to_zero = 0;
    while(ptr_to_zero < nums.size() && 
          nums[ptr_to_zero] != 0)
      ptr_to_zero++;    

    int ptr_to_non_zero = ptr_to_zero;
    while(ptr_to_non_zero < nums.size() && 
          nums[ptr_to_non_zero] == 0)
      ptr_to_non_zero++;    

    while(ptr_to_non_zero < nums.size())
    {
        std::swap(nums[ptr_to_zero], nums[ptr_to_non_zero]);
        while(nums[ptr_to_zero] != 0) 
          ptr_to_zero++;
        while(nums[ptr_to_non_zero] == 0) 
          ptr_to_non_zero++;
    }
}

// https://leetcode.com/problems/majority-element/description
int majorityElement(vector<int>& nums) 
{
    return 0;        
}


// backtracking algorithm
// https://leetcode.com/problems/binary-tree-paths
vector<string> binaryTreePathsHelper(TreeNode* root)
{
    if(root == nullptr)
     return {};
    auto left_s = binaryTreePathsHelper(root->left);
    auto right_s = binaryTreePathsHelper(root->right);
    if(root->left == nullptr && root->right == nullptr)
      return {std::to_string(root->val)};
    
    std::for_each(left_s.begin(), left_s.end(), [&root](string& s) { s = std::to_string(root->val) + "->" + s; } );
    std::for_each(right_s.begin(), right_s.end(), [&root](string& s) { s = std::to_string(root->val) + "->" + s; } );
    std::vector<string> merged(left_s.size() + right_s.size());
    std::merge(left_s.begin(), left_s.end(), right_s.begin(), right_s.end(), merged.begin());
    return merged;
}

// https://leetcode.com/problems/permutations/description/
// performance is confoundedly low!!
std::vector<std::vector<int>> permuteHelper(std::vector<int> xs)
{
    if(xs.size() == 0)
       return {{}};
    std::vector<std::vector<int>> acc_x = {};
    for (size_t i = 0; i < xs.size(); i++)
    {
      auto tmp = xs;
      tmp.erase(tmp.begin() + i);
      auto yys = permuteHelper(tmp);
      std::for_each(
        yys.begin(), 
        yys.end(),
        [xs, i, &acc_x](std::vector<int>& ys)
        { ys.insert(ys.begin(), xs[i]);
          acc_x.push_back(ys);
        } );
    }
    return acc_x;
}


// https://leetcode.com/problems/combination-sum
/*
Step-by-Step Approach
Sort the Array (Optional):

1 (optional) Sorting the array can help in pruning branches early if you decide to skip further exploration when the current sum exceeds the target.

2 Define the Backtracking Function:
  Create a recursive function that takes the current combination, 
  the remaining target, the start index, and the original array as arguments.

  - Base Cases:
      If the remaining target is zero, add the current combination to the list of results.
      If the remaining target is less than zero or if the start index is out of bounds, return without adding the combination.

  - Recursive Exploration:
      Iterate over the array starting from the current index.
      Include the current element in the combination and recursively call the function with the updated combination and target.
      Exclude the current element and move to the next index.

3 Backtracking: After exploring with the current element, remove it from the combination to explore other possibilities.
*/
void combinationSumHelper(size_t idx, vector<int> xs, int& target, vector<int>& ys, vector<vector<int>>& acc)
{
    auto n = xs.size();
    if(target == 0)
      acc.push_back(ys);
    else if(target < 0)
      return;
    else if (idx == n)
      return;
    else
    { 
        // Include the current element in the combination and 
        // recursively call the function with the updated combination and target.
        ys.push_back(xs[idx]);
        target -= xs[idx];
        combinationSumHelper(idx, xs, target, ys, acc);
        // Exclude the current element and move to the next index.
        ys.pop_back();
        target += xs[idx];
        combinationSumHelper(idx + 1, xs, target, ys, acc);
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
    std::sort(candidates.begin(), candidates.end());
    vector<vector<int>> combinationXs = {};
    for (size_t i = 0; i < candidates.size(); i++)
    {
      vector<int> ys = {candidates[i]};
      int val = target - candidates[i];
      combinationSumHelper(i, candidates, val, ys, combinationXs);
    }
    return combinationXs;
}

// https://leetcode.com/problems/product-of-array-except-self
// array: [1, 2, 3, 4, 5]
// prefix product array: P = [1, 2, 6, 24, 120]
// P[0] = A[0] = 1
// P[1] = P[0] * A[1] = 1 * 2 = 2
// P[2] = P[1] * A[2] = 2 * 3 = 6
// P[3] = P[2] * A[3] = 6 * 4 = 24
// P[4] = P[3] * A[4] = 24 * 5 = 120
// suffix product array: S = [120, 120, 60, 20, 5]
// S[4] = A[4] = 5
// S[3] = S[4] * A[3] = 5 * 4 = 20
// S[2] = S[3] * A[2] = 20 * 3 = 60
// S[1] = S[2] * A[1] = 60 * 2 = 120
// S[0] = S[1] * A[0] = 120 * 1 = 120
// r(i) = P(i - 1) * S(i + 1)
// if i > size -> S(sie) == 1
// if i == 0 -> P(0) = 1
// r(0) = 1 * S(1) -> 120
// r(4) = P(3) * 1 -> 24
// r(1) = P(0) * S(2) -> 1 * 60 -> 60
// r(2) = P(1) * S(3) -> 2 * 20 -> 40
vector<int> computeSuffixProduct(const vector<int>& xs) {
    int n = xs.size();
    vector<int> s(n);
    s[n - 1] = xs[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        s[i] = s[i + 1] * xs[i];
    }
    return s;
}

vector<int> computePrefixProduct(const vector<int>& xs) {
    int n = xs.size();
    vector<int> p(n);
    p[0] = xs[0];
    for (int i = 1; i < n; ++i) {
        p[i] = p[i - 1] * xs[i];
    }
    return p;
}

vector<int> productExceptSelf(vector<int>& nums)
{
    vector<int> prefixXs = computePrefixProduct(nums); // O(n) <- extra space for prefix products
    vector<int> suffixXs = computeSuffixProduct(nums); // O(n) <- extra space for suffix products
    vector<int> res = {};
    for (size_t i = 0; i < nums.size(); i++)
    {
        auto prefix = i == 0 ? 1 : prefixXs[i - 1];
        auto suffix = i + 1 == nums.size() ? 1 : suffixXs[i + 1];
        auto tmp = prefix * suffix;
        res.push_back(tmp);
    }
    return res;
}


// https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage
int garbageCollection(vector<string>& garbage, vector<int>& travel) 
{
    return 0;
}

// https://leetcode.com/problems/find-the-score-of-all-prefixes-of-an-array
vector<long long> findPrefixScore(vector<int>& nums) 
{
    return {};
}

int maxSubArray(vector<int>& nums, int i, int& best)
{
    if(i == 0)
      return nums[0];
    auto el = nums[i];
    auto curr_sum = maxSubArray(nums, i - 1, best);
    auto sum = std::max(el, curr_sum + el);
    best = std::max(best, sum);
    return sum;
}


// matrix multiplication, straightforward solution O(n^3)
using matrix = std::vector<std::vector<int>>;
void matrixMultiply(matrix a, matrix b, matrix& c, size_t row)
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < row; j++)
        {
            for (size_t k = 0; k < row; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
        
    }   
}

void matrixMultiplyRecursive(matrix a, matrix b, matrix& c, size_t row)
{
}

// https://leetcode.com/problems/subsets/description
std::vector<std::vector<int>> generateAllSubset(std::vector<int> xs)
{
    if(xs.size() == 0)
      return {{}};
    auto xs_copy = xs;
    xs_copy.erase(xs_copy.begin());  
    auto xxs = generateAllSubset(xs_copy);
    auto xxs_copy = xxs;
    std::for_each(
      xxs.begin(), 
      xxs.end(), 
      [xs](std::vector<int>& ys) 
      { ys.insert(ys.begin(), xs[0]); } 
    );
    xxs_copy.insert(xxs_copy.end(), xxs.begin(), xxs.end());
    return xxs_copy;
}


// https://leetcode.com/problems/longest-continuous-increasing-subsequence
int findLengthOfLCIS(vector<int>& nums) 
{
    int i = 0;
    int j = 0;
    int max_seq = 0;

    while(++j < nums.size())
    {
        if(nums[j - 1] < nums[j])
          continue;
        else
        {
            max_seq = std::max(max_seq, j - i);
            i = j;
        }
    }
    return std::max(j - i, max_seq);
}


// https://leetcode.com/problems/merge-intervals
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) 
{
    std::sort(intervals.begin(), intervals.end());
    auto interim_interval = intervals[0];
    vector<vector<int>> res = {};
    for (size_t i = 1; i < intervals.size(); i++)
    {
        if (intervals[i][0] <= interim_interval[1]) {
            // Overlapping intervals, merge them
            interim_interval[1] = std::max(interim_interval[1], intervals[i][1]);
        }
        else
        {
            // Non-overlapping interval, add to merged list  
            res.push_back(interim_interval);
            interim_interval = intervals[i];
        }
    }
    res.push_back(interim_interval);
    return res;
}

// https://leetcode.com/problems/insert-interval
vector<vector<int>> insertInterval(vector<vector<int>>& xs, vector<int>& x) 
{
    // find the position where new interval start time is between two intervals
    auto iter = std::lower_bound(xs.begin(), xs.end(), x, [](vector<int> x, vector<int> y) { return x[1] < y[0]; } );
    auto idx = iter - xs.begin();
    xs.insert(xs.begin() + idx, x);
    return mergeIntervals(xs);
}

// https://leetcode.com/problems/sort-colors
void sortColors(vector<int>& nums) 
{
    vector<int> tmp = vector<int>(3);
    for(size_t i = 0; i < nums.size(); i++)
        tmp[nums[i]]++;

    size_t idx = 0;
    for (size_t i = 0; i < tmp[0]; i++)
      nums[idx++] = 0;
    for (size_t i = 0; i < tmp[1]; i++)
      nums[idx++] = 1;
    for (size_t i = 0; i < tmp[2]; i++)
      nums[idx++] = 2;
}

// https://leetcode.com/problems/interval-list-intersections
vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) 
{
    return {};
}

// https://leetcode.com/problems/container-with-most-water
//
int maxAreaHelper(vector<int>& xs, int left, int right, int volume)
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

int maxArea(vector<int>& height)
{
     int init_volume = (height.size() - 1) * std::min(height[0], height[height.size() - 1]);
     return maxAreaHelper(height, 0, height.size() - 1, init_volume);
}

// https://leetcode.com/problems/gas-station
/*
To solve this problem, you can use a greedy approach with the following steps:

Check if the total gas available is greater than or equal to the total cost. If not, return -1.
Use a greedy method to find the starting station:
  - Traverse the gas stations and keep track of the current surplus of gas.
  - If the surplus drops below zero, reset the surplus and set the next station as the new starting point.
*/
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
{
     int diff = 0;
     int tank = 0;
     int petrol_station = 0;

     for (size_t i = 0; i < gas.size(); i++)
     {
         tank += gas[i];
         if(tank - cost[i] < 0)
         {
             diff += tank - cost[i];
             tank = 0;
             petrol_station = i + 1; 
         }
         else tank -= cost[i];
     }

     return tank - (-1) * diff >= 0 ? petrol_station : -1;
}

// https://leetcode.com/problems/climbing-stairs
// You are climbing a staircase. It takes n steps to reach the top.
// Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
/*
1 step =1 way,
2 steps =2 ways,
3 steps =3 ways,
4 steps =5 ways,
5 steps =8 ways, 
6 steps =13 ways
7 steps =21 ways
8 steps =34 ways
9 steps =55 ways
10 steps =89 ways
11 steps =144 ways
12 steps =233 ways
13 steps =377 ways
*/
int climbStairsSolve(int n, vector<int>& memo)
{
    if(n == 1)
      return 1;
    if(n == 2)
      return 2;
    if(memo[n] != -1)
      return memo[n];  
    auto ways = climbStairsSolve(n - 1, memo) + climbStairsSolve(n - 2, memo);
    memo[n] = ways;
    return ways;
}

int climbStairs(int n) 
{
    auto memo = vector<int>(n + 1, -1);
    return climbStairsSolve(n, memo); 
}

// https://leetcode.com/problems/unique-paths
// base case solve(0, 0) = 0
// recursive case: 
//    solve(y, x) =
//    solve(y - 1, x) +  <--- when we approach (y, x) from above
//    solve(y, x - 1)    <-- when we approach (y, x) from left
// for we have a negative index when 0 is applied we should write base cases for: solve(0, x), solve(y, 0)
// solve(0, x) = 0
// solve(y, 0) = 0
int uniquePathsSolve(int m, int n, vector<vector<int>>& memo)
{
     if(m == 1 && n == 1)
       return 1;
     if(m == 0 && n != 0)
       return 0;
     if(m != 0 && n == 0)
       return 0;   
     if(memo[m][n] != -1)
       return memo[m][n];
     int paths = uniquePathsSolve(m - 1, n, memo) + uniquePathsSolve(m, n - 1, memo);
     memo[m][n] = paths;
     return paths;
}

int uniquePaths(int m, int n) 
{
    vector<vector<int>> memo = vector<vector<int>>(m + 1, vector<int>(n + 1, -1));
    return uniquePathsSolve(m, n, memo);
}

// https://leetcode.com/problems/predict-the-winner
/*
You are given an integer array nums. Two players are playing a game with this array: player 1 and player 2.
Player 1 and player 2 take turns, with player 1 starting first. Both players start the game with a score of 0. 
At each turn, the player takes one of the numbers from either end of the array (i.e., nums[0] or nums[nums.length - 1]) which reduces the size of the array by 1. 
The player adds the chosen number to their score. The game ends when there are no more elements in the array.
Return true if Player 1 can win the game. If the scores of both players are equal, then player 1 is still the winner, and you should also return true. 
You may assume that both players are playing optimally.
*/
bool predictTheWinner(vector<int>& nums) { return false; }

// https://leetcode.com/problems/house-robber
int robHelper(vector<int>& xs, int i, vector<int>& memo)
{
    if(i >= xs.size())
      return 0;
    if(memo[i] != -1)
      return memo[i]; 
    int maxBooty = 0;
    for (size_t j = i + 2; j < xs.size(); j++) {
      int local = robHelper(xs, j, memo);
      memo[j] = local;
      maxBooty = std::max(maxBooty, local);
    }
    return xs[i] + maxBooty;
}

int solveHouseRobber(vector<int>& nums) 
{
    vector<int> memo = vector<int>(nums.size() + 1, -1);
    int maxBooty = 0;
    for (size_t i = 0; i < nums.size(); i++)
      maxBooty = std::max(maxBooty, robHelper(nums, i, memo));
    return maxBooty;
}

// https://leetcode.com/problems/house-robber-ii
// Since House[1] and House[n] are adjacent, they cannot be robbed together. 
// Therefore, the problem becomes to rob either House[1]-House[n-1] or House[2]-House[n], 
// depending on which choice offers more money.
int solveHouseRobber2(vector<int>& nums) 
{
  if(nums.size() == 1)
    return nums[0];

  auto last_house = *(nums.end() - 1);
  nums.pop_back();
  int maxBootyNoLast = solveHouseRobber(nums);
  nums.erase(nums.begin());
  nums.push_back(last_house);
  int maxBootyNoFirst = solveHouseRobber(nums);
  return std::max(maxBootyNoLast, maxBootyNoFirst);
}

// https://leetcode.com/problems/burst-balloons
int burstBalloons(vector<int>& nums) { return 0; }

// https://leetcode.com/problems/rotate-array
void rotateArray(vector<int>& xs, int k) 
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

int longestIncreasingSubsequence(vector<int>& xs)
{
    auto length = vector<int>(xs.size(), 1);
    for (size_t i = 0; i < xs.size(); i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            if(xs[j] < xs[i])
              length[i] = std::max(length[i], length[j] + 1);
        }
    }
    return *std::max_element(length.begin(), length.end());
}


std::optional<int> binarySearchJump(vector<int> xs, int target)
{
     return std::make_optional(0);
}

// https://leetcode.com/problems/minimum-cost-for-tickets
int mincostTickets(vector<int>& days, vector<int>& costs) 
{
    return 0;
}

// maximum path in a grid
void maxPathInGridSolve(vector<vector<int>> grid, vector<vector<int>>& sum)
{    
   for (int y = 1; y < 5; y++)
     for (int x = 1; x < 5; x++)
       sum[y][x] = max(sum[y][x-1],sum[y-1][x])+ grid[y][x];
}

int maxPathInGrid(vector<vector<int>> grid) {

  vector<vector<int>> sum = { {grid[0][0], 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0} };
      // Initialize the first row
    for (int j = 1; j < 5; ++j) {
        sum[0][j] = sum[0][j - 1] + grid[0][j];
    }

    // Initialize the first column
    for (int i = 1; i < 5; ++i) {
        sum[i][0] = sum[i - 1][0] + grid[i][0];
    }
  maxPathInGridSolve(grid, sum);
  return sum[4][4];
}

// https://leetcode.com/problems/contains-duplicate
bool containsDuplicate(vector<int>& nums) 
{
    std::sort(nums.begin(), nums.end());
    auto curr_ptr = 0;
    auto next_ptr = 1;
    auto res = false;
    while(next_ptr < nums.size())
    {
        if(nums[curr_ptr] == nums[next_ptr])
        {
           res = true;
           break;
        }
        curr_ptr++;
        next_ptr++;
    }
    return res;
}

// https://leetcode.com/problems/3sum-closest
int threeSumClosest(vector<int>& nums, int target) { return 0; }

// https://leetcode.com/problems/generate-parentheses
vector<string> generateParenthesis(int n) 
{
     return {};        
}

// https://leetcode.com/problems/linked-list-cycle
/*
To check if a linked list has a cycle, you can use Floyd's Tortoise and Hare algorithm, which is a two-pointer technique. 
This approach involves using two pointers that traverse the list at different speeds. 
If there is a cycle, the faster pointer will eventually meet the slower pointer
*/
bool hasCycle(ListNode *head) 
{
     auto one_step_ptr = head;
     auto two_step_ptr = head->next;
     auto isCycle = false;
     while(two_step_ptr != nullptr)
     {
        if(one_step_ptr == two_step_ptr)
        {
            isCycle = true;
            break;
        }
        one_step_ptr = one_step_ptr->next;
        two_step_ptr = two_step_ptr->next != nullptr ? two_step_ptr->next->next : nullptr;
     }

     return isCycle;
}


// https://leetcode.com/problems/longest-consecutive-sequence
int longestConsecutive(vector<int>& nums) { return 0; }


// Given a list of weights [w1,w2,...,wn], determine all sums that can be constructed using the weights
// possible(x,k)=possible(x−wk,k−1) or possible(x,k−1)
vector<vector<bool>> makePossibility(vector<int> nums, int m)
{
      vector<vector<bool>> possibilities = vector<vector<bool>>(m + 1, vector<bool>(nums.size(), false));
      possibilities[0][0] = true;
      for (int x = 0; x <= m; m++) {
        for (int k = 1; k <= nums.size(); k++) { 
          if (x-nums[k] >= 0)
          {
              possibilities[x][k] = possibilities[x][k] | possibilities[x-nums[k]][k-1];
          }
          possibilities[x][k] = possibilities[x][k] | possibilities[x][k-1];
        }
      }
      return possibilities;
}

template<class T>
void printVector(vector<T> xs) 
{ 
    for (auto x : xs) { std::cout << x << " "; }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> array_1 = {78, 34, 67, 1111, 7, 6, -9, 11};

    // selection(array_1);
    recursive_insertion_sort(array_1, array_1.size());

    for (int i = 0; i < array_1.size(); i++) {  // Iterate through the array
        std::cout << array_1[i] << " ";  // Print each element
    }
    std::cout << std::endl;  // End the line

    std::vector<int> array_2 = {1, 2, 4, 5, 7, 9};
    std::cout << binary_search(array_2, 0, array_2.size(), 1) << std::endl;

    std::vector<int> twoSum_array = {3, 3};
    auto opt = sumOfTwoNumbers(twoSum_array, 67);
    std::cout << (opt.has_value() ? std::to_string(std::get<1>(opt.value())) : "null");

    std::cout << std::endl;

    auto list = mergeTwoLists(new ListNode(1, new ListNode(2, new ListNode(4))), new ListNode(1, new ListNode(3, new ListNode(4))));
    list->print();

    std::cout << std::endl;

    std::vector<int> duplicate_array = {0,0,1,1,1,2,2,3,3,4};    
    std::cout << removeDuplicates(duplicate_array);

    std::cout << std::endl; 
    
    std::vector<int> prices = {7,1,5,3,6,4};
    // std::vector<int> prices_no_profit = {7,6,4,3,1};

    auto profits_days = maxProfitStraightforward(prices);
    std::cout << (profits_days.has_value() ? "buy: " + std::to_string(std::get<0>(profits_days.value())) + ", sell: " + std::to_string(std::get<1>(profits_days.value())) : "no profit");

    std::cout << std::endl;

    std::vector<int> removeElement_array = {4, 5};
    std::cout << removeElement(removeElement_array, 4);


    std::cout << std::endl;

    std::vector<int> nums1 = {1,2,4,5,6,0};
    std::vector<int> nums2 = {3};
    merge(nums1, 5, nums2, 1);

    for (int i = 0; i < nums1.size(); i++) {  // Iterate through the array
        std::cout << nums1[i] << " ";  // Print each element
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- removeLeafNodes ---\n";

    auto test_tree = new TreeNode(1, new TreeNode(2), nullptr);

    auto tree = removeLeafNodesHelper(test_tree, 2);
    auto tree_xs = preorderTraversal(tree);
    for (int i = 0; i < tree_xs.size(); i++) {  // Iterate through the array
      std::cout << tree_xs[i] << " ";  // Print each element
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- matrix multiplication ---\n";

    matrix a = { {1, 1}, {2, 2} };
    matrix b = { {1, 1}, {2, 2} };
    matrix c = {{0, 0}, {0, 0}};
    matrixMultiply(a, b, c, 2);

    for ( const auto &row : c )
    {
      for ( const auto &s : row ) std::cout << s << ' ';
      std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- all subsets  ---\n";

    std::vector<int> set = {1, 2, 3};
    auto subsets = generateAllSubset(set);

    for ( const auto &row : subsets )
    {
      for ( const auto &s : row ) 
        std::cout << s << ' ';
      std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- all permutations  ---\n";
    
    std::vector<int> permutationXs = {1, 2, 3, 4, 5, 6};
    // std::vector<std::vector<int>> allPermutations = {};
    // std::vector<std::vector<int>> acc = {};
    auto acc = permuteHelper(permutationXs);

    for ( const auto &row : acc )
    {
      for ( const auto &s : row ) 
        std::cout << s << ' ';
      std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- move zeros  ---\n";

   std::vector<int> moveZeroesXs = {0, 0};
   moveZeroes(moveZeroesXs);

   for (int i = 0; i < moveZeroesXs.size(); i++) {  // Iterate through the array
        std::cout << moveZeroesXs[i] << " ";  // Print each element
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "---  longest Continuous Increasing Subsequence  ---\n";

    std::vector<int> maxSeqXs = {1,3,5,4,7};
    std::cout << findLengthOfLCIS(maxSeqXs);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "---  /////  ---\n";
  
    std::vector<int> maxSubArrayXs = {-1, 2, 4, -3, 5, 2, -5, 2};
    int best = 0;
    maxSubArray(maxSubArrayXs, maxSubArrayXs.size() - 1, best);
    std::cout << best;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "---  combinationSum  ---\n";

    // [[2,2,2,2,2],[2,2,2,4],[2,8],[2,4,4],[5,5]]
    std::vector<int> combinationSumXs = {26,21,39,38,24,16,30,7,5,4,9,29,8,35,3,17,19,11,34};
    auto combinationSumYs = combinationSum(combinationSumXs, 29);
   
    for ( const auto &row : combinationSumYs )
    {
      for ( const auto &s : row ) std::cout << s << ' ';
      std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "---  product of Array Except Self  ---\n";

    vector<int> productExceptSelfXs = {-1,1,0,-3,3};
    auto productExceptSelfRes = productExceptSelf(productExceptSelfXs);
 
    for (int i = 0; i < productExceptSelfRes.size(); i++) {  // Iterate through the array
        std::cout << productExceptSelfRes[i] << " ";  // Print each element
    }

   
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "---  three sum  ---\n";

    // [[-1,-1,2],[-1,0,1]]
    // {-4, -1, -1, 0, 1, 2}
    // vector<int> threeSumXs = {-1, 0, 1, 2, -1, -4};
    // vector<int> threeSumXs = {0, 1, 1};
    vector<int> threeSumXs = {0, 0, 0};
    // vector<int> threeSumXs = {-1, 0, 1, 0};
    // [-5,1,4]
    // [-4,0,4]
    // [-4,1,3]
    // [-2,-2,4]
    // [-2,1,1]
    // [0,0,0]
    // vector<int> threeSumXs = {-4, -2, 1, -5, -4, -4, 4, -2, 0, 4, 0, -2, 3, 1, -5, 0};
    auto threeSumRes = threeSum(threeSumXs);

    for ( const auto &row : threeSumRes )
    {
      for ( const auto &s : row ) std::cout << s << ' ';
      std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- sort colours  ---\n";

    vector<int> sortColorsXs = {2, 0, 2, 1, 1, 0, 1, 1};
    sortColors(sortColorsXs);

    for (int i = 0; i < sortColorsXs.size(); i++) {  // Iterate through the array
        std::cout << sortColorsXs[i] << " ";  // Print each element
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- merge intervals  ---\n";

    // vector<vector<int>> intervalsXs = { {1, 3}, {2, 6}, {8, 10}, {15, 18} };
    // vector<vector<int>> intervalsXs = { {1, 4}, {4, 5} };
    vector<vector<int>> intervalsXs = { {1, 4}, {1, 5} };
    auto intervalsYs = mergeIntervals(intervalsXs);
 
    for ( const auto &row : intervalsYs )
    {
      for ( const auto &s : row ) std::cout << s << ' ';
      std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- insert interval  ---\n";

    vector<vector<int>> insertIntervalsXs = { {1, 3}, {6, 9} };
    // vector<vector<int>> insertIntervalsXs = { {1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16} };
    vector<int> newInterval = {2, 5};
    auto insertIntervalsYs = insertInterval(insertIntervalsXs, newInterval);

    for ( const auto &row : insertIntervalsYs )
    {
      for ( const auto &s : row ) std::cout << s << ' ';
      std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- rotate array  ---\n";
    
    // vector<int> rotateArrayXs = {1, 2, 3, 4, 5, 6, 7};
    vector<int> rotateArrayXs = {1, 2};
    // vector<int> rotateArrayXs = {1, 2, 3};
    rotateArray(rotateArrayXs, 3);

    for (int i = 0; i < rotateArrayXs.size(); i++) {  // Iterate through the array
        std::cout << rotateArrayXs[i] << " ";  // Print each element
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- binary search (jumps approach)  ---\n";
     
    vector<int> binarySearchJumpXs = {1, 3, 3, 4, 6, 6, 7}; 
    std::cout << binarySearchJump(binarySearchJumpXs, 4).value();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Container With Most Water ---\n";

    // vector<int> maxAreaXs = {1, 8, 6, 2, 5, 4, 8, 3, 7 };
    // vector<int> maxAreaXs = {1, 2};
    // vector<int> maxAreaXs = { 1, 8, 6, 2, 5, 4, 8, 25, 7 };
    // vector<int> maxAreaXs = {2, 1};
    // vector<int> maxAreaXs = { 2, 3, 10, 5, 7, 8, 9 }; // expected: 36, got: 15
    // vector<int> maxAreaXs = { 1, 2, 3, 4, 5, 6 }; // // expected: 9, got: 8
    // vector<int> maxAreaXs =  { 6, 5, 4, 3, 2, 1 };
    // vector<int> maxAreaXs = { 1, 2, 1 };
    vector<int> maxAreaXs = 
       { 76,155,15,188,180,154,84,34,187,142,22,5,27,183,111,128,50,58,2,
         112,179,2,100,111,115,76,134,120,118,103,31,146,58,198,134,38,104,
         170,25,92,112,199,49,140,135,160,20,185,171,23,98,150,177,198,61,92,
         26,147,164,144,51,196,42,109,194,177,100,99,99,125,143,12,76,192,152,
         11,152,124,197,123,147,95,73,124,45,86,168,24,34,133,120,85,81,163,146,
         75,92,198,126,191 };
    std::cout << maxArea(maxAreaXs);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Coin Change ---\n";
     
    vector<int> coinChangeXs = { 1, 2, 5 };
    std::cout << " min: " << std::get<0>(coinChange(coinChangeXs, 11 ));
    
    std::cout << std::endl;

    std::cout << " coins used: ";
    printVector(std::get<1>(coinChange(coinChangeXs, 11 )));

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Coin All Solutions ---\n";

    vector<int> coinAllSolutionsXs = {1, 3, 4};
    vector<int> coinAllSolutionsMemo = vector<int>(INT32_MAX, -1);
    std::cout << coinAllSolutions(coinAllSolutionsXs, 6, coinAllSolutionsMemo);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Gas Station ---\n";
    
    // vector<int> gas = { 1, 2, 3, 4, 5 };
    // vector<int> cost = { 3, 4, 5, 1, 2 };
    
    vector<int> gas = { 2, 3, 4 };
    vector<int> cost = { 3, 4, 3 };

    std::cout << canCompleteCircuit(gas, cost);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Longest subsequence ---\n";

    vector<int> longestIncreasingSubsequenceXs = { 6, 2, 5, 1, 7, 4, 8, 3 };
    std::cout << longestIncreasingSubsequence(longestIncreasingSubsequenceXs);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Climb stairs ---\n";
    std::cout << climbStairs(9);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Maximum path in a grid ---\n";

    vector<vector<int>> grid = 
       { {3, 7, 9, 2, 7},
         {9, 8, 3, 5, 5},
         {1, 7, 9, 8, 5},
         {3, 8, 6, 4, 10},
         {6, 3, 9, 7, 8}
       };
    
    std::cout << maxPathInGrid(grid);

    // std::cout << std::endl;
    // std::cout << std::endl;
    // std::cout << "--- all possibilities ---\n";

    // vector<int> possibilityXs = {1, 3};
    // auto possibilityYs = makePossibility(possibilityXs, 4);

    // for ( const auto &row : possibilityYs )
    // {
    //   for ( const auto &s : row ) std::cout << s << ' ';
    //   std::cout << std::endl;
    // }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Unique Paths ---\n";
    
    std::cout << uniquePaths(134, 78);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- House Robber ---\n";
    
    vector<int> robXs = {2,7,9,3,1,7};
    std::cout << solveHouseRobber(robXs);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- House Robber 2 ---\n";

    vector<int> rob2Xs = {0};
    std::cout << solveHouseRobber2(rob2Xs);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Unique Paths II ---\n"; 
    
    vector<vector<int>> obstacleGrid = { {0, 0, 1, 0} };
    std::cout << uniquePathsWithObstacles(obstacleGrid);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- Graph ---\n";

    auto graph = new Graph(5);
    graph->addEdge(1, 2)->addEdge(2, 3)->addEdge(2, 4)->addEdge(3, 4)->addEdge(4, 1);

    graph->display();

    std::cout << "--- Weighted Graph ---\n";

    auto weighted_graph = new WeightedGraph(5);
    weighted_graph->addEdge(1, 2, 5)->addEdge(2, 3, 7)->addEdge(2, 4, 6)->addEdge(3, 4, 5)->addEdge(4, 1, 2);

    weighted_graph->display();
}