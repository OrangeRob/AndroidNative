#include "jvm.h"

JavaVM *gvm = nullptr;

void setJVM(JavaVM *jvm) {
    gvm = jvm;
}

JavaVM *getJVM() {
    return gvm;
}
