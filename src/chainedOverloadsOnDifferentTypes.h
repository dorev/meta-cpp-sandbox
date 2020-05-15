#pragma once
#include "common.h"

struct ClassA {};
struct ClassB {};
struct ClassC {};

template<typename T> struct is_my_class : std::false_type {};
template<>           struct is_my_class<ClassA> : std::true_type {};
template<>           struct is_my_class<ClassB> : std::true_type {};

template<typename T>
constexpr bool is_my_class_v = is_my_class<T>::value;

void runOverload(ClassA c) { printf("ClassA overload\n"); }
void runOverload(ClassB c) { printf("ClassB overload\n"); }

/*
This does not allow a fallback
https://stackoverflow.com/questions/61526391/c-stdenable-if-fallback

template<typename T, typename = std::enable_if_t<is_my_class_v<T>>>
void run(T myClass)
{
    runOverload(myClass);
};
*/

template<typename T, std::enable_if_t<is_my_class_v<T>, int> = 0>
void run(T myClass)
{
    runOverload(myClass);
};

template<typename T, std::enable_if_t<!is_my_class_v<T>, int> = 0>
void run(T myClass)
{
    static_assert(false, "Not supported!"); // compile time error
    //printf("Not supported\n");  // runtime fallback
};

/* C++17 easy solution
template<typename T>
void run(T myClass)
{
    if constexpr (is_my_class_v<T>)
        runOverload(myClass);
    else
        printf("Not supported\n");  // runtime fallback
}
*/

template<typename T, typename... Ts>
void run(T myClass, Ts... classesLeft)
{
    run(myClass);
    run(classesLeft...);
};
