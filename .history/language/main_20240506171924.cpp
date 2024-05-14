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
// first: [7, 1, 5] 
// second: [3, 6, 4]
// max: 7
// [7, 1, 5], [3, 6, 4], m = 5 --> 1 step
// [7, 1], [5], m = 1 --> 2 step 
// [3, 6], [4], m = 6 --> 2 step
// 
std::optional<std::tuple<int, int>> maxProfitRecursive(vector<int>& prices)
{
    auto mkProfit = [](vector<int>& prices, size_t l, size_t m, size_t h)
    {   
    }
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
}