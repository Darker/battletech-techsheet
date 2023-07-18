#pragma once
template <typename base_iterator, template predicate>
struct filtered_iterator : BaseIterator
{
  filtered_iterator() = default;
  filtered_iterator(filter_type filter, base_iterator base, base_iterator end = {})
    : BaseIterator(base), _end(end), _filter(filter_type)
  {
    while (*this != _end && !_filter(**this))
    {
      ++* this;
    }
  }

  filtered_iterator& operator++()
  {
    do
    {
      BaseIterator::operator++();
    } while (*this != _end && !_filter(**this));
  }

  filtered_iterator operator++(int)
  {
    filtered_iterator copy = *this;
    ++* this;
    return copy;
  }

private:
  BaseIterator _end;
  filter_type _filter;
};

template <typename BaseIterator>
filtered_iterator<BaseIterator> make_filtered_iterator(
  typename filtered_iterator<BaseIterator>::filter_type filter,
  BaseIterator base, BaseIterator end = {})
{
  return { filter, base, end };
}