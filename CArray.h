#ifndef CARRAY_H
#define CARRAY_H

#include "MetaPrgTools.h"

//---------------------------------------------------------------------------
namespace SvcApp {
//---------------------------------------------------------------------------

// an array type that can be returned from a function
// and has `constexpr` accessors (as opposed to C++11's `std::array`)
template<typename T, size_t N>
struct c_array
{
    using value_type = T;
    using iterator_type = value_type const *;
    using size_type = size_t;
    using reference_type = value_type const &;

    T m_[N];

    constexpr reference_type operator[]( size_type p ) const {  return m_[p];  }
    constexpr iterator_type begin() const { return m_; }
    constexpr iterator_type end() const { return m_ + N; }
    static constexpr size_type size() noexcept { return N; }
};

// return the index of the smallest element (using Op for comparisons)
template<typename Op, typename T, size_t Size>
constexpr size_t c_min_index( c_array<T,Size> const & a, size_t ofs, size_t cur )
{
    return
        Size == ofs ?
          cur
        :
          c_min_index<Op>( a, ofs + 1, Op( a[cur], a[ofs] ) ? cur : ofs );
}

// return the index of the smallest element (using T's less than operator)
template<typename T, size_t Size>
constexpr size_t c_min_index( c_array<T,Size> const & a, size_t ofs, size_t cur )
{
    return
        Size == ofs ?
          cur
        :
          c_min_index( a, ofs + 1, a[cur] < a[ofs] ? cur : ofs );
}

// copy the c_array but with the elements at `index0` and `index1` swapped
template<typename T, size_t Size, size_t... Is>
constexpr c_array<T,Size> c_swap( c_array<T,Size> const & a, size_t idx0,
                                  size_t idx1, seq<Is...> )
{
    return { { a[Is == idx0 ? idx1 : Is == idx1 ? idx0 : Is]... } };
}

// the c_array's selection sort algorithm (using Op for comparisons)
template<typename Op, typename T, size_t Size>
constexpr c_array<T,Size> c_sel_sort( c_array<T,Size> const & a, size_t cur = 0 )
{
    return
        Size == cur ?
          a
        :
          c_sel_sort<Op>(
              c_swap( a, cur, c_min_index<Op>( a, cur, cur ), gen_seq<Size>{} ),
              cur + 1
          );
}

// the c_array's selection sort algorithm (using T's less than operator)
template<typename T, size_t Size>
constexpr c_array<T,Size> c_sel_sort( c_array<T,Size> const & a, size_t cur = 0 )
{
    return
        Size == cur ?
          a
        :
          c_sel_sort(
              c_swap( a, cur, c_min_index( a, cur, cur ), gen_seq<Size>{} ),
              cur + 1
          );
}








//---------------------------------------------------------------------------
} // End of namespace SvcApp
//---------------------------------------------------------------------------
#endif
