//---------------------------------------------------------------------------

#ifndef CursorH
#define CursorH


class TCursorManager
{
private:
    TCursor oldCursor_;
    bool restored_;
public:
    TCursorManager( TCursor Cursor = crHourGlass );
    TCursorManager( TCursorManager const & ) = delete;
    TCursorManager& operator=( TCursorManager const & ) = delete;
    ~TCursorManager() throw();
    TCursor __fastcall Set( TCursor Cursor );
    void __fastcall Restore();
};
//---------------------------------------------------------------------------
#endif
