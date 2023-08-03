#pragma once
#include "is_safe_numeric_cast.h"
#include "template_defs.h"

#include <initializer_list>
#include <limits>
#include <type_traits>


namespace techsheet
{

struct NumberIshOpts final
{
  using option_t = unsigned short;
  enum class Opt : option_t
  {
    NO_OPT = 0,
    ALL_OPTS = 0xFFFF,
    ADD_SELF = 1,
    ADD_UNDERLYING = 2,
    ADD_UNDERLYING_CREATES_SELF = 4,
    MULTIPLY_SELF = 8,
    MULTIPLY_UNDERLYING = 16,
    MULTIPLY_UNDERLYING_CREATES_SELF = 32,
    COMPARE_SELF = 64,
    COMPARE_UNDERLYING = 128,
    DEFAULT_CTOR = 256
  };

  /*
  * What is the result of an operation with the undrelying type?
  * 
  * Self means it returns instance of the NumberIsh implementing class,
  * INNER means it returns the inner/underlying type
  */
  enum class OpWithInner
  {
    DISABLED = 0,
    CREATES_UNDERLYING = 1,
    CREATES_SELF = 2
  };

  constexpr NumberIshOpts(Opt o) : opts{ o } {}

  Opt opts;

  constexpr NumberIshOpts addSelf(bool status) const
  {
    return setOpt(Opt::ADD_SELF, status);
  }

  constexpr NumberIshOpts addUnderlying(OpWithInner mode) const
  {
    return setUnderlyingOpt(Opt::ADD_UNDERLYING, mode);
  }

  constexpr NumberIshOpts addEither(bool status) const
  {
    return setOpt(Opt::ADD_SELF, status)
      .setOpt(Opt::ADD_SELF, status)
      .setOpt(Opt::ADD_UNDERLYING_CREATES_SELF, false);
  }

  constexpr NumberIshOpts addEitherToSelf(bool status) const
  {
    return setOpt(Opt::ADD_SELF, status)
      .setOpt(Opt::ADD_SELF, status)
      .setOpt(Opt::ADD_UNDERLYING_CREATES_SELF, status);
  }

  constexpr NumberIshOpts multiplySelf(bool status) const
  {
    return setOpt(Opt::MULTIPLY_SELF, status);
  }

  constexpr NumberIshOpts multiplyUnderlying(OpWithInner mode) const
  {
    return setUnderlyingOpt(Opt::MULTIPLY_UNDERLYING, mode);
  }

  constexpr NumberIshOpts compareSelf(bool status) const
  {
    return setOpt(Opt::COMPARE_SELF, status);
  }

  constexpr NumberIshOpts compareUnderlying(bool status) const
  {
    return setOpt(Opt::COMPARE_UNDERLYING, status);
  }

  constexpr NumberIshOpts compareEither(bool status) const
  {
    return compareSelf(status).compareUnderlying(status);
  }
  /*
  * Set this to true if you want default ctor generated
  */
  constexpr NumberIshOpts defCtor(bool status) const
  {
    return setOpt(Opt::DEFAULT_CTOR, status);
  }

  constexpr bool hasOpt(NumberIshOpts opt) const
  {
    return (*this & opt) != Opt::NO_OPT;
  }

  constexpr bool canAddSelf() const { return hasOpt(Opt::ADD_SELF); }
  constexpr bool canAddUnderlying() const { return hasOpt(Opt::ADD_UNDERLYING); }
  constexpr bool canMultiplySelf() const { return hasOpt(Opt::MULTIPLY_SELF); }
  constexpr bool canMultiplyUnderlying() const { return hasOpt(Opt::MULTIPLY_UNDERLYING); }
  constexpr bool canCompareSelf() const { return hasOpt(Opt::COMPARE_SELF); }
  constexpr bool canCompareUnderlying() const { return hasOpt(Opt::COMPARE_UNDERLYING); }

  constexpr static NumberIshOpts defaults()
  {
    return Opt::COMPARE_SELF;
  }

  constexpr static NumberIshOpts none()
  {
    return Opt::NO_OPT;
  }

