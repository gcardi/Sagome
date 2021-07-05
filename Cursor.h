//---------------------------------------------------------------------------

#ifndef CursorH
#define CursorH

#include <boost/utility.hpp>

class TCursorManager : boost::noncopyable
{
private:
    TCursor oldCursor_;
    bool restored_;
public:
    __fastcall TCursorManager( TCursor Cursor = crHourGlass );
    __fastcall ~TCursorManager() throw();
    TCursor __fastcall Set( TCursor Cursor );
    void __fastcall Restore();
};
//---------------------------------------------------------------------------
#endif
