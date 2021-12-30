//---------------------------------------------------------------------------

#ifndef CursorH
#define CursorH

class TCursorManager
{
public:
    explicit TCursorManager( TCursor Cursor = crHourGlass );
    ~TCursorManager();
    TCursorManager( TCursorManager const & ) = delete;
    TCursorManager& operator=( TCursorManager const & ) = delete;
    TCursor __fastcall Set( TCursor Cursor );
    void __fastcall Restore();
private:
    TCursor oldCursor_;
    bool restored_;
};
//---------------------------------------------------------------------------
#endif
