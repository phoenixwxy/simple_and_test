//
// Created by phoenix on 2024/3/17.
//

#include "JNICPP.h"

std::string JNICPP::s_String = "Static String";

JNICPP::JNICPP() {

}

JNICPP::JNICPP(int num) : mNum(num) {

}

JNICPP::JNICPP(int num, std::string string) : mNum(num), mString(string) {

}

JNICPP::~JNICPP() {

}

std::string JNICPP::getStr() {
    return mString;
}

int JNICPP::getNum() {
    return mNum;
}

void JNICPP::setNum(int num) {
    this->mNum = num;
}

void JNICPP::setStr(std::string str) {
    this->mString = str;
}

std::string JNICPP::getStaticStr() {
    return s_String;
}

