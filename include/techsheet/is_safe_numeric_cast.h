#pragma once
#include <type_traits>
namespace techsheet
{
namespace cast_helpers
{
// pred_base selects the appropriate base type (true_type or false_type) to
// make defining our own predicates easier.

template<bool> struct pred_base : std::false_type {};
template<>     struct pred_base<true> : std::true_type {};

// same_decayed
// -------------
// Are the decayed versions of "T" and "O" the same basic type?
// Gets around the fact that std::is_same will treat, say "bool" and "bool&" as
// different types and using std::decay all over the place gets really verbose

template <class T, class O>
struct same_decayed
  : pred_base <std::is_same<typename std::decay<T>::type, typename std::decay<O>::type>::value>
{};


// is_numeric.  Is it a number?  i.e. true for floats and integrals but not bool

template<class T>
struct is_numeric
  : pred_base<std::is_arithmetic<T>::value && !same_decayed<bool, T>::value>
{};


// both - less verbose way to determine if TWO types both meet a single predicate

template<class A, class B, template<typename> class PRED>
struct both
  : pred_base<PRED<A>::value&& PRED<B>::value>
{};

// Some simple typedefs of both (above) for common conditions

template<class A, class B> struct both_numeric : both<A, B, is_numeric> {};    // Are both A and B numeric        types?
template<class A, class B> struct both_floating : both<A, B, std::is_floating_point> {};    // Are both A and B floating point types?
template<class A, class B> struct both_integral : both<A, B, std::is_integral> {};    // Are both A and B integral       types
template<class A, class B> struct both_signed : both<A, B, std::is_signed> {};    // Are both A and B signed         types
template<class A, class B> struct both_unsigned : both<A, B, std::is_unsigned> {};    // Are both A and B unsigned       types


// Returns true if both number types are signed or both are unsigned
template<class T, class F>
struct same_signage
  : pred_base<(both_signed<T, F>::value) || (both_unsigned<T, F>::value)>
{};
}


// And here, finally is the trait I wanted in the first place:  is_safe_numeric_cast
template <class T, class F>
struct is_safe_numeric_cast
  : cast_helpers::pred_base <cast_helpers::both_numeric<T, F>::value &&                            // Obviously both src and dest must be numbers
  (std::is_floating_point<T>::value && (std::is_integral<F>::value || sizeof(T) >= sizeof(F))) ||  // Floating dest: src must be integral or smaller/equal float-type
  ((cast_helpers::both_integral<T, F>::value) &&                                                   // Integral dest: src must be integral and (smaller/equal+same signage) or (smaller+different signage)
    (sizeof(T) > sizeof(F) || (sizeof(T) == sizeof(F) && cast_helpers::same_signage<T, F>::value)))>
{
};
template <class T, class F>
constexpr bool is_safe_numeric_cast_v = is_safe_numeric_cast<T, F>::value;
}