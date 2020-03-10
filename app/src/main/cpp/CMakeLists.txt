# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
add_library(native-basic
            SHARED
            jni/jni_basic_type.cpp )

add_library(native-string
            SHARED
        jni/jni_string_type.cpp)

add_library(native-ref
            SHARED
            jni/jni_reference_type.cpp )

add_library(native-field
            SHARED
            jni/jni_access_field.cpp )

add_library(native-method
            SHARED
            jni/jni_access_method.cpp )

add_library(native-invoke
        SHARED
        base/jvm.cpp
        jni/jni_invoke_method.cpp )

add_library(native-constructor
        SHARED
        jni/jni_constructor_class.cpp )

add_library(native-execption
        SHARED
        jni/jni_execption.cpp )

add_library(native-thread
        SHARED
        jni/jni_thread.cpp )

add_library(native-notify
        SHARED
        jni/jni_wait_notify.cpp )

add_library(native-bitmap
        SHARED
        jni/jni_bitmap.cpp )

add_library( # Sets the name of the library.
             dynamic-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             jni/jni_dynamic_load.cpp )

include_directories(${CMAKE_CURRENT_LIST_DIR}/base/)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       dynamic-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )

target_link_libraries( native-basic
        ${log-lib} )

target_link_libraries( native-string
        ${log-lib} )

target_link_libraries( native-ref
        ${log-lib} )

target_link_libraries( native-field
        ${log-lib} )

target_link_libraries( native-method
        ${log-lib} )

target_link_libraries( native-invoke
        ${log-lib} )

target_link_libraries( native-constructor
        ${log-lib} )

target_link_libraries( native-execption
        ${log-lib} )

target_link_libraries( native-thread
        ${log-lib} )

target_link_libraries( native-notify
        ${log-lib} )

target_link_libraries( native-bitmap
        jnigraphics
        ${log-lib} )