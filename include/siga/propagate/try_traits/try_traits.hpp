#pragma once

#include <concepts>

namespace siga::propagate::try_traits {

template<typename T>
class try_traits;

template<typename T>
concept has_try_traits = requires(T value) {
    typename try_traits<T>::value_type;
    typename try_traits<T>::error_type;

    { try_traits<T>::is_ok(value) } -> std::convertible_to<bool>;

    {
        try_traits<T>::extract_value(value)
    } -> std::convertible_to<typename try_traits<T>::value_type>;

    {
        try_traits<T>::extract_error(value)
    } -> std::convertible_to<typename try_traits<T>::error_type>;

    // TODO: add a check for `from_value` and `from_error` somehow
};

} // namespace siga::propagate::try_traits
