//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Cursor.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

TCursorManager::TCursorManager( TCursor Cursor )
    : restored_( false ), oldCursor_( Set( Cursor ) )
{
}
//---------------------------------------------------------------------------

TCursorManager::~TCursorManager()
{
    try {
        if ( !restored_ )
            Restore();
    }
    catch ( ... ) {
    }
}
//---------------------------------------------------------------------------

TCursor TCursorManager::Set( TCursor Cursor )
{
    TCursor const CurrentCursor( Screen->Cursor );
    Screen->Cursor = Cursor;
    restored_ = false;
    return CurrentCursor;
}
//---------------------------------------------------------------------------

void TCursorManager::Restore()
{
    Screen->Cursor = oldCursor_;
    restored_ = false;
}
//---------------------------------------------------------------------------

