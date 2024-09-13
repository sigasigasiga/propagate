#pragma once

#include <algorithm>
#include <stdexcept>
#include <string_view>

namespace siga::propagate::detail {

template<std::size_t N>
struct [[nodiscard]] string_literal
{
public:
    static_assert(N > 0);
    static constexpr std::size_t size = N - 1;

public:
    constexpr string_literal() = default;

    constexpr string_literal(const char (&str)[N])
    {
        if(str[N - 1] == '\0') {
            std::ranges::copy(str, std::ranges::begin(data));
        } else {
            throw std::invalid_argument{"the string must be null-terminated"};
        }
    }

public:
    [[nodiscard]] constexpr std::string_view as_view() const noexcept { return data; }
    [[nodiscard]] constexpr operator std::string_view() const noexcept { return as_view(); }

public:
    char data[N] = {};
};

} // namespace siga::propagate::detail
