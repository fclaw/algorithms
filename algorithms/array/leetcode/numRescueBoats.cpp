#include <vector>

namespace algorithms::array::leetcode
{
    // https://leetcode.com/problems/boats-to-save-people
    /**
     * You are given an array people where people[i] is the weight of the ith person, 
     * and an infinite number of boats where each boat can carry a maximum weight of limit. 
     * Each boat carries at most two people at the same time, 
     * provided the sum of the weight of those people is at most limit.
     * Return the minimum number of boats to carry every given person.
     */
    int numRescueBoats(std::vector<int> people, int capacity) 
    {
        int size = people.size();
        std::sort(people.begin(), people.end(), std::greater<>());
 
        int first = 0;
        int last = --size;
        int boats = 0;
        int load = 0;
        
        return boats; 
    }
}