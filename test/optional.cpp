#include <siga/propagate/try_traits/optional.hpp>
#include <siga/propagate/detail/deducer.hpp>

std::optional<int> foo()
{
    return {};
}

std::optional<double> bar()
{
    if(false) {
        return siga::propagate::detail::deducer<__PRETTY_FUNCTION__>{};
    }
}

int main()
{
}
