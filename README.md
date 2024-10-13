# siga.propagate

A GNU-C++23 library that attempts to implement something close to `operator??` that is proposed under [P2561](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2561r2.html).

# Requirements

C++23 compiler that supports GNU's [statement exprs](https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html) extension.

Tested on:
* gcc 14.1
* clang 18.1

# How to use

```cpp
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
```

# Limitations

* `std::optional<std::optional<T>>` is not supported
* Reference types are not supported (though I don't know why would one ever use them)
