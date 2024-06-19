//
// Created by mi on 6/13/24.
//

#include "SimpleThirdLib.h"

#include <android/log.h>

namespace phoenix {
SimpleThirdLib::SimpleThirdLib() {
    __android_log_print(ANDROID_LOG_ERROR,
                        "PhoenixDebug", "SimpleThirdLib()");
}

SimpleThirdLib::~SimpleThirdLib() {
    __android_log_print(ANDROID_LOG_ERROR,
                        "PhoenixDebug", "~SimpleThirdLib()");
}
} // phoenix