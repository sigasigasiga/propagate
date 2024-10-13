#pragma once

#include <utility>

#include <siga/propagate/detail/ubiq.hpp>

#define SIGA_PROPAGATE_TRY(EXPR)                                                                   \
    ({                                                                                             \
        namespace ppg = ::siga::propagate;                                                         \
                                                                                                   \
        if(false) {                                                                                \
            return ppg::detail::ubiq<__PRETTY_FUNCTION__>{};                                       \
        }                                                                                          \
                                                                                                   \
        using fn_return_type = ppg::detail::function_return_type<__PRETTY_FUNCTION__>;             \
        namespace ppg_tt = ppg::try_traits;                                                        \
                                                                                                   \
        /* p2561r0 semantics */                                                                    \
        using ret_traits = ppg_tt::try_traits<fn_return_type>;                                     \
                                                                                                   \
        auto &&val = EXPR;                                                                         \
        using expr_traits = ppg_tt::try_traits<::std::remove_cvref_t<decltype(val)>>;              \
        if(not ret_traits::is_ok(val)) {                                                           \
            return ret_traits::from_error(                                                         \
                expr_traits::extract_error(::std::forward<decltype(val)>(val))                     \
            );                                                                                     \
        }                                                                                          \
                                                                                                   \
        expr_traits::extract_value(::std::forward<decltype(val)>(val));                            \
    })
