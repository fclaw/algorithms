#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <optional>
#include <cmath>

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


int* recursive_insertion_sort(const int* array, size_t n) 
{
    if(n == 0)
    {
        return new int[1]{array[0]};
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

    std::vector<int> array_1 = {78, 34, 67, 1111, 7, 6, -9, 11};

    // selection(array_1);
    merge_sort(array_1, 0, array_1.size() - 1);

    for (int i = 0; i < array_1.size(); i++) {  // Iterate through the array
        std::cout << array_1[i] << " ";  // Print each element
    }
    std::cout << std::endl;  // End the line

    return 0;
}