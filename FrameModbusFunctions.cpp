//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <algorithm>

#include "Utils.h"
#include "FrameModbusFunctions.h"

using std::min;
using std::max;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfrmeModbusFunctions *frmeModbusFunctions;
//---------------------------------------------------------------------------

__fastcall TfrmeModbusFunctions::TfrmeModbusFunctions(TComponent* Owner)
    : TFrame(Owner)
{
}
//---------------------------------------------------------------------------

int TfrmeModbusFunctions::GetFnIdx() const
{
    return pgctrlFunctions->TabIndex;
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetFnIdx( int Val )
{
    pgctrlFunctions->TabIndex =
        max( 0, min( pgctrlFunctions->PageCount - 1, Val ) );
}
//---------------------------------------------------------------------------

Modbus::RegAddrType TfrmeModbusFunctions::GetReadHoldingRegistersAddr() const
{
    return ParseWord( edtReadHoldingRegistersAddr->Text );
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetReadHoldingRegistersAddr( Modbus::RegAddrType Val )
{
    edtReadHoldingRegistersAddr->Text = Val;
}
//---------------------------------------------------------------------------

Modbus::RegCountType TfrmeModbusFunctions::GetReadHoldingRegistersPtCnt() const
{
    return ParseWord( edtReadHoldingRegistersPtCnt->Text );
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetReadHoldingRegistersPtCnt( Modbus::RegCountType Val )
{
    edtReadHoldingRegistersPtCnt->Text = Val;
}
//---------------------------------------------------------------------------

Modbus::RegAddrType TfrmeModbusFunctions::GetReadInputRegistersAddr() const
{
    return ParseWord( edtReadInputRegistersAddr->Text );
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetReadInputRegistersAddr( Modbus::RegAddrType Val )
{
    edtReadInputRegistersAddr->Text = Val;
}
//---------------------------------------------------------------------------

Modbus::RegCountType TfrmeModbusFunctions::GetReadInputRegistersPtCnt() const
{
    return ParseWord( edtReadInputRegistersPtCnt->Text );
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetReadInputRegistersPtCnt( Modbus::RegCountType Val )
{
    edtReadInputRegistersPtCnt->Text = Val;
}
//---------------------------------------------------------------------------

Modbus::RegAddrType TfrmeModbusFunctions::GetPresetSingleRegisterAddr() const
{
    return ParseWord( edtPresetSingleRegisterAddr->Text );
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetPresetSingleRegisterAddr( Modbus::RegAddrType Val )
{
    edtPresetSingleRegisterAddr->Text = Val;
}
//---------------------------------------------------------------------------

Modbus::RegDataType TfrmeModbusFunctions::GetPresetSingleRegisterValue() const
{
    return ParseWord( edtPresetSingleRegisterValue->Text );
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetPresetSingleRegisterValue( Modbus::RegDataType Val )
{
    edtPresetSingleRegisterValue->Text = Val;
}
//---------------------------------------------------------------------------

Modbus::RegAddrType TfrmeModbusFunctions::GetPresetMultipleRegistersAddr() const
{
    return ParseWord( edtPresetMultipleRegistersAddr->Text );
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetPresetMultipleRegistersAddr( Modbus::RegAddrType Val )
{
    edtPresetMultipleRegistersAddr->Text = Val;
}
//---------------------------------------------------------------------------

String TfrmeModbusFunctions::GetPresetMultipleRegistersData() const
{
    return Trim( edtPresetMultipleRegistersData->Text );
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetPresetMultipleRegistersData( String Val )
{
    edtPresetMultipleRegistersData->Text = Trim( Val );
}
//---------------------------------------------------------------------------

bool TfrmeModbusFunctions::GetPresetSingleRegisterPulsed() const
{
    return cboxPresetSingleRegisterPulsed->Checked;
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetPresetSingleRegisterPulsed( bool Val )
{
    cboxPresetSingleRegisterPulsed->Checked = Val;
}
//---------------------------------------------------------------------------

uint32_t TfrmeModbusFunctions::GetPresetSingleRegisterPulseTime() const
{
    return
        max( edtPresetSingleRegisterPulseTime->Text.ToIntDef( 1000 ), 0 );
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetPresetSingleRegisterPulseTime( uint32_t Val )
{
    edtPresetSingleRegisterPulseTime->Text = Val;
}
//---------------------------------------------------------------------------

bool TfrmeModbusFunctions::GetPresetMultipleRegisterPulsed() const
{
    return cboxPresetMultipleRegisterPulsed->Checked;
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetPresetMultipleRegisterPulsed( bool Val )
{
    cboxPresetMultipleRegisterPulsed->Checked = Val;
}
//---------------------------------------------------------------------------

uint32_t TfrmeModbusFunctions::GetPresetMultipleRegisterPulseTime() const
{
    return
        max( edtPresetMultipleRegisterPulseTime->Text.ToIntDef( 1000 ), 0 );
}
//---------------------------------------------------------------------------

void TfrmeModbusFunctions::SetPresetMultipleRegisterPulseTime( uint32_t Val )
{
    edtPresetMultipleRegisterPulseTime->Text = Val;
}
//---------------------------------------------------------------------------

