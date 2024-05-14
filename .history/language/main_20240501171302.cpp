#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <optional>

using namespace std;


optional<int> linear_search(const std::vector<int>& arr, int target) {
    optional<int> index = std::nullopt; //  initialisation

    // invariant: the processed sub-array doesn hold the target up to index i
    // maintainence: at each iteration the invariant is maintained until the target matches an element under index i
    // termination: either the target matches an element under index i or the array is processed completely (invariant holds)
    for (int i = 0; i < arr.size(); ++i) {  // Loop through the array
        if (arr[i] == target) {  // Check if the current element matches the target
            index = i;  // If it matches, return the index
            break;
        } else {
            continue;
        }
    }

    return index;
}


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
    if(l >= r) 
    {
        return;
    } else 
    {
        size_t q = (int)floor(l + r / 2);
        merge_sort(array, l, q);
        merge_sort(array, q + 1, r);
        merge(array, )
    }
}


int main() 
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::optional<int> result = linear_search(arr, 3456);

    if (result.has_value()) {  // Check if the optional has a value
        std::cout << "Found: " << result.value() << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    std::vector<int> array_1 = {78, 34, 67, 7};

    // selection(array_1);
    merge_sort(array_1, 0, array_1.size());

    for (int i = 0; i < 4; i++) {  // Iterate through the array
        std::cout << array_1[i] << " ";  // Print each element
    }
    std::cout << std::endl;  // End the line

    return 0;
}