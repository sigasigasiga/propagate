#include <string>

#include <siga/propagate.hpp>

struct my_error_type
{};

std::expected<int, my_error_type> g_ex;

std::expected<std::string, my_error_type> try_ex_to_string()
{
    return std::to_string(SIGA_PROPAGATE_TRY(g_ex));
}

void test_ex()
{
    g_ex = std::unexpected{my_error_type{}};

    auto v1 = try_ex_to_string();
    if(v1.has_value()) {
        abort();
    }

    g_ex = 777;
    auto v2 = try_ex_to_string();
    if(v2 != "777") {
        abort();
    }
}

// -----------------------------------------------------------------------------

std::optional<int> &get_opt()
{
    static std::optional<int> ret;
    return ret;
}

std::optional<std::string> try_opt_to_string()
{
    return std::to_string(SIGA_PROPAGATE_TRY(get_opt()));
}

void test_opt()
{
    get_opt() = std::nullopt;

    auto v1 = try_opt_to_string();
    if(v1.has_value()) {
        abort();
    }

    get_opt() = 777;
    auto v2 = try_opt_to_string();
    if(v2 != "777") {
        abort();
    }
}

int main()
{
    test_ex();
    test_opt();
}