  constexpr operator Opt() const { return opts; }

  constexpr NumberIshOpts operator|(const NumberIshOpts other) const
  {
    return mergeOpts(opts, other.opts);
  }

  constexpr static NumberIshOpts mergeOpts(Opt a, Opt b)
  {
    return NumberIshOpts{ static_cast<option_t>(static_cast<option_t>(a) | static_cast<option_t>(b)) };
  }

private:

  explicit constexpr NumberIshOpts(option_t val) : opts{ static_cast<Opt>(val) } {}

  constexpr NumberIshOpts operator&(const NumberIshOpts other) const
  {
    return NumberIshOpts{ static_cast<option_t>(static_cast<option_t>(opts) & static_cast<option_t>(other.opts)) };
  }

  constexpr NumberIshOpts setOpt(Opt opt, bool state) const
  {
    if (state)
    {
      return *this | NumberIshOpts(opt);
    }
    else
    {
      return *this & NumberIshOpts(~static_cast<option_t>(opt));
    }
  }
  constexpr NumberIshOpts setUnderlyingOpt(Opt operation, OpWithInner mode) const
  {
    Opt result_opt = Opt::NO_OPT;
    switch (operation)
    {
    case Opt::ADD_UNDERLYING: result_opt = Opt::ADD_UNDERLYING_CREATES_SELF; break;
    case Opt::MULTIPLY_UNDERLYING: result_opt = Opt::MULTIPLY_UNDERLYING_CREATES_SELF; break;
    default: mode = OpWithInner::DISABLED; operation = Opt::NO_OPT;
    }
    const bool status = mode != OpWithInner::DISABLED;
    if (status)
    {
      return setOpt(operation, true).setOpt(result_opt, mode == OpWithInner::CREATES_SELF);
    }
    else
    {
      return setOpt(operation, false).setOpt(result_opt, false);
    }
  }
};

template<typename base_t,
  // this is the type that inherits NumberIsh
  typename type_t,
  // flags
  NumberIshOpts::Opt flags_v>
struct NumberIsh
{
  static_assert(std::is_arithmetic_v<base_t>, "NumberIsh needs a numeric underlying type");
  using base_type = base_t;
  using WrapperType = type_t;

  constexpr static NumberIshOpts flags{ flags_v };
  constexpr static base_type max_base_value = std::numeric_limits<base_type>::max();
  constexpr static base_type min_base_value = std::numeric_limits<base_type>::min();

  // handy so that inheriting class does not have to repeat all template arguments
  using SelfType = NumberIsh;
  template <typename TTest>
  static constexpr bool is_constructible_from = is_safe_numeric_cast_v<base_type, TTest> || std::is_same_v<WrapperType, TTest>;

  explicit constexpr NumberIsh(base_type value) : value(value) {}
  explicit constexpr NumberIsh(const WrapperType& value) : value(value.value) 
  {
    static_assert(std::is_base_of_v<NumberIsh, WrapperType>, "Must provide struct that inherits NumberIsh");
  }
  constexpr NumberIsh() : value{} { static_assert(flags.hasOpt(NumberIshOpts::Opt::DEFAULT_CTOR), "NumberIsh implicit ctor must be explicitly enabled"); }
  // explicit conversion is allowed
  explicit constexpr operator base_type() const
  {
    return value;
  }

  base_type value;

#pragma region self comparison
  constexpr bool operator==(WrapperType other) const
  {
    return other.value == value;
  }
  constexpr bool operator!=(WrapperType other) const
  {
    return other.value != value;
  }

  constexpr bool operator>(WrapperType other) const
  {
    static_assert(flags.canCompareSelf(), "Size comparison with same type not supported");
    return value > other.value;
  }
  constexpr bool operator<(WrapperType other) const
  {
    static_assert(flags.canCompareSelf(), "Size comparison with same type not supported");
    return value < other.value;
  }
  constexpr bool operator>=(WrapperType other) const
  {
    return *this > other || *this == other;
  }
  constexpr bool operator<=(WrapperType other) const
  {
    return *this < other || *this == other;
  }
#pragma endregion
#pragma region base type comparison
  static constexpr auto base_comparison_enabled = flags.canCompareUnderlying();
  constexpr bool operator==(base_type other) const
  {
    static_assert(base_comparison_enabled, "Cannot compare with underlying type");
    return other == value;
  }
  constexpr bool operator!=(base_type other) const
  {
    static_assert(base_comparison_enabled, "Cannot compare with underlying type");
    return other != value;
  }

