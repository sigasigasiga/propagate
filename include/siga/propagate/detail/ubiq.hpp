#pragma once

#include <utility>

#include <siga/propagate/detail/string_literal.hpp>
#include <siga/propagate/try_traits/try_traits.hpp>

namespace siga::propagate::detail {

template<string_literal PrettyFunction>
struct tag
{
    friend constexpr auto loophole(tag<PrettyFunction>);
};

template<typename ReturnType, string_literal PrettyFunction, bool HasLoophole>
struct loophole_write;

template<typename ReturnType, string_literal PrettyFunction>
requires try_traits::has_try_traits<ReturnType>
struct loophole_write<ReturnType, PrettyFunction, false>
{
    friend constexpr auto loophole(tag<PrettyFunction>) { return std::type_identity<ReturnType>{}; }
};

template<class ReturnType, string_literal PrettyFunction>
struct loophole_write<ReturnType, PrettyFunction, true>
{};

template<string_literal PrettyFunction>
struct ubiq
{
private:
    // Interesting trick from Boost.PFR:
    // 1. Compiler tries to invoke `ins(int)` because it's the best match
    //    and because `...` is always the last candidate to consider
    // 2. However, this function has a template parameter that depends on `loophole` function
    // 2.1. If `loophole` is found, then return `true_type`
    // 2.2. Otherwise, return `false_type`
    // 3. Pass the resulting `bool` to `loophole_write` as the last template parameter
    //
    // However, I don't really understand why `U` and `M` are needed
    template<typename U, string_literal M, std::size_t = sizeof(loophole(tag<M>{}))>
    static constexpr std::true_type ins(int)
    {
        return {};
    }

    template<typename U, string_literal M>
    static constexpr std::false_type ins(...)
    {
        return {};
    }

public:
    template<
        typename ReturnType,
        std::size_t =
            sizeof(loophole_write<ReturnType, PrettyFunction, ins<ReturnType, PrettyFunction>(0)>)>
    constexpr operator ReturnType &() const && noexcept
    {
        std::unreachable();
    }
};

template<string_literal PrettyFunction>
using function_return_type = decltype(loophole(tag<PrettyFunction>{}))::type;

} // namespace siga::propagate::detail
