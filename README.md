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
#include <siga/propagate.hpp>

std::optional<double> g_opt;

std::optional<double> try_plus_one()
{
    return SIGA_PROPAGATE_TRY(g_opt) + 1;
}

int main()
{
    auto v1 = try_plus_one();
    assert(!v1);

    g_opt = 1;

    auto v2 = try_plus_one();
    assert(v2 == 2.0);
}
```

## Limitations

* Functions that return `std::optional<std::optional<T>>` are not supported
* Function that return references are not supported (though I don't know why one would ever use them in such scenario)
