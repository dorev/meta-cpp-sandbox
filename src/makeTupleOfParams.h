#pragma once
#include "common.h"

// base template
template<typename Function>
struct makeTupleOfParams
{
};

// template specialization to identify function pointer
template <typename Return, typename... Params>
struct makeTupleOfParams<Return(*)(Params...)>
{
    using type = std::tuple<Params...>;
};

// template specialization to identify method pointer
template <typename Class, typename Return, typename... Params>
struct makeTupleOfParams<Return(Class::*)(Params...)>
{
    using type = std::tuple<Params...>;
};

// shortcut to identify type of parameters
template <typename Function>
using tupleOfParamTypes_t = typename makeTupleOfParams<Function>::type;