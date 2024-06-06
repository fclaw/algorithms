#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <optional>
#include <cmath>
#include <tuple>
#include <unordered_map>

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

struct ListNode 
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
  public:
    void print()
    {
        auto ptr = this;
        do
        {
            std::cout << ptr->val << (ptr->next == nullptr ? " " : " -> ");
            ptr = ptr->next;
            
        }while(ptr != nullptr);
    }
};
 
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
void combinationSumHelper(vector<int>& xs, int& acc, vector<int>& ys)
{
    if()
}


vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
    return {};
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

// https://leetcode.com/problems/insert-interval
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) 
{
    return {};
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
}