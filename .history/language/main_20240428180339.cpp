#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int main() 
{
   
  short array[5] = {1, 2, 4, 5, 8};

    copy(array, array + sizeof(array) / sizeof(array[0]),
       ostream_iterator<short>(cout, "\n"));

  return 0;

}