//
// Created by Phoenix on 8/13/24.
//

#include <gtest/gtest.h>

#include <numeric>
#include <vector>
#include <string>

template<typename T, std::enable_if_t<std::is_same<T, std::string>::value, bool> = true>
std::string vectorToString(const std::vector<T> &vec) {
    return vec.empty() ? "" : std::accumulate(
        vec.begin() + 1, vec.end(), *vec.begin(),
        [](const std::string &a, const T &b) { return a + ", " + b; });
}

template<typename T, std::enable_if_t<std::is_fundamental_v<T>, bool> = true>
std::string vectorToString(const std::vector<T> &vec) {
    return vec.empty() ? "" : std::accumulate(
        vec.begin() + 1, vec.end(), std::to_string(*vec.begin()),
        [](const std::string &a, const T &b) { return a + ", " + std::to_string(b); });
}

template<typename T, std::enable_if_t<std::is_class_v<T> && !std::is_same_v<T, std::string>, bool> = true>
std::string vectorToString(const std::vector<T> &vec) {
    return vec.empty() ? "" : std::accumulate(
        vec.begin() + 1, vec.end(), vec.begin()->toString(),
        [](const std::string &a, const T &b) { return a + ", " + b.toString(); });
}

TEST(Metaprogramming, test1) {
    class Test {
    public:
        explicit Test(std::vector<int32_t> nums) : nums(std::move(nums)) {}

        std::string toString() const {
            return vectorToString<int32_t>(nums);
        }

    private:
        std::vector<int32_t> nums;
    };

    Test test({1, 2, 3});
    std::cout << test.toString() << std::endl;
    EXPECT_EQ(test.toString(), "1, 2, 3");

    std::vector<Test> tests = {Test({1, 2, 3}), Test({4, 5, 6})};

    std::cout << vectorToString<Test>(tests) << std::endl;

    std::vector<std::string> strings = {"hello", "world"};
    std::cout << vectorToString<std::string>(strings) << std::endl;
}