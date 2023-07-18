#pragma once
#include <type_traits>
namespace std
{
#ifndef DISABLE_STL_POLYFILL

#if __cplusplus < 202002L

inline constexpr bool is_constant_evaluated() { return false; }
template<class T>
struct remove_cvref
{
  using type = remove_cv_t<remove_reference_t<T>>;
};
template<class T>
using remove_cvref_t = typename remove_cvref<T>::type;
#endif

#endif
}