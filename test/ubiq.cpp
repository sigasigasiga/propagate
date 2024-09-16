#include <string>
#include <type_traits>

#include <siga/propagate/detail/ubiq.hpp>

template<>
struct siga::propagate::try_traits::try_traits<std::string>
{};

std::string foo()
{
    if(false) {
        return siga::propagate::detail::ubiq<__PRETTY_FUNCTION__>{};
    }

    using foo_return_type = siga::propagate::detail::function_return_type<__PRETTY_FUNCTION__>;
    static_assert(std::is_same_v<foo_return_type, std::string>);

    return "";
}

int main()
{
    (void)foo();
}
