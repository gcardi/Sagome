//---------------------------------------------------------------------------

#ifndef FrameSerialSettingsH
#define FrameSerialSettingsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------

class TfrmeSerialSettings : public TFrame
{
__published:	// IDE-managed Components
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TComboBox *cmboxSpeed;
    TComboBox *cmboxParity;
    TComboBox *cmboxStopBits;
    TComboBox *cmboxDataBits;
    TCheckBox *checkboxCancelTXEcho;
    TComboBox *cmboxPortName;
    TLabel *Label1;
private:	// User declarations
    String GetPortName() const;
    void SetPortName( String Val );
    TStrings& GetPortNameList() const;
    void SetPortNameList( TStrings& Val );
    int GetSpeed() const;
    void SetSpeed( int Value );
    int GetParity() const;
    void SetParity( int Value );
    int GetBits() const;
    void SetBits( int Value );
    int GetStopBits() const;
    void SetStopBits( int Value );
    bool GetCancelTXEcho() const;
    void SetCancelTXEcho( bool Val );
public:		// User declarations
    __fastcall TfrmeSerialSettings(TComponent* Owner);
    bool CheckParsValidity() const;
    __property String PortName = { read = GetPortName, write = SetPortName };
    __property TStrings& PortNameList = { read = GetPortNameList, write = SetPortNameList };
    __property int Speed = { read = GetSpeed, write = SetSpeed };
    __property int Parity = { read = GetParity, write = SetParity };
    __property int Bits = { read = GetBits, write = SetBits };
    __property int StopBits = { read = GetStopBits, write = SetStopBits };
    __property bool CancelTXEcho = { read = GetCancelTXEcho, write = SetCancelTXEcho };
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmeSerialSettings *frmeSerialSettings;
//---------------------------------------------------------------------------
#endif
