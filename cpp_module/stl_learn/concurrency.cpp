//
// Created by Phoenix on 8/5/24.
//
#include <gtest/gtest.h>

#include <thread>
#include <future>
#include <mutex>

using namespace std::chrono_literals;

/**
 * Threads
 */

/**
 * Cache size access
 */

/**
 * Atomic operations
 */

/**
 * Mutual exclusion
 */

/**
 * Condition variables
 */

/**
 * Semaphores
 */

/**
 * Latches and Barriers
 */

/**
* Futures
*/
std::mutex m;
TEST(Concurrency, TestFuturesAsync) {
    std::cout << "main thread: " << std::this_thread::get_id() << "\n";
    auto f = std::async(std::launch::async, []() {
      std::this_thread::sleep_for(100ms);
      std::cout << "async thread: " << std::this_thread::get_id() << ", async run\n";
    });

    std::future_status status;
    while (f.valid() && status != std::future_status::ready) {
        status = f.wait_for(10ms);
    }

    // Form cppreference.com
    {

        struct X {
          void foo(int i, const std::string &str) {
              std::lock_guard<std::mutex> lk(m);
              std::cout << str << ' ' << i << '\n';
          }

          void bar(const std::string &str) {
              std::lock_guard<std::mutex> lk(m);
              std::cout << str << '\n';
          }

          int operator()(int i) {
              std::lock_guard<std::mutex> lk(m);
              std::cout << i << '\n';
              return i + 10;
          }
        };

        X x;
        // Calls (&x)->foo(42, "Hello") with default policy:
        // may print "Hello 42" concurrently or defer execution
        auto a1 = std::async(&X::foo, &x, 42, "Hello");
        // Calls x.bar("world!") with deferred policy
        // prints "world!" when a2.get() or a2.wait() is called
        auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
        // Calls X()(43); with async policy
        // prints "43" concurrently
        auto a3 = std::async(std::launch::async, X(), 43);
        a2.wait();                     // prints "world!"
        std::cout << a3.get() << '\n'; // prints "53"
    }
}

TEST(Concurrency, TestFeturesFeature) {
    // Default constructor
    std::future<void> futureDefault;
    ASSERT_EQ(futureDefault.valid(), false);
    // operator =
    auto futureMoved = std::move(futureDefault);
    ASSERT_EQ(futureMoved.valid(), false);
    // Move constructor
    std::future<void> futureMoved2(std::move(futureMoved));
    ASSERT_EQ(futureMoved2.valid(), false);

    auto future = std::async(std::launch::async, []() -> int {
      // do nothing, only share state with future
      return 10;
    });
    ASSERT_EQ(future.valid(), true);
    ASSERT_EQ(future.get(), 10);
    ASSERT_EQ(future.valid(), false);
}

TEST(Concurrency, TestFuturesPromise) {
    auto promise = std::promise<void>();
    auto future = promise.get_future();
    auto f = std::async(std::launch::async, [&promise]() {
      std::this_thread::sleep_for(500ms);
      std::cout << "set value\n";
      promise.set_value();
    });

    std::cout << "start wait\n";
    ASSERT_EQ(f.valid(), true);
    ASSERT_EQ(future.valid(), true);
    future.wait();
    f.wait();
}

TEST(Concurrency, TestFuturesPackaged_task) {
    std::packaged_task<int(int, int)> task([](int a, int b) { return a + b; });
    auto future = task.get_future();
    auto f = std::async(std::launch::async, [&task]() {
        std::this_thread::sleep_for(500ms);
        task(1, 1);
    });
}
