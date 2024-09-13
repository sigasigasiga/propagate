#include <type_traits>

#include <siga/propagate/detail/deducer.hpp>

std::string foo()
{
    if(false) {
        return siga::propagate::detail::deducer<__PRETTY_FUNCTION__>{};
    }

    using foo_return_type = siga::propagate::detail::function_return_type<__PRETTY_FUNCTION__>;
    static_assert(std::is_same_v<foo_return_type, std::string>);

    return "";
}

int main()
{
    (void)foo();
}
