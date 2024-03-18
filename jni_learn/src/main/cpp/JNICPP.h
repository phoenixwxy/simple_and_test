//
// Created by phoenix on 2024/3/17.
//

#ifndef SIMPLE_TEST_JNICPP_H
#define SIMPLE_TEST_JNICPP_H

#include <string>

class JNICPP {
public:
    JNICPP();

    explicit JNICPP(int num);
    explicit JNICPP(int num, std::string string);
    ~JNICPP();

    static std::string s_String;

    std::string getStr();

    void setStr(std::string str);

    int getNum();

    void setNum(int num);

    std::string getStaticStr();
private:
    int mNum;
    std::string mString;
};


#endif //SIMPLE_TEST_JNICPP_H
