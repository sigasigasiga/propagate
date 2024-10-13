#include <siga/propagate/try_traits/optional.hpp>
#include <siga/propagate/detail/ubiq.hpp>

std::optional<double> single_optional()
{
    if(false) {
        return siga::propagate::detail::ubiq<__PRETTY_FUNCTION__>{};
    }

    using return_type = siga::propagate::detail::function_return_type<__PRETTY_FUNCTION__>;
    static_assert(std::is_same_v<return_type, std::optional<double>>);

    return {};
}

#if 0
// FIXME
std::optional<std::optional<double>> double_optional()
{
    if(false) {
        return siga::propagate::detail::ubiq<__PRETTY_FUNCTION__>{};
    }

    using return_type = siga::propagate::detail::function_return_type<__PRETTY_FUNCTION__>;
    static_assert(std::is_same_v<return_type, std::optional<std::optional<double>>>);
}
#endif

int main()
{
}
