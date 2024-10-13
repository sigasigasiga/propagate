#pragma once

#include <optional>

#include <siga/propagate/try_traits/try_traits.hpp>

namespace siga::propagate::try_traits {

template<class T>
class try_traits<std::optional<T>>
{
public:
    using value_type = T;
    using error_type = std::nullopt_t;

public:
    static bool is_ok(const std::optional<T> &o) { return o.has_value(); }

    template<typename U>
    static auto &&extract_value(U &&o)
    {
        return *std::forward<U>(o);
    }

    static error_type extract_error(auto &&) { return std::nullopt; }

    template<typename U>
    static std::optional<T> from_value(U &&v)
    {
        return std::optional<T>(std::in_place, std::forward<U>(v));
    }

    static std::optional<T> from_error(std::nullopt_t) { return {}; }
};

static_assert(has_try_traits<std::optional<int>>);

} // namespace siga::propagate::try_traits