  constexpr bool operator>(base_type other) const
  {
    static_assert(base_comparison_enabled, "Cannot compare with underlying type");
    return value > other;
  }
  constexpr bool operator<(base_type other) const
  {
    static_assert(base_comparison_enabled, "Cannot compare with underlying type");
    return value < other;
  }
  constexpr bool operator>=(base_type other) const
  {
    return *this > other || *this == other;
  }
  constexpr bool operator<=(base_type other) const
  {
    return *this < other || *this == other;
  }
#pragma endregion
#pragma region operations with self

  constexpr WrapperType operator+(WrapperType other) const
  {
    static_assert(flags.canAddSelf(), "Addition with same type not supported");
    return WrapperType(value + other.value);
  }

  /*
  * Safe clamped addition. This will not underflow and always result in max/min possible
  * value in cases where the result cannot fit
  *
  * This results in `this + other` operation.
  */
  constexpr WrapperType add_clamp(WrapperType other) const
  {
    static_assert(flags.canAddSelf(), "Addition with same type not supported");
    return WrapperType{ clamped_add(value, other.value) };
  }

  constexpr WrapperType& operator+=(WrapperType other)
  {
    static_assert(flags.canAddSelf(), "Addition with same type not supported");
    value += other.value;
    return static_cast<WrapperType&>(*this);
  }

  constexpr WrapperType& operator-=(WrapperType other)
  {
    static_assert(flags.canAddSelf(), "Substraction with same type not supported");
    value -= other.value;
    return static_cast<WrapperType&>(*this);
  }

  constexpr WrapperType& operator++()
  {
    static_assert(flags.canAddSelf(), "Increment not supported");
    ++value;
    return *this;
  }

  constexpr WrapperType& operator--()
  {
    static_assert(flags.canAddSelf(), "Decrement not supported");
    --value;
    return *this;
  }

  constexpr WrapperType operator++(int)
  {
    static_assert(flags.canAddSelf(), "Increment not supported");
    WrapperType res{ *this };
    ++value;
    return res;
  }

  constexpr WrapperType operator--(int)
  {
    static_assert(flags.canAddSelf(), "Decrement not supported");
    WrapperType res{ *this };
    --value;
    return res;
  }

  constexpr WrapperType operator-(WrapperType other) const
  {
    static_assert(flags.canAddSelf(), "Substraction with same type not supported");
    return WrapperType(value - other.value);
  }

  /*
  * Safe clamped substraction. This will not underflow and always result in max/min possible
  * value in cases where the result cannot fit.
  * 
  * This results in `this - other` operation.
  */
  constexpr WrapperType substract_clamp(WrapperType other) const
  {
    static_assert(flags.canAddSelf(), "Substraction with same type not supported");
    return WrapperType{ clamped_substract(value, other.value) };
  }

  constexpr WrapperType operator*(WrapperType other) const
  {
    static_assert(flags.canMultiplySelf(), "Multiplication with same type not supported");
    return WrapperType(value * other.value);
  }

  constexpr WrapperType operator/(WrapperType other) const
  {
    static_assert(flags.canMultiplySelf(), "Division with same type not supported");
    return WrapperType(value / other.value);
  }

#pragma endregion
#pragma region operations with base type

  static constexpr auto underlying_enabled_add = flags.canAddUnderlying();
  static constexpr auto underlying_enabled_mult = flags.canMultiplyUnderlying();
  using underlying_add_result_t = 
    typename std::conditional < 
      flags.hasOpt(NumberIshOpts::Opt::ADD_UNDERLYING_CREATES_SELF), WrapperType, base_type 
    >::type;
  using underlying_mult_result_t = 
    typename std::conditional < 
    flags.hasOpt(NumberIshOpts::Opt::MULTIPLY_UNDERLYING_CREATES_SELF), WrapperType, base_type
    >::type;

