#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>
#include <stdexcept>
#include <tuple>     // For std::tuple
#include <utility>   // For std::apply and std::forward

/**
 * Runs a given function with a specified timeout.
 *
 * @tparam Func The type of the function to execute.
 * @tparam ...Args The types of the arguments to the function.
 * @param timeout The maximum duration to wait for the function to complete.
 * @param f The function to execute.
 * @param ...args The arguments to pass to the function 'f'.
 * @return The value returned by the function 'f'.
 * @throws std::runtime_error if the function does not complete within the timeout period.
 */
template<typename Func, typename... Args>
auto run_with_timeout(std::chrono::milliseconds timeout, Func&& f, Args&&... args) 
    -> decltype(f(std::forward<Args>(args)...)) 
{
    using ReturnType = decltype(f(std::forward<Args>(args)...));

    std::promise<ReturnType> p;
    auto future_result = p.get_future();

    // --- START OF THE FIX ---

    // 1. Capture the function and its arguments into a tuple.
    auto args_tuple = std::make_tuple(std::forward<Args>(args)...);

    // 2. The worker thread now captures the function and the tuple.
    std::thread worker([&p, f = std::forward<Func>(f), captured_args = std::move(args_tuple)]() mutable {
        try {
            // 3. Use std::apply to call the function 'f' with the arguments from the tuple.
            p.set_value(std::apply(f, std::move(captured_args)));
        } catch (...) {
            p.set_exception(std::current_exception());
        }
    });
    
    // --- END OF THE FIX ---

    worker.detach();

    if (future_result.wait_for(timeout) == std::future_status::timeout) {
        throw std::runtime_error("Function timed out.");
    } else {
        return future_result.get();
    }
}