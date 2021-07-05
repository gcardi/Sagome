//---------------------------------------------------------------------------

#ifndef FormWaveParamsH
#define FormWaveParamsH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>

//---------------------------------------------------------------------------

class TfrmWaveParameters : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label15;
    TEdit *edtPeakDetConf;
    TLabel *Label14;
    TEdit *edtPeakDetMinDuration;
    TActionList *ActionList1;
    TAction *actOK;
    TAction *actCancel;
    TButton *Button1;
    TButton *Button2;
    TEdit *edtPeakDMinDetectionTimeDistance;
    TLabel *Label1;
    void __fastcall actOKExecute(TObject *Sender);
    void __fastcall actOKUpdate(TObject *Sender);
    void __fastcall actCancelExecute(TObject *Sender);
private:	// User declarations
    bool IsPeakDetMinDurationValid() const;
    bool IsPeakDetConfidenceValid() const;
    bool IsPeakMinDetectionTimeDistanceValid() const;
    int GetPeakDetectionMinDuration() const;
    void SetPeakDetectionMinDuration( int Val );
    int GetPeakDetectionConfidence() const;
    void SetPeakDetectionConfidence( int Val );
    int GetPeakMinDetectionTimeDistance() const;
    void SetPeakMinDetectionTimeDistance( int Val );
public:		// User declarations
    __fastcall TfrmWaveParameters(TComponent* Owner);
    __property int PeakDetectionMinDuration = {
        read = GetPeakDetectionMinDuration, write = SetPeakDetectionMinDuration
    };
    __property int PeakDetectionConfidence = {
        read = GetPeakDetectionConfidence, write = SetPeakDetectionConfidence
    };
    __property int PeakMinDetectionTimeDistance = {
        read = GetPeakMinDetectionTimeDistance,
        write = SetPeakMinDetectionTimeDistance
    };
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmWaveParameters *frmWaveParameters;
//---------------------------------------------------------------------------
#endif
