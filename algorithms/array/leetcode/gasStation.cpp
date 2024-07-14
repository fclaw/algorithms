#include <vector>
#include <algorithm>

namespace algorithms::array::leetcode
{
    // https://leetcode.com/problems/gas-station
    /*
    To solve this problem, you can use a greedy approach with the following steps:

    Check if the total gas available is greater than or equal to the total cost. If not, return -1.
    Use a greedy method to find the starting station:
    - Traverse the gas stations and keep track of the current surplus of gas.
    - If the surplus drops below zero, reset the surplus and set the next station as the new starting point.
    */
    int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) 
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
}