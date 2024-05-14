#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <optional>

using namespace std;


optional<int> linear_search(const std::vector<int>& arr, int target) {
    optional<int> index = std::nullopt; //  initialisation
    for (int i = 0; i < arr.size(); ++i) {  // Loop through the array
        if (arr[i] == target) {  // Check if the current element matches the target
            index = i;  // If it matches, return the index
            break;
        } else {
            continue;
        }
    }
    return  ;  
}

int main() 
{
   
  short array[5] = {1, 2, 4, 5, 8};

    copy(
      array, 
      array + sizeof(array) / sizeof(array[0]),
      ostream_iterator<short>(cout, "\n")
    );

  return 0;

}