//
// Created by Phoenix on 8/7/24.
//
#include <gtest/gtest.h>

TEST(Language, TestEnumClass) {
    enum class TestEnumClass : int32_t {
      A = 1,
      B = 2,
    };

    // Not Supported
//    enum class SubEnumClass : public TestEnumClass {
//        C = 3,
//    };
}

TEST(Language, TestClassMember) {
    struct Callback {
      std::function<void()> callback_;
    };

    class Test {
    public:
        void setCallback(Callback
                         &callback) {
            callback_ = callback;
        }
        void process() const {
            callback_.callback_();
        }

    private:
        const Callback callback_;
    };

    class Base{
    public:
        void test() {
            callback_.callback_ = []() {
              std::cout << "hello" << std::endl;
            };

            test_.setCallback(callback_);
        }

        void testCallback() {
            test_.process();
        }
    private:
        Test test_;
        Callback callback_;
    };

    Base base;
    base.test();

    base.testCallback();
}
