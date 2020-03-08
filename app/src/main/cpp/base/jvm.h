#ifndef NATIVE_JVM_H
#define NATIVE_JVM_H

#include <base.h>

#ifdef __cplusplus
extern "C" {
#endif

    void setJVM(JavaVM *jvm);
    JavaVM *getJVM();

#ifdef __cplusplus
}; // extern "C"
#endif

#endif //NATIVE_JVM_H
