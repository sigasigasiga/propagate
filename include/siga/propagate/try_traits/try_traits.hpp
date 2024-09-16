#pragma once

namespace siga::propagate::try_traits {

template<typename T>
class try_traits
{
public:
    using detail__is_unspecialized = void;
};

template<typename T>
concept has_try_traits = !requires { typename try_traits<T>::detail__is_unspecialized; };

} // namespace siga::propagate::try_traits
