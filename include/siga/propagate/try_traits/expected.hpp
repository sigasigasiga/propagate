#pragma once

#include <expected>

#include <siga/propagate/try_traits/try_traits.hpp>

namespace siga::propagate::try_traits {

template<typename T, typename E>
class try_traits<std::expected<T, E>>
{
public:
    using value_type = T;
    using error_type = E;

public:
    static bool is_ok(const std::expected<T, E> &e) { return e.has_value(); }

    template<typename U>
    static auto &&extract_value(U &&e)
    {
        return *std::forward<U>(e);
    }

    template<typename U>
    static auto &&extract_error(U &&e)
    {
        return std::forward<U>(e).error();
    }

    template<typename U>
    static std::expected<T, E> from_value(U &&v)
    {
        return std::expected<T, E>(std::in_place, std::forward<U>(v));
    }

    template<typename U>
    static std::expected<T, E> from_error(U &&e)
    {
        return std::expected<T, E>(std::unexpect, std::forward<U>(e));
    }
};

static_assert(has_try_traits<std::expected<short, long>>);

} // namespace siga::propagate::try_traits
