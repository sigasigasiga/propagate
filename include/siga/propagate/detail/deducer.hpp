#pragma once

#include <siga/propagate/detail/string_literal.hpp>

namespace siga::propagate::detail {

template<string_literal Fn>
struct tag
{
    friend constexpr auto loophole(tag<Fn>);
};

template<string_literal Fn>
constexpr auto loophole(tag<Fn>);

template<string_literal Fn, typename ReturnType>
struct deducer_loophole
{
    friend constexpr auto loophole(tag<Fn>) { return std::type_identity<ReturnType>{}; };

    constexpr static auto init_loophole() { return loophole(tag<Fn>{}); }
};

template<string_literal Fn>
struct deducer
{
    template<typename T, std::size_t = sizeof(deducer_loophole<Fn, T>::init_loophole())>
    constexpr operator T()
    {
        std::unreachable();
    }
};

template<string_literal Fn>
using function_return_type = decltype(loophole(tag<Fn>{}))::type;

} // namespace siga::propagate::detail
