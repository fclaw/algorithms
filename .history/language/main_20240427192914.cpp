#include <iostream>

using namespace std;

int main() 
{
  int sum = 0, val = 1;
// keepexecutingthewhileaslongasvalislessthanorequalto10 while (val <= 10) {
sum+=val; // assignssum+valtosum
++val; // add1toval }
std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;
return 0;

}