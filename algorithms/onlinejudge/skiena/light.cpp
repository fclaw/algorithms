#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

namespace algorithms::onlinejudge::skiena::light
{
    /** https://onlinejudge.org/external/101/10110.pdf
     * There is man named ”mabu” for switching on-off light in our University. He switches on-off the lights
     * in a corridor. Every bulb has its own toggle switch. That is, if it is pressed then the bulb turns on.
     * Another press will turn it off. To save power consumption (or may be he is mad or something else)
     * he does a peculiar thing. If in a corridor there is n bulbs, he walks along the corridor back and forth
     * n times and in i-th walk he toggles only the switches whose serial is divisible by i. He does not press
     * any switch when coming back to his initial position. A i-th walk is defined as going down the corridor
     * (while doing the peculiar thing) and coming back again. Now you have to determine what is the final
     * condition of the last bulb. Is it on or off? */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
    }
}