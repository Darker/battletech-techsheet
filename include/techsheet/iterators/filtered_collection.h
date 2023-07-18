#pragma once
#include <array>
#include <type_traits>

#include "../template_defs.h"

namespace techsheet
{

struct unused_filtering_param {};

template <typename TCollection, typename TPredicateParam = unused_filtering_param>
struct filtered_collection
{
  using collection_t_base = std::remove_reference_t<std::remove_const_t<TCollection>>;
  using collection_t_q = std::remove_reference_t<TCollection>;
  static constexpr bool collection_is_const = std::is_const_v<collection_t_q>;

  using inner_iterator = decltype(collection_t_q{}.begin());
  using const_inner_iterator = decltype(collection_t_q{}.cbegin());
  using value_type = std::remove_reference_t<decltype(inner_iterator{}.operator*())>;

  static constexpr bool no_predicate_param = std::is_same_v<TPredicateParam, unused_filtering_param>;
  using filter_predicate_no_param = bool (*)(const value_type&);
  using filter_predicate_param = bool (*)(const value_type&, const TPredicateParam&);
  using filter_predicate = std::conditional_t<no_predicate_param, filter_predicate_no_param, filter_predicate_param>;
  static constexpr auto max_predicates = 4;
  using predicates = std::array<filter_predicate, max_predicates>;

  template<typename = std::enable_if_t<no_predicate_param>>
  filtered_collection(
    collection_t_q& collection,
    filter_predicate f1, 
    filter_predicate f2 = nullptr, 
    filter_predicate f3 = nullptr,
    filter_predicate f4 = nullptr
  )
    : collection{ collection }
    , filters{f1, f2, f3, f4}
  { }

  template<typename = std::enable_if_t<!no_predicate_param>>
  filtered_collection(
    collection_t_q& collection,
    TPredicateParam param,
    filter_predicate f1,
    filter_predicate f2 = nullptr,
    filter_predicate f3 = nullptr,
    filter_predicate f4 = nullptr
  )
    : collection{ collection }
    , filters{ f1, f2, f3, f4 }
    , param{ param }
  {}

  //filtered_collection(TCollection& collection, predicates&& filters)
  //  : collection{ collection }
  //{}

  template<bool is_const_iterator_v = true>
  class iterator_impl
  {
  public:
    static constexpr bool is_const_iterator = is_const_iterator_v;
    //! Decides between const or non const value
    using iterator_spec = typename std::conditional<is_const_iterator, const_inner_iterator, inner_iterator>::type;
    using value_type_spec = decltype(iterator_spec{}.operator*());

    //! Create iterator starting at index
    iterator_impl(iterator_spec it, iterator_spec end, const filtered_collection& parent)
      : index{ it }
      , end{ end }
      , parent{ parent }
    {
      if(it != end)
        find_valid();
    }

    //! Move the iterator one step
    iterator_impl& operator++() noexcept { ++index; find_valid(); return *this; }
    //! Returns true if the current iterator index is the same as the other one
    bool operator==(const iterator_impl& other) const { return index == other.index; }
    //! Returns negative of operator==
    bool operator!=(const iterator_impl& other) const { return !(other == *this); }
    //! Provides refference to the current value
    value_type_spec operator*() const { return *index; }

  private:
    //! Current iterator index
    iterator_spec index;
    iterator_spec end;
    const filtered_collection& parent;

    void find_valid() 
    {
      while (index != end)
      {
        bool passed = true;
        for (const auto& pred : parent.filters)
        {
          if (pred == nullptr)
          {
            break;
          }
          else if (!exec_predicate(pred))
          {
            passed = false;
            ++index;
            break;
          }
        }
        if (passed)
        {
          break;
        }
      }
    }

    bool exec_predicate(filter_predicate pred) const
    {
      if constexpr (no_predicate_param)
      {
        return pred(*index);
      }
      else
      {
        return pred(*index, parent.param);
      }
    }
  };

  using iterator = iterator_impl<false>;
  using const_iterator = iterator_impl<true>;

  template<typename = std::enable_if_t<!collection_is_const>>
  iterator begin() { return iterator(collection.begin(), collection.end(), *this); }
  template<typename = std::enable_if_t<!collection_is_const>>
  iterator end() { return iterator(collection.end(), collection.end(), *this); }

  template<typename = std::enable_if_t<collection_is_const>>
  const_iterator begin() const { return const_iterator(collection.cbegin(), collection.cend(), *this); }
  template<typename = std::enable_if_t<collection_is_const>>
  const_iterator end() const { return const_iterator(collection.cend(), collection.cend(), *this); }

  const_iterator cbegin() { return const_iterator(collection.cbegin(), collection.cend(), *this); }
  const_iterator cend() { return const_iterator(collection.cend(), collection.cend(), *this); }

private:
  collection_t_q& collection;
  predicates filters{};
  TPredicateParam param{};
};

static_assert(filtered_collection<std::array<int, 4>, unused_filtering_param>::no_predicate_param);
static_assert(!filtered_collection<std::array<int, 4>, int>::no_predicate_param);

template <typename TCollection>
auto make_filtered(TCollection&& collection, 
  typename filtered_collection<TCollection>::filter_predicate f1,
  typename filtered_collection<TCollection>::filter_predicate f2 = nullptr,
  typename filtered_collection<TCollection>::filter_predicate f3 = nullptr,
  typename filtered_collection<TCollection>::filter_predicate f4 = nullptr
)
{
  return filtered_collection<TCollection>(collection, f1, f2, f3, f4);
}

template <typename TCollection, typename TParam>
auto make_filtered(TCollection&& collection,
  TParam param,
  typename filtered_collection<TCollection, TParam>::filter_predicate f1,
  typename filtered_collection<TCollection, TParam>::filter_predicate f2 = nullptr,
  typename filtered_collection<TCollection, TParam>::filter_predicate f3 = nullptr,
  typename filtered_collection<TCollection, TParam>::filter_predicate f4 = nullptr
)
{
  return filtered_collection<TCollection, TParam>(collection, param, f1, f2, f3, f4);
}

}
