#include <string>
#include <type_traits>

#include <siga/propagate/detail/ubiq.hpp>

template<>
class siga::propagate::try_traits::try_traits<std::string>
{
public:
    using value_type = std::string;
    using error_type = std::string;

public:
    static bool is_ok(std::string) { return true; }
    static value_type extract_value(std::string s) { return s; }
    static error_type extract_error(std::string s) { return s; }
};

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
