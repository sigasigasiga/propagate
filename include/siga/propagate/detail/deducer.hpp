#pragma once

#include <utility>

#include <siga/propagate/detail/string_literal.hpp>
#include <siga/propagate/try_traits/try_traits.hpp>

namespace siga::propagate::detail {

template<string_literal Fn>
struct tag
{
    friend constexpr auto loophole(tag<Fn>);
};

template<string_literal Fn, typename ReturnType>
struct deducer_loophole
{
    constexpr static char init_loophole();
};

template<string_literal Fn, typename ReturnType>
requires try_traits::has_try_traits<ReturnType>
struct deducer_loophole<Fn, ReturnType>
{
    friend constexpr auto loophole(tag<Fn>) { return std::type_identity<ReturnType>{}; };

    constexpr static auto init_loophole() { return loophole(tag<Fn>{}); }
};

template<string_literal Fn>
struct deducer
{
    template<typename T, std::size_t = sizeof(deducer_loophole<Fn, T>::init_loophole())>
    requires try_traits::has_try_traits<T>
    constexpr operator T &() const noexcept
    {
        std::unreachable();
    }
};

template<string_literal Fn>
using function_return_type = decltype(loophole(tag<Fn>{}))::type;

} // namespace siga::propagate::detail
