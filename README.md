# siga.propagate

A GNU-C++23 library that implements a macro which behaves like `operator??` that is proposed under [P2561](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2561r2.html).

It supports:
* Function return type retrieval
* `try_traits`
* Usage inside an expression

## Requirements

Your C++ compiler must support:
* C++23
* GNU's [statement exprs](https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html) extension
* [Type loopholes](https://alexpolt.github.io/type-loophole.html) (probably every compiler supports them though)

Tested on:
* gcc 14.1
* clang 18.1

## How to use

```cpp
#include <cassert>
#include <string>

#include <siga/propagate.hpp>

struct my_error_type
{};

std::expected<int, my_error_type> g_ex;

std::expected<std::string, my_error_type> try_ex_to_string()
{
    return std::to_string(SIGA_PROPAGATE_TRY(g_ex));
}

int main()
{
    g_ex = std::unexpected{my_error_type{}};

    auto v1 = try_ex_to_string();
    assert(!v1);

    g_ex = 777;
    auto v2 = try_ex_to_string();
    assert(v2 == "777");
}
```

```cpp
#include <cassert>
#include <string>

#include <siga/propagate.hpp>

std::optional<int> &get_opt()
{
    static std::optional<int> ret;
    return ret;
}

std::optional<std::string> try_opt_to_string()
{
    return std::to_string(SIGA_PROPAGATE_TRY(get_opt()));
}

int main()
{
    get_opt() = std::nullopt;

    auto v1 = try_opt_to_string();
    assert(!v1);

    get_opt() = 777;
    auto v2 = try_opt_to_string();
    assert(v2 == "777");
}
```

## Limitations

* Functions that return `std::optional<std::optional<T>>` are not supported
* Function that return references are not supported (though I don't know why one would ever use them in such scenario)
