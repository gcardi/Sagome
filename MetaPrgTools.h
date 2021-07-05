#ifndef METAPROGTOOLS_H
#define METAPROGTOOLS_H

//---------------------------------------------------------------------------
namespace SvcApp {
//---------------------------------------------------------------------------

// generate a sequence of integers as non-type template arguments
template<size_t... Is> struct seq {};
template<size_t N, size_t... Is> struct gen_seq : gen_seq<N-1, N-1, Is...> {};
template<size_t... Is> struct gen_seq<0, Is...> : seq<Is...> {};

//---------------------------------------------------------------------------
} // End of namespace SvcApp
//---------------------------------------------------------------------------
#endif
