//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrameLog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TFrame1 *Frame1;
//---------------------------------------------------------------------------

__fastcall TfrmeLog::TfrmeLog(TComponent* Owner)
    : TFrame(Owner)
{
}
//---------------------------------------------------------------------------

void TfrmeLog::LogMessage( String Text, TColor Color )
{
    RichEdit1->SetFocus();
    RichEdit1->SelStart = RichEdit1->GetTextLen();
    RichEdit1->SelAttributes->Color = Color;
    RichEdit1->SelText = Text;
    RichEdit1->Perform( EM_SCROLLCARET, 0, static_cast<NativeInt>( 0 ) );
}
//---------------------------------------------------------------------------

void __fastcall TfrmeLog::SpeedButton1Click(TObject *Sender)
{
    RichEdit1->Clear();
}
//---------------------------------------------------------------------------

