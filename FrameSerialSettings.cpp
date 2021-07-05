//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <algorithm>

#include "FrameSerialSettings.h"

using std::lower_bound;
using std::min;
using std::max;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfrmeSerialSettings *frmeSerialSettings;
//---------------------------------------------------------------------------

__fastcall TfrmeSerialSettings::TfrmeSerialSettings(TComponent* Owner)
    : TFrame(Owner)
{
}
//---------------------------------------------------------------------------

bool TfrmeSerialSettings::CheckParsValidity() const
{
    // https://msdn.microsoft.com/en-us/library/windows/desktop/aa363214(v=vs.85).aspx
    // o The number of data bits must be 5 to 8 bits.
    // o The use of 5 data bits with 2 stop bits is an invalid combination,
    //   as is 6, 7, or 8 data bits with 1.5 stop bits.
    return cmboxDataBits->ItemIndex >= 0 &&
           ( Bits != 5 || StopBits != TWOSTOPBITS ) &&
           ( Bits <= 5 || StopBits != ONE5STOPBITS );
}
//---------------------------------------------------------------------------

static DWORD const BaudRate[] = {
      CBR_110
    , CBR_300
    , CBR_600
    , CBR_1200
    , CBR_2400
    , CBR_4800
    , CBR_9600
    , CBR_14400
    , CBR_19200
    , CBR_38400
    , CBR_57600
    , CBR_115200
    , CBR_128000
    , CBR_256000
};

String TfrmeSerialSettings::GetPortName() const
{
    return Trim( cmboxPortName->Text );
}
//---------------------------------------------------------------------------

void TfrmeSerialSettings::SetPortName( String Val )
{
    cmboxPortName->Text = Trim( Val );
}
//---------------------------------------------------------------------------

TStrings& TfrmeSerialSettings::GetPortNameList() const
{
    return *cmboxPortName->Items;
}
//---------------------------------------------------------------------------

void TfrmeSerialSettings::SetPortNameList( TStrings& Val )
{
    cmboxPortName->Items->Assign( &Val );
}
//---------------------------------------------------------------------------

int TfrmeSerialSettings::GetSpeed() const
{
    int const Idx = cmboxSpeed->ItemIndex;
    if ( Idx >= 0 && Idx < static_cast<int>( sizeof BaudRate / sizeof *BaudRate ) ) {
        return BaudRate[Idx];
    }
    return CBR_115200;
}
//---------------------------------------------------------------------------

void TfrmeSerialSettings::SetSpeed( int Value )
{
    DWORD const * Begin = BaudRate;
    DWORD const * End = BaudRate + sizeof BaudRate / sizeof *BaudRate;
    DWORD const * Ptr = lower_bound( Begin, End, Value );
    cmboxSpeed->ItemIndex = Ptr == End ? -1 : Ptr - Begin;
}
//---------------------------------------------------------------------------

int TfrmeSerialSettings::GetParity() const
{
    int const Idx = cmboxParity->ItemIndex;
    return Idx >= 0 ? Idx : NOPARITY;
}
//---------------------------------------------------------------------------

void TfrmeSerialSettings::SetParity( int Value )
{
    cmboxParity->ItemIndex =
        min( max( Value, 0 ), cmboxParity->Items->Count - 1 );
}
//---------------------------------------------------------------------------

int TfrmeSerialSettings::GetBits() const
{
    int const Idx = cmboxDataBits->ItemIndex;
    return Idx >= 0 ? Idx + 5 : 8;
}
//---------------------------------------------------------------------------

void TfrmeSerialSettings::SetBits( int Value )
{
    cmboxDataBits->ItemIndex =
        min( max( Value - 5, 0 ), cmboxDataBits->Items->Count - 1 );
}
//---------------------------------------------------------------------------

int TfrmeSerialSettings::GetStopBits() const
{
    int const Idx = cmboxStopBits->ItemIndex;
    return Idx >= 0 ? Idx : ONESTOPBIT;
}
//---------------------------------------------------------------------------

void TfrmeSerialSettings::SetStopBits( int Value )
{
    cmboxStopBits->ItemIndex =
        min( max( Value, 0 ), cmboxStopBits->Items->Count - 1 );
}
//---------------------------------------------------------------------------

bool TfrmeSerialSettings::GetCancelTXEcho() const
{
    return checkboxCancelTXEcho->Checked;
}
//---------------------------------------------------------------------------

void TfrmeSerialSettings::SetCancelTXEcho( bool Val )
{
    checkboxCancelTXEcho->Checked = Val;
}
//---------------------------------------------------------------------------


