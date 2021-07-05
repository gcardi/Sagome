//---------------------------------------------------------------------------

#ifndef FrameProtocolSettingsH
#define FrameProtocolSettingsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "FrameSerialSettings.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------

class TfrmeProtocolSettings : public TFrame
{
__published:	// IDE-managed Components
    TCheckBox *cboxAutoIncTransactionID;
    TComboBox *comboboxProtocol;
    TEdit *edtSlaveId;
    TEdit *edtTransactionID;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TPageControl *pgctrlProtocolSettings;
    TTabSheet *tbshtProtocolSerialSettings;
    TfrmeSerialSettings *frmeSerialSettings1;
    TTabSheet *tbshtProtocolTCPIPSettings;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *edtTCPIPHost;
    TEdit *edtTCPIPPort;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmeProtocolSettings(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmeProtocolSettings *frmeProtocolSettings;
//---------------------------------------------------------------------------
#endif
