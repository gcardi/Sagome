//---------------------------------------------------------------------------

#ifndef FrameModbusFunctionsH
#define FrameModbusFunctionsH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>

#include <cstdint>

#include "Utils.h"
#include "Modbus.h"

//---------------------------------------------------------------------------

class TfrmeModbusFunctions : public TFrame
{
__published:	// IDE-managed Components
    TPanel *Panel4;
    TPageControl *pgctrlFunctions;
    TTabSheet *tbshrFnReadHoldingRegisters;
    TLabel *Label3;
    TLabel *Label4;
    TButton *Button2;
    TEdit *edtReadHoldingRegistersAddr;
    TEdit *edtReadHoldingRegistersPtCnt;
    TTabSheet *tbshrFnReadInputRegisters;
    TLabel *Label12;
    TLabel *Label13;
    TButton *Button6;
    TEdit *edtReadInputRegistersAddr;
    TEdit *edtReadInputRegistersPtCnt;
    TTabSheet *tbshtFnPresetSingleRegister;
    TLabel *Label8;
    TLabel *Label9;
    TButton *Button3;
    TEdit *edtPresetSingleRegisterAddr;
    TEdit *edtPresetSingleRegisterValue;
    TTabSheet *tbshtFnPresetMultipleRegisters;
    TLabel *Label10;
    TLabel *Label11;
    TButton *Button5;
    TEdit *edtPresetMultipleRegistersAddr;
    TEdit *edtPresetMultipleRegistersData;
    TCheckBox *cboxPresetSingleRegisterPulsed;
    TEdit *edtPresetSingleRegisterPulseTime;
    TLabel *Label2;
    TCheckBox *cboxPresetMultipleRegisterPulsed;
    TEdit *edtPresetMultipleRegisterPulseTime;
    TLabel *Label1;
private:	// User declarations
    int GetFnIdx() const;
    void SetFnIdx( int Val );
    Modbus::RegAddrType GetReadHoldingRegistersAddr() const;
    void SetReadHoldingRegistersAddr( Modbus::RegAddrType Val );
    Modbus::RegCountType GetReadHoldingRegistersPtCnt() const;
    void SetReadHoldingRegistersPtCnt( Modbus::RegCountType Val );
    Modbus::RegAddrType GetReadInputRegistersAddr() const;
    void SetReadInputRegistersAddr( Modbus::RegAddrType Val );
    Modbus::RegCountType GetReadInputRegistersPtCnt() const;
    void SetReadInputRegistersPtCnt( Modbus::RegCountType Val );
    Modbus::RegAddrType GetPresetSingleRegisterAddr() const;
    void SetPresetSingleRegisterAddr( Modbus::RegAddrType Val );
    Modbus::RegDataType GetPresetSingleRegisterValue() const;
    void SetPresetSingleRegisterValue( Modbus::RegDataType Val );
    Modbus::RegAddrType GetPresetMultipleRegistersAddr() const;
    void SetPresetMultipleRegistersAddr( Modbus::RegAddrType Val );
    String GetPresetMultipleRegistersData() const;
    void SetPresetMultipleRegistersData( String Val );
    bool GetPresetSingleRegisterPulsed() const;
    void SetPresetSingleRegisterPulsed( bool Val );
    uint32_t GetPresetSingleRegisterPulseTime() const;
    void SetPresetSingleRegisterPulseTime( uint32_t Val );
    bool GetPresetMultipleRegisterPulsed() const;
    void SetPresetMultipleRegisterPulsed( bool Val );
    uint32_t GetPresetMultipleRegisterPulseTime() const;
    void SetPresetMultipleRegisterPulseTime( uint32_t Val );
public:		// User declarations
    __fastcall TfrmeModbusFunctions(TComponent* Owner);
    __property int FnIdx = { read = GetFnIdx, write = SetFnIdx };
    __property Modbus::RegAddrType ReadHoldingRegistersAddr = {
        read = GetReadHoldingRegistersAddr, write = SetReadHoldingRegistersAddr
    };
    __property Modbus::RegCountType ReadHoldingRegistersPtCnt = {
        read = GetReadHoldingRegistersPtCnt, write = SetReadHoldingRegistersPtCnt
    };
    __property Modbus::RegAddrType ReadInputRegistersAddr = {
        read = GetReadInputRegistersAddr, write = SetReadInputRegistersAddr
    };
    __property Modbus::RegCountType ReadInputRegistersPtCnt = {
        read = GetReadInputRegistersPtCnt, write = SetReadInputRegistersPtCnt
    };
    __property Modbus::RegAddrType PresetSingleRegisterAddr = {
        read = GetPresetSingleRegisterAddr, write = SetPresetSingleRegisterAddr
    };
    __property Modbus::RegDataType PresetSingleRegisterValue = {
        read = GetPresetSingleRegisterValue, write = SetPresetSingleRegisterValue
    };
    __property Modbus::RegAddrType PresetMultipleRegistersAddr = {
        read = GetPresetMultipleRegistersAddr, write = SetPresetMultipleRegistersAddr
    };
    __property String PresetMultipleRegistersData = {
        read = GetPresetMultipleRegistersData, write = SetPresetMultipleRegistersData
    };
    __property bool PresetSingleRegisterPulsed = {
        read = GetPresetSingleRegisterPulsed, write = SetPresetSingleRegisterPulsed
    };
    __property uint32_t PresetSingleRegisterPulseTime = {
        read = GetPresetSingleRegisterPulseTime,
        write = SetPresetSingleRegisterPulseTime
    };
    __property bool PresetMultipleRegisterPulsed = {
        read = GetPresetMultipleRegisterPulsed, write = SetPresetMultipleRegisterPulsed
    };
    __property uint32_t PresetMultipleRegisterPulseTime = {
        read = GetPresetMultipleRegisterPulseTime,
        write = SetPresetMultipleRegisterPulseTime
    };

    template<typename OutIt>
    void CopyPresetMultipleRegistersData( OutIt It );
};
//---------------------------------------------------------------------------

template<typename OutIt>
void TfrmeModbusFunctions::CopyPresetMultipleRegistersData( OutIt It )
{
    StringToSaturatedWords( PresetMultipleRegistersData, It );
}

//---------------------------------------------------------------------------
//extern PACKAGE TfrmeModbusFunctions *frmeModbusFunctions;
//---------------------------------------------------------------------------
#endif
