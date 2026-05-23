//---------------------------------------------------------------------------

#pragma hdrstop

#include <System.Math.hpp>
#include <Vcl.Themes.hpp>

#include <algorithm>
#include <cmath>

#include "Utils.h"

using std::min;
using std::max;

//---------------------------------------------------------------------------
#pragma package(smart_init)

String GetActiveStyleName()
{
    if ( TStyleManager::ActiveStyle ) {
        return TStyleManager::ActiveStyle->Name;
    }
    return {};
}
//---------------------------------------------------------------------------

uint16_t ParseWord( String Text )
{
    return min( 65535, max( 0, Text.ToInt() ) );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


