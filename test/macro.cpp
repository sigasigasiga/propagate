#include <siga/propagate.hpp>

std::optional<double> g_opt;

std::optional<double> try_plus_one()
{
    return SIGA_PROPAGATE_TRY(g_opt) + 1;
}

int main()
{
    auto v1 = try_plus_one();
    if(v1) {
        abort();
    }

    g_opt = 1;

    auto v2 = try_plus_one();
    if(v2 != 2.0) {
        abort();
    }
}