  // operator- really means value * (-1)
  constexpr underlying_mult_result_t operator-() const
  {
    static_assert(underlying_enabled_mult, "Operator - not supported");
    return underlying_mult_result_t(-value);
  }

  constexpr underlying_add_result_t operator+(base_type other) const
  {
    static_assert(underlying_enabled_add, "Addition with underlying type not supported");
    return underlying_add_result_t(value + other.value);
  }

  /*
  * Safe clamped addition. This will not underflow and always result in max/min possible
  * value in cases where the result cannot fit
  *
  * This results in `this + other` operation.
  */
  constexpr underlying_add_result_t add_clamp(base_type other) const
  {
    static_assert(underlying_enabled_add, "Addition with underlying type not supported");
    return underlying_add_result_t{ clamped_add(value, other.value) };
  }

  constexpr underlying_add_result_t operator-(base_type other) const
  {
    static_assert(underlying_enabled_add, "Substraction with underlying type not supported");
    return underlying_add_result_t(value - other.value);
  }

  /*
  * Safe clamped substraction. This will not underflow and always result in max/min possible
  * value in cases where the result cannot fit.
  *
  * This results in `this - other` operation.
  */
  constexpr underlying_add_result_t substract_clamp(base_type other) const
  {
    static_assert(underlying_enabled_add, "Substraction with underlying type not supported");
    return underlying_add_result_t{ clamped_substract(value, other.value) };
  }

  constexpr underlying_mult_result_t operator*(base_type other) const
  {
    static_assert(underlying_enabled_mult, "Multiplication with underlying type not supported");
    return underlying_mult_result_t(value * other.value);
  }

  constexpr underlying_mult_result_t operator/(base_type other) const
  {
    static_assert(underlying_enabled_mult, "Division with underlying type not supported");
    return underlying_mult_result_t(value / other.value);
  }
#pragma endregion
#pragma region static math helpers
  static constexpr WrapperType max_of(std::initializer_list<WrapperType> values)
  {
    WrapperType smallest{ std::numeric_limits<base_type>::min() };
    for (const auto& val : values)
    {
      if (val > smallest)
      {
        smallest = val;
      }
    }
    return smallest;
  }
  static constexpr WrapperType min_of(std::initializer_list<WrapperType> values)
  {
    WrapperType largest{ std::numeric_limits<base_type>::max() };
    for (const auto& val : values)
    {
      if (val < largest)
      {
        largest = val;
      }
    }
    return largest;
  }
#pragma endregion
#pragma region creation helpers
  static constexpr WrapperType max_value()
  { 
    return WrapperType{ max_base_value };
  };
  static constexpr WrapperType min_value()
  {
    return WrapperType{ min_base_value };
  };
  /*
  * Forces cast from any numeric type to this value. There are no checks what so ever.
  */
  template <typename TSource>
  static constexpr WrapperType forced_cast(TSource numericValue)
  {
    static_assert(std::is_arithmetic_v<TSource>, "forcedCast a numeric source type");
    return WrapperType{ static_cast<base_type>(numericValue) };
  }
#pragma endregion

#pragma region internal math helpers
private:
  static constexpr base_type clamped_add(base_type a, base_type b)
  {
    // overflow
    if (b > 0 && a > max_base_value - b)
    {
      return max_base_value;
    }
    // underflow
    else if (b < 0 && a < min_base_value - b)
    {
      return min_base_value;
    }
    else
    {
      return a + b;
    }
  }
  static constexpr base_type clamped_substract(base_type a, base_type b)
  {
    // overflow
    if (b < 0 && a > max_base_value + b)
    {
      return max_base_value;
    }
    // underflow
    else if (b > 0 && a < min_base_value + b)
    {
      return min_base_value;
    }
    else
    {
      return a - b;
    }
  }
#pragma endregion
};

//inline constexpr bool is_

}