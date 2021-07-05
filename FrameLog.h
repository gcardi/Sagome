//---------------------------------------------------------------------------

#ifndef FrameLogH
#define FrameLogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmeLog : public TFrame
{
__published:	// IDE-managed Components
    TRichEdit *RichEdit1;
    TPanel *Panel2;
    TSpeedButton *SpeedButton1;
    void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmeLog(TComponent* Owner);
    void LogMessage( String Text, TColor Color );

};
//---------------------------------------------------------------------------
//extern PACKAGE TFrame1 *Frame1;
//---------------------------------------------------------------------------
#endif
