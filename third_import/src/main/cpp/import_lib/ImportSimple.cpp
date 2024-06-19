//
// Created by mi on 6/14/24.
//

#include "ImportSimple.h"

#include "SimpleThirdLib.h"

#include <android/log.h>

namespace phoenix {

ImportSimple::ImportSimple() {
    __android_log_print(ANDROID_LOG_ERROR,
                        "PhoenixDebug", "ImportSimple()");
    SimpleThirdLib simple_third_lib;
}

ImportSimple::~ImportSimple() {
    __android_log_print(ANDROID_LOG_ERROR,
                        "PhoenixDebug", "~ImportSimple()");
}
} // phoenix