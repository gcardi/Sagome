//---------------------------------------------------------------------------

#ifndef UtilsH
#define UtilsH

#include <System.hpp>
#include <System.SysUtils.hpp>

#include <cstdint>
#include <memory>
#include <algorithm>

#include "RegexDefs.h"

//---------------------------------------------------------------------------

extern uint16_t ParseWord( String Text );

//---------------------------------------------------------------------------

template<typename C>
String WordsToString( C Data )
{
    auto SB = std::make_unique<TStringBuilder>();
    size_t n {};
    for ( auto const & di : Data ) {
        SB->AppendFormat(
            n++ ? _T( ", %d" ) : _T( "%d" ), ARRAYOFCONST( ( di ) )
        );
    }
    return SB->ToString();
}
//---------------------------------------------------------------------------

#if !defined( USE_STD_REGEX )
  #if !defined(_UNICODE)
    using cregex_iterator_type = boost::cregex_iterator;
  #else
    using cregex_iterator_type = boost::wcregex_iterator;
  #endif
#else
  #if !defined(_UNICODE)
    using cregex_iterator_type = std::cregex_iterator;
  #else
    using cregex_iterator_type = std::wcregex_iterator;
  #endif
#endif

template<typename OutIt>
int StringToSaturatedWords( String Text, OutIt Out )
{
    int Cnt = 0;
    regex_type re( _T( "(-?\\d+)[^\\d]\?" ) );
    regex_cmatch_type m;
    cregex_iterator_type m1( Text.c_str(), Text.c_str() + Text.Length(), re );
    cregex_iterator_type m2;
    for ( ; m1 != m2 ; m1++ ) {
        int const Id =
            std::min(
                std::max( String( (*m1)[1].str().c_str() ).ToInt(), 0 ),
                65535
            );
        *Out++ = Id;
        if ( Id ) {
            ++Cnt;
        }
    }
    return Cnt;
}

//---------------------------------------------------------------------------
#endif
