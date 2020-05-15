#include "common.h"

//#include "chainedOverloadsOnDifferentTypes.h"
//#include "forEach.h"
//#include "dispatchFunction.h"
//#include "makeTupleOfParams.h"

struct remove_const_meta_function_class
{
    template<typename T> struct apply
    {
        // meta_function
        using type = typename std::remove_const_t<T>;
    };
};

// generic version of above
template<template<typename...>typename meta_function>
struct meta_function_class_maker
{
    struct type
    {
        template<typename... args> struct apply
        {
            using type = typename meta_function<args...>::type;
        };
    };
};

template<typename List, typename F> struct transform {};

template<template<class...> class List, class... Elems, class F>
struct transform<List<Elems...>, F>
{
    template <typename T> using call = typename F::template apply<T>::type;
    using type = List<call<Elems>...>;
};

int main()
{
 

    //using tuple_no_ptr = transform<meta_function_class_maker<std::remove_pointer>, std::tuple<int*, double*>>::type;
    //tuple_no_ptr a = std::make_tuple(1, 2.0);
    /*
    // Test for chainedOverloadsOnDifferentTypes.h
    ClassA a;
    ClassB b;
    ClassC c;

    run(a, b); // works!
    //run(c);  // does not compile
    */
}





