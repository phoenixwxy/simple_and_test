//
// Created by Phoenix on 8/6/24.
//
#include <gtest/gtest.h>

#include <sys/prctl.h>

#include <thread>

int main(int argc, char** argv) {
    std::cout << "argc: " << argc << "\n";


    std::this_thread::sleep_for(std::chrono::seconds(5));
    char name[128];
    auto ret = prctl(PR_GET_NAME, name);
    if (ret < 0) {
        std::printf("prctl(PR_GET_NAME): %s", strerror(ret));
    }
    std::cout << "name: " << name << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    ret = prctl(PR_SET_NAME, (unsigned long)"phoenix", 0, 0, 0);
    if (ret < 0) {
        std::printf("prctl(PR_SET_NAME): %s", strerror(ret));
    }
    std::cout << "set name to: os_func_learn\n";

    std::this_thread::sleep_for(std::chrono::seconds(5));
}