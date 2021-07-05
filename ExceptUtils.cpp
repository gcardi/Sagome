//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <System.hpp>

#include "ExceptUtils.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

String FormatExceptionErrorMessage( System::TObject* ExceptObject, void * ExceptAddr )
{
    WideChar Buffer[4096];

    int const Len =
        ExceptionErrorMessage(
            ExceptObject, ExceptAddr,
            Buffer, sizeof Buffer / sizeof *Buffer - 1
        );
    return String( Buffer, Len );
}
//---------------------------------------------------------------------------

