#pragma once
#include "common.h"

// function to unroll a tuple of parameters on a function
template <typename Function, typename Params, size_t... Index>
auto dispatchParams(Function f, Params p, std::index_sequence<Index...>)
{
    return f(std::get<Index>(p)...);
}

template <typename Function, typename... Params>
auto call(Function f, Params... p)
{
    // getting size of Params and argument types of Function
    constexpr size_t paramsCount = sizeof...(Params);

    auto params = std::make_tuple(p...);

    return dispatchParams(f, params, std::make_index_sequence<paramsCount>());
}