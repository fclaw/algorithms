#include <chrono>
#include <thread>

namespace runtime
{

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

    template<typename Ans, typename... Args>
    std::pair<Ans, int> measure(Args... args, Ans (*fun)(Args... args))
    {
        auto start = high_resolution_clock::now();
        auto res = fun(args...);
        auto end = high_resolution_clock::now();
        auto ms_int = duration_cast<milliseconds>(end - start);
        return std::make_pair(res, ms_int.count());
    }
}