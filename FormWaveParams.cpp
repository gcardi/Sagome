//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <algorithm>

#include "FormWaveParams.h"

using std::min;
using std::max;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfrmWaveParameters *frmWaveParameters;
//---------------------------------------------------------------------------

__fastcall TfrmWaveParameters::TfrmWaveParameters(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmWaveParameters::actOKExecute(TObject *Sender)
{
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWaveParameters::actOKUpdate(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = IsPeakDetMinDurationValid() && IsPeakDetConfidenceValid() &&
                  IsPeakMinDetectionTimeDistanceValid();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWaveParameters::actCancelExecute(TObject *Sender)
{
    ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

bool TfrmWaveParameters::IsPeakDetMinDurationValid() const
{
    auto Val = edtPeakDetMinDuration->Text.ToIntDef( -1 );
    return Val >= 20 && Val <= 500;
}
//---------------------------------------------------------------------------

bool TfrmWaveParameters::IsPeakDetConfidenceValid() const
{
    auto Val = edtPeakDetConf->Text.ToIntDef( -1 );
    return Val >= 10 && Val <= 100;
}
//---------------------------------------------------------------------------

bool TfrmWaveParameters::IsPeakMinDetectionTimeDistanceValid() const
{
    auto Val = edtPeakDetMinDuration->Text.ToIntDef( -1 );
    return Val >= 0 && Val <= 10000;
}
//---------------------------------------------------------------------------

int TfrmWaveParameters::GetPeakDetectionMinDuration() const
{
    return min( max( edtPeakDetMinDuration->Text.ToIntDef( 70 ), 20 ), 500 );
}
//---------------------------------------------------------------------------

void TfrmWaveParameters::SetPeakDetectionMinDuration( int Val )
{
    edtPeakDetMinDuration->Text = Val;
}
//---------------------------------------------------------------------------

int TfrmWaveParameters::GetPeakDetectionConfidence() const
{
    return min( max( edtPeakDetConf->Text.ToIntDef( 80 ), 10 ), 100 );
}
//---------------------------------------------------------------------------

void TfrmWaveParameters::SetPeakDetectionConfidence( int Val )
{
    edtPeakDetConf->Text = Val;
}
//---------------------------------------------------------------------------

int TfrmWaveParameters::GetPeakMinDetectionTimeDistance() const
{
    return min( max( edtPeakDMinDetectionTimeDistance->Text.ToIntDef( 70 ), 0 ), 10000 );
}
//---------------------------------------------------------------------------

void TfrmWaveParameters::SetPeakMinDetectionTimeDistance( int Val )
{
    edtPeakDMinDetectionTimeDistance->Text = Val;
}
//---------------------------------------------------------------------------


