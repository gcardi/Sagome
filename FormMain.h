//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.WinXCtrls.hpp>

#include "FrameSerialSettings.h"
#include "FrameLog.h"
#include "FrameModbusFunctions.h"
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Dialogs.hpp>

#include <memory>
#include <cstdint>
#include <array>
#include <future>
#include <atomic>

#include <anafestica/PersistFormVCL.h>
#include <anafestica/CfgRegistrySingleton.h>

#include "fftw3.h"

#include "WaveIn.h"
#include "Modbus.h"
#include "GdiPlusUtils.h"
#include "CArray.h"

//---------------------------------------------------------------------------

using TConfigRegistryForm =
	Anafestica::TPersistFormVCL<Anafestica::Registry::TConfigSingleton>;

//---------------------------------------------------------------------------

template<size_t SIZE, typename T = fftw_complex>
class FFTWCont {
public:
    using ValueType = T;
    static size_t get_length() { return SIZE; }
    FFTWCont() : buffer_( (T*)fftw_malloc( sizeof( T ) * SIZE ) ) {}
    ~FFTWCont() { if ( buffer_ ) { fftw_free( buffer_ ); } }
    operator T*() const { return buffer_; }
    FFTWCont( FFTWCont const & Rhs )
      : buffer_( (T*)fftw_malloc( sizeof( T ) * SIZE ) )
    {
        memcpy( buffer_, Rhs.buffer_, SIZE * sizeof( T ) );
    }
    FFTWCont( FFTWCont&& Rhs )
      : buffer_( Rhs.buffer_ )
    {
        Rhs.buffer_ = nullptr;
    }
    FFTWCont& operator=( FFTWCont const & Rhs ) {
        memcpy( buffer_, Rhs.buffer_, SIZE * sizeof( T ) );
        return *this;
    }
    FFTWCont& operator=( FFTWCont&& Rhs ) {
        buffer_ = Rhs.buffer_;
        Rhs.buffer_ = nullptr;
        return *this;
    }
private:
    T* buffer_ { nullptr };
};

template<typename C>
class FFTWPlan {
public:
    FFTWPlan( C& In, C& Out )
      : p_( fftw_plan_dft_1d( C::get_length(), In, Out, FFTW_FORWARD, FFTW_ESTIMATE ) ) {}
    ~FFTWPlan() { fftw_destroy_plan( p_ ); }
    operator fftw_plan() const { return p_; }
    FFTWPlan( FFTWPlan const & ) = delete;
    FFTWPlan( FFTWPlan&& ) = delete;
    FFTWPlan& operator=( FFTWPlan const & ) = delete;
    FFTWPlan& operator=( FFTWPlan&& ) = delete;
private:
    fftw_plan p_;
};

template<typename CPF, typename APF, typename GC>
class ProtocolDef {
public:
    ProtocolDef( CPF CreateProtocolFn, APF ApplyParamsFn, GC GuiCtrl )
      : createProtocolFn_( CreateProtocolFn ), applyParamsFn_( ApplyParamsFn )
      , guiCtrl_( GuiCtrl ) {}
    CPF const & GetCreateProtocolFn() const { return createProtocolFn_; }
    APF const & GetApplyParamsFn() const { return applyParamsFn_; }
    GC const & GetGuiCtrl() const { return guiCtrl_; }
private:
    CPF createProtocolFn_;
    APF applyParamsFn_;
    GC guiCtrl_;
};

template<typename CPF, typename APF, typename GC>
inline ProtocolDef<CPF,APF,GC>* MakeProtocolDef( CPF CreateProtocolFn, APF ApplyParamsFn,
                                                 GC GuiCtrl )
{
    return new ProtocolDef<CPF,APF,GC>( CreateProtocolFn, ApplyParamsFn, GuiCtrl );
}

class WaveDataTimePoint {
public:
    WaveDataTimePoint( WaveIn::BufferCont const & WaveData, TDateTime TimePoint )
      : waveData_( WaveData ), timePoint_( TimePoint ) {}
    WaveIn::BufferCont const & GetWaveData() const { return waveData_; }
    TDateTime GetTimePoint() const { return timePoint_; }
private:
    WaveIn::BufferCont waveData_;
    TDateTime timePoint_;
};

class TfrmMain : public TConfigRegistryForm
{
__published:	// IDE-managed Components
    TActionManager *ActionManager1;
    TButton *Button1;
    TButton *Button4;
    TAction *actOpen;
    TAction *actFnReadHoldingRegisters;
    TAction *actFnPresetSingleRegister;
    TAction *actClose;
    TLabel *Label5;
    TPageControl *pgctrlProtocolSettings;
    TTabSheet *tbshtProtocolSerialSettings;
    TTabSheet *tbshtProtocolTCPIPSettings;
    TEdit *edtTCPIPHost;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *edtTCPIPPort;
    TComboBox *comboboxProtocol;
    TEdit *edtSlaveId;
    TLabel *Label6;
    TEdit *edtTransactionID;
    TLabel *Label7;
    TCheckBox *cboxAutoIncTransactionID;
    TfrmeSerialSettings *frmeSerialSettings1;
    TApplicationEvents *ApplicationEvents1;
    TPanel *pnlLog;
    TPanel *Panel5;
    TAction *actFnPresetMultipleRegisters;
    TAction *actFnReadInputRegisters;
    TfrmeLog *frmeLog1;
    TfrmeModbusFunctions *frmeModbusFunctions1;
    TPageControl *PageControl1;
    TTabSheet *tbshtModbus;
    TPanel *Panel1;
    TButton *Button2;
    TAction *actGarePrimaPGCMiratoStart;
    TAction *actGareResetCycle;
    TButton *Button3;
    TTimer *tmrGare;
    TLabel *lblStopwatch;
    TAction *actGareStop;
    TButton *Button5;
    TAction *actGareProvaPGCCelereStart;
    TButton *Button6;
    TAction *actGareApertura;
    TAction *actGareChiusura;
    TButton *Button7;
    TButton *Button8;
    TAction *actGareEnb1_5;
    TAction *actGareEnb6_10;
    TAction *actGareProvaPS150;
    TButton *Button9;
    TAction *actGarePrimaPS20;
    TAction *actGarePrimaPS10;
    TButton *Button11;
    TAction *actGareProvaPA8;
    TButton *Button12;
    TButton *Button13;
    TButton *Button14;
    TAction *actGarePrimaPA6;
    TAction *actGarePrimaPA4;
    TToggleSwitch *ToggleSwitch1;
    TToggleSwitch *ToggleSwitch2;
    TLabel *Label3;
    TLabel *Label4;
    TTimer *tmrReadStatusPorta;
    TPaintBox *PaintBox1_5;
    TPaintBox *PaintBox6_10;
    TStatusBar *StatusBar1;
    TTabSheet *tbshtPGCMirato;
    TTabSheet *tbshtPGCCelere;
    TTabSheet *tbshtPS10sec;
    TTabSheet *tbshtPS20sec;
    TTabSheet *tbshtPS150sec;
    TTabSheet *tbshtPA4sec;
    TTabSheet *tbshtPA6sec;
    TTabSheet *tbshtPA8sec;
    TPanel *pnlTrials;
    TPanel *Panel6;
    TPageControl *PageControl2;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TPanel *pnlTop;
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TLabel *Label8;
    TLabel *Label9;
    TAction *actGarePrimaPGCCelereStart;
    TAction *actGareProssimaPGCCelereStart;
    TButton *Button15;
    TButton *Button16;
    TButton *Button17;
    TButton *Button18;
    TAction *actGareProvaPGCMiratoStart;
    TAction *actGareProssimaPGCMiratoStart;
    TAction *actGareProssimaPS10;
    TButton *Button19;
    TButton *Button10;
    TButton *Button20;
    TAction *actGareProssimaPS20;
    TButton *Button21;
    TButton *Button22;
    TAction *actGarePrimaPS150;
    TAction *actGareProssimaPS150;
    TButton *Button23;
    TButton *Button24;
    TButton *Button25;
    TButton *Button26;
    TAction *actGareProssimaPA4;
    TAction *actGareProssimaPA6;
    TAction *actGarePrimaPA8;
    TAction *actGareProssimaPA8;
    TTabSheet *tbshtProtocolDummySettings;
    TTabSheet *tbshtMic;
    TComboBox *comboboxAudioSources;
    TLabel *Label10;
    TPaintBox *pboxSpectrogram;
    TPanel *pnlSpectrogram;
    TButton *Button27;
    TButton *Button28;
    TPageControl *pgctrlWaveViewer;
    TTabSheet *tbshtViewerFreq;
    TTabSheet *tbshtViewerTime;
    TChart *chartFreq;
    TLineSeries *SeriesFreq1;
    TLineSeries *SeriesFreq2;
    TChart *chartTime;
    TLineSeries *SeriesTime1;
    TLineSeries *SeriesTime2;
    TAction *actWaveStartListening;
    TAction *actWaveStopListening;
    TSplitter *Splitter1;
    TLabel *lblSpectrogramDuration;
    TLabel *Label12;
    TPanel *Panel2;
    TLineSeries *SeriesdBThreshold;
    TPanel *pnlTime;
    TImage *imgSpectrogramGradient;
    TLabel *Label13;
    TLabel *lblFloor_dB;
    TPaintBox *pboxSpectrogramGradientIndicator;
    TPanel *Panel4;
    TPanel *Panel7;
    TPanel *pnlThreshold;
    TLabel *Label11;
    TLabel *lblThreshold;
    TPaintBox *pboxFreqCuts;
    TAreaSeries *SeriesFreqCuts;
    TPaintBox *pboxPeaksTimepoint;
    TPanel *pnlPeaksTimepoint;
    TAction *actWaveSetParameters;
    TButton *Button29;
    TPanel *Panel3;
    TPanel *pnlStopwatch;
    TTaskDialog *TaskDialog1;
    void __fastcall EnableIfConnectionIsClose(TObject *Sender);
    void __fastcall EnableIfConnectionIsOpen(TObject *Sender);
    void __fastcall actCloseExecute(TObject *Sender);
    void __fastcall comboboxProtocolChange(TObject *Sender);
    void __fastcall actOpenExecute(TObject *Sender);
    void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
    void __fastcall actFnReadHoldingRegistersExecute(TObject *Sender);
    void __fastcall actFnPresetSingleRegisterExecute(TObject *Sender);
    void __fastcall actFnPresetMultipleRegistersExecute(TObject *Sender);
    void __fastcall ActionManager1Execute(TBasicAction *Action, bool &Handled);
    void __fastcall actFnReadInputRegistersExecute(TObject *Sender);
    void __fastcall actGarePrimaPGCMiratoStartExecute(TObject *Sender);
    void __fastcall actGareResetCycleExecute(TObject *Sender);
    void __fastcall EnableIfConnectionIsOpenAndEnabled(TObject *Sender);
    void __fastcall tmrGareTimer(TObject *Sender);
    void __fastcall actGareStopExecute(TObject *Sender);
    void __fastcall EnabledIfTrialIsRunning(TObject *Sender);
    void __fastcall actGareProvaPGCCelereStartExecute(TObject *Sender);
    void __fastcall actGareAperturaExecute(TObject *Sender);
    void __fastcall actGareChiusuraExecute(TObject *Sender);
    void __fastcall actGareEnb1_5Execute(TObject *Sender);
    void __fastcall actGareEnb6_10Execute(TObject *Sender);
    void __fastcall actGareProvaPS150Execute(TObject *Sender);
    void __fastcall actGarePrimaPS20Execute(TObject *Sender);
    void __fastcall actGarePrimaPS10Execute(TObject *Sender);
    void __fastcall actGareProvaPA8Execute(TObject *Sender);
    void __fastcall actGarePrimaPA6Execute(TObject *Sender);
    void __fastcall actGarePrimaPA4Execute(TObject *Sender);
    void __fastcall tmrReadStatusPortaTimer(TObject *Sender);
    void __fastcall PaintBox1_5Paint(TObject *Sender);
    void __fastcall actGarePrimaPGCCelereStartExecute(TObject *Sender);
    void __fastcall actGareProssimaPGCCelereStartExecute(TObject *Sender);
    void __fastcall actGareProssimaPGCMiratoStartExecute(TObject *Sender);
    void __fastcall actGareProvaPGCMiratoStartExecute(TObject *Sender);
    void __fastcall actGareProssimaPS10Execute(TObject *Sender);
    void __fastcall actGareProssimaPS20Execute(TObject *Sender);
    void __fastcall actGarePrimaPS150Execute(TObject *Sender);
    void __fastcall actGareProssimaPS150Execute(TObject *Sender);
    void __fastcall actGareProssimaPA4Execute(TObject *Sender);
    void __fastcall actGareProssimaPA6Execute(TObject *Sender);
    void __fastcall actGarePrimaPA8Execute(TObject *Sender);
    void __fastcall actGareProssimaPA8Execute(TObject *Sender);
    void __fastcall pboxSpectrogramPaint(TObject *Sender);
    void __fastcall ActionManager1Update(TBasicAction *Action, bool &Handled);
    void __fastcall actWaveStartListeningExecute(TObject *Sender);
    void __fastcall EnabledIfTrialIsNotRunning(TObject *Sender);
    void __fastcall actWaveStopListeningUpdate(TObject *Sender);
    void __fastcall actWaveStopListeningExecute(TObject *Sender);
    void __fastcall pnlSpectrogramResize(TObject *Sender);
    void __fastcall actWaveStartListeningUpdate(TObject *Sender);
    void __fastcall pboxSpectrogramGradientIndicatorPaint(TObject *Sender);
    void __fastcall pboxSpectrogramGradientIndicatorMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall pboxSpectrogramGradientIndicatorMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall pboxSpectrogramGradientIndicatorMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall pboxFreqCutsPaint(TObject *Sender);
    void __fastcall pboxFreqCutsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall pboxFreqCutsMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall pboxFreqCutsMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
    void __fastcall pboxPeaksTimepointPaint(TObject *Sender);
    void __fastcall actWaveSetParametersExecute(TObject *Sender);
    void __fastcall actWaveSetParametersUpdate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);

protected:
	virtual void __fastcall WndProc( Winapi::Messages::TMessage &Message ) override;
private:	// User declarations

    using ModbusProtocol = Modbus::Master::Protocol  ;
    using ModbusProtocolPtr = std::unique_ptr<ModbusProtocol>;
    using ModbusContext = Modbus::TCPIPContext;
    using CreateProtocolFnMemPtrType = ModbusProtocolPtr (*)();
    using ApplyProtoParamsFnMemPtrType = void ( TfrmMain::* )( ModbusProtocol& ) const;

    using ProtoDef =
        ProtocolDef<CreateProtocolFnMemPtrType,ApplyProtoParamsFnMemPtrType,TTabSheet*>;

    static ModbusProtocolPtr CreateRTUProtocol();
    void ApplyRTUProtoParams( ModbusProtocol& Proto ) const;
    static ModbusProtocolPtr CreateTCPIndyProtocol();
    void ApplyTCPIPProtoParams( ModbusProtocol& Proto ) const;
    static ModbusProtocolPtr CreateUDPIndyProtocol();
    static ModbusProtocolPtr CreateDummyProtocol();
    void ApplyDummyProtoParams( ModbusProtocol& Proto ) const;

    std::array<ProtoDef, 4> const Protocols{ {
      ProtoDef(
        &TfrmMain::CreateRTUProtocol,
        &TfrmMain::ApplyRTUProtoParams,
        tbshtProtocolSerialSettings
      ),
      ProtoDef(
        &TfrmMain::CreateTCPIndyProtocol,
        &TfrmMain::ApplyTCPIPProtoParams,
        tbshtProtocolTCPIPSettings
      ),
      ProtoDef(
        &TfrmMain::CreateUDPIndyProtocol,
        &TfrmMain::ApplyTCPIPProtoParams,
        tbshtProtocolTCPIPSettings
      ),
      ProtoDef(
        &TfrmMain::CreateDummyProtocol,
        &TfrmMain::ApplyDummyProtoParams,
        tbshtProtocolDummySettings
      ),

    } };

    ModbusProtocolPtr modbusProto_;
    std::mutex modbusProtoMutex_;

    std::unique_ptr<WaveInCO> waveIn_;

    using FFTWContN = FFTWCont<WaveIn::SampleCount>;
    using FFTWPlanType = FFTWPlan<FFTWContN>;

    using SignalCont = std::array<double,WaveIn::SampleCount>;
    //FFTWContN FFTIn_;
    //FFTWContN FFTOut_;
    //FFTWPlanType FFTPlan_;

    std::mutex spectrogramMutex_;
    std::array<std::unique_ptr<TBitmap>,2> spectrogramBmps_;

    void Init();
    void Destroy();
    static String GetModuleFileName();
    void SetupCaption();
    void RestoreProperties();
    void SaveProperties() const;

    void ScanSerialPorts();

    ProtoDef const & GetSelectedProtoDef() const;

    void SetupSerialPortsControls();
    void SetupAudioSourcesControls();

    String GetModbusProtocolName() const;
    void SetModbusProtocolName( String Val );

    int GetSlaveID() const;
    void SetSlaveID( int Val );
    int GetTransactionID() const;
    void SetTransactionID( int Val );
    bool GetAutoIncTransactionID() const;
    void SetAutoIncTransactionID( bool Val );

    String GetTCPIPHost() const;
    void SetTCPIPHost( String Val );
    int GetTCPIPPort() const;
    void SetTCPIPPort( int Val );

    String GetSerialPortPortName() const { return frmeSerialSettings1->PortName; }
    void SetSerialPortPortName( String Val ) { frmeSerialSettings1->PortName = Val; }
    int GetSerialPortSpeed() const { return frmeSerialSettings1->Speed; }
    void SetSerialPortSpeed( int Val ) { frmeSerialSettings1->Speed = Val; }
    int GetSerialPortParity() const { return frmeSerialSettings1->Parity; }
    void SetSerialPortParity( int Val ) { frmeSerialSettings1->Parity = Val; }
    int GetSerialPortBits() const { return frmeSerialSettings1->Bits; }
    void SetSerialPortBits( int Val ) { frmeSerialSettings1->Bits = Val; }
    int GetSerialPortStopBits() const { return frmeSerialSettings1->StopBits; }
    void SetSerialPortStopBits( int Val ) { frmeSerialSettings1->StopBits = Val; }
    bool GetSerialPortCancelTXEcho() const { return frmeSerialSettings1->CancelTXEcho; }
    void SetSerialPortCancelTXEcho( bool Val ) { frmeSerialSettings1->CancelTXEcho = Val; }

    ModbusProtocolPtr CreateProtocol();

    bool IsConnectionActive() const;

    void LogMessage( String Text, TColor Color = clWindowText );
    void LogMessage( String FormatText, TVarRec const *Args, int Args_High,
                     TColor Color = clWindowText );

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
    bool GetPresetSingleRegisterPulsed() const;
    void SetPresetSingleRegisterPulsed( bool Val );
    uint32_t GetPresetSingleRegisterPulseTime() const;
    void SetPresetSingleRegisterPulseTime( uint32_t Val );
    Modbus::RegAddrType GetPresetMultipleRegistersAddr() const;
    void SetPresetMultipleRegistersAddr( Modbus::RegAddrType Val );
    String GetPresetMultipleRegistersData() const;
    void SetPresetMultipleRegistersData( String Val );
    bool GetPresetMultipleRegisterPulsed() const;
    void SetPresetMultipleRegisterPulsed( bool Val );
    uint32_t GetPresetMultipleRegisterPulseTime() const;
    void SetPresetMultipleRegisterPulseTime( uint32_t Val );
    String GetWaveInDevice() const;
    void SetWaveInDevice( String Val );
    int GetMainPanelSize() const;
    void SetMainPanelSize( int Val );
    int GetThreshold() const;
    void SetThreshold( int Val );

    int GetWaveInId() const;

    __property String ModbusProtocolName = {
        read = GetModbusProtocolName, write = SetModbusProtocolName
    };

    __property int SlaveID = { read = GetSlaveID, write = SetSlaveID };
    __property int TransactionID = { read = GetTransactionID, write = SetTransactionID };
    __property bool AutoIncTransactionID = { read = GetAutoIncTransactionID, write = SetAutoIncTransactionID };

    __property String TCPIPHost = { read = GetTCPIPHost, write = SetTCPIPHost };
    __property int TCPIPPort = { read = GetTCPIPPort, write = SetTCPIPPort };

    __property String SerialPortName = { read = GetSerialPortPortName, write = SetSerialPortPortName };
    __property int SerialPortSpeed = { read = GetSerialPortSpeed, write = SetSerialPortSpeed };
    __property int SerialPortParity = { read = GetSerialPortParity, write = SetSerialPortParity };
    __property int SerialPortBits = { read = GetSerialPortBits, write = SetSerialPortBits };
    __property int SerialPortStopBits = { read = GetSerialPortStopBits, write = SetSerialPortStopBits };
    __property bool SerialPortCancelTXEcho = { read = GetSerialPortCancelTXEcho, write = SetSerialPortCancelTXEcho };

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
    __property bool PresetSingleRegisterPulsed = {
        read = GetPresetSingleRegisterPulsed,
        write = SetPresetSingleRegisterPulsed
    };
    __property uint32_t PresetSingleRegisterPulseTime = {
        read = GetPresetSingleRegisterPulseTime,
        write = SetPresetSingleRegisterPulseTime
    };
    __property Modbus::RegAddrType PresetMultipleRegistersAddr = {
        read = GetPresetMultipleRegistersAddr, write = SetPresetMultipleRegistersAddr
    };
    __property String PresetMultipleRegistersData = {
        read = GetPresetMultipleRegistersData, write = SetPresetMultipleRegistersData
    };
    __property bool PresetMultipleRegisterPulsed = {
        read = GetPresetMultipleRegisterPulsed,
        write = SetPresetMultipleRegisterPulsed
    };
    __property uint32_t PresetMultipleRegisterPulseTime = {
        read = GetPresetMultipleRegisterPulseTime,
        write = SetPresetMultipleRegisterPulseTime
    };

    __property int WaveInId = {
        read = GetWaveInId
    };

    __property String WaveInDevice = {
        read = GetWaveInDevice, write = SetWaveInDevice
    };

    __property int MainPanelSize = {
        read = GetMainPanelSize, write = SetMainPanelSize
    };

    __property int Threshold = {
        read = GetThreshold, write = SetThreshold
    };

    ModbusContext ContextSx{ 2, 0 };
    ModbusContext ContextDx{ 1, 0 };

public:
    enum class CmdType {
        None, Chiusura, Apertura, MessaggioAsincrono, MessaggioSincrono,
        StartAudioSampling, StopAudioSampling,
    };

    class Cmd {
    public:
        constexpr Cmd( CmdType Cmd, uint16_t Time, LPCTSTR Msg, LPCTSTR AuxData = nullptr )
            : cmd_{ Cmd }, time_{ Time }, message_{ Msg }, auxData_{ AuxData } {}
        CmdType GetCmd() const { return cmd_; }
        uint16_t GetTime() const { return time_; }
        LPCTSTR GetMessage() const { return message_; }
        LPCTSTR GetAuxData() const { return auxData_; }
    private:
        CmdType cmd_;
        uint16_t time_;
        LPCTSTR message_;
        LPCTSTR auxData_;
    };

private:
    static constexpr auto WM_USER_LOG_EXCEPTION_MSG = WM_USER + 999;
    static constexpr auto WM_USER_REPAINT_LED_1_5 = WM_USER + 15;
    static constexpr auto WM_USER_REPAINT_LED_6_10 = WM_USER + 620;
    static constexpr auto WM_USER_RESTART_STATUS_PORTA = WM_USER + 101;
    static constexpr auto WM_USER_WAVE_DATA = WM_USER + 876;

    GdiplusUtils::GdiPlusSessionManager gdiPlusSessionManager_;
    std::future<void> currentTask_;
    Cmd const * cmds_ { nullptr };
    size_t stepCount_ {};
    TDateTime deadLine_ {};
    std::atomic<Modbus::RegDataType> sagome1_5_out_ {};
    std::atomic<Modbus::RegDataType> sagome6_10_out_ {};
    static constexpr bool DefaultPortaChiusa { false };
    bool portaChiusa_{ DefaultPortaChiusa };
    std::atomic<bool> taskRunning_ {};
    size_t seriesNo_ {};
    int cutdBThreshold_ = -20;
    int spectrogramThresholdMin_ { -96 };
    int spectrogramThresholdMax_ { 0 };
    bool spectrogramGradientIndicatorTracking_ {};

    using SpectrogramColorMapType = std::array<RGBTRIPLE,256>;

    SpectrogramColorMapType spectrogramColorMap_;

    static double constexpr spectrogramdBFloor = -96.0;

    double cutLoFreq_ { 172.265625 };
    double cutHiFreq_ { 3962.109375 };

    enum class FreqCutTracking { None, Lo, Hi };

    FreqCutTracking freqCutTracking_ { FreqCutTracking::None };

    using FreqCutHandlePolygonType = std::array<Gdiplus::PointF,3>;

    size_t detectCnt_ {};
    TDateTime detectTimePoint_ {};
    TDateTime startListeningTimePoint_ {};

    std::vector<TDateTime> peaksAbsTimePoint_;

    int peakDetMinDuration_ { 70 };
    int peakDetConf_{ 80 };

    SignalCont window_;

    TDateTime peakDetInhTime_ {};

    uint16_t peakMinDetectionTimeDistance_ { 200 };

    int pollingTimerDisabled_ { false };

    String soundFolder_;

    void AllOff();
    void AllOn();
    void SingleReset();
    void DoubleReset();
    void ResetCycle();
    void Apertura();
    void Chiusura();
    TDateTime EseguiComando( Cmd const & Comando );
    Modbus::RegDataType GetSagome1_5_Out() const;
    Modbus::RegDataType GetSagome6_10_Out() const;
    void SetSagome1_5_Out( Modbus::RegDataType Val );
    void SetSagome6_10_Out( Modbus::RegDataType Val );
    void UpdateOuts( Modbus::RegDataType Val );
    void SetStopwatchColor( TColor Val );
    void UpdateStopwatch( TDateTime Val );
    void ReadHoldingRegisters( Modbus::Context const & Context,
                               Modbus::RegAddrType StartAddr,
                               Modbus::RegCountType PointCount,
                               Modbus::RegDataType* Data );
    void ReadInputRegisters( Modbus::Context const & Context,
                             Modbus::RegAddrType StartAddr,
                             Modbus::RegCountType PointCount,
                             Modbus::RegDataType* Data );
    void PresetSingleRegister( Modbus::Context const & Context,
                               Modbus::RegAddrType Addr,
                               Modbus::RegDataType Data );
    void PresetMultipleRegisters( Modbus::Context const & Context,
                                  Modbus::RegAddrType StartAddr,
                                  Modbus::RegCountType PointCount,
                                  const Modbus::RegDataType* Data );
    void DisableAll();
    void ReadStatusPorta();
    void StartGara( Cmd const * Cmds, size_t CmdsCnt );

    __property Modbus::RegDataType Sagome1_5_Out = {
        read = GetSagome1_5_Out, write = SetSagome1_5_Out
    };
    __property Modbus::RegDataType Sagome6_10_Out = {
        read = GetSagome6_10_Out, write = SetSagome6_10_Out
    };

    void StopGara();
    void Close();
    void LogException( Exception const & E );
    void LogStdException( std::exception const & e );
    void LogUnknownException();

    void __fastcall WaveDataEvtHndlr( WaveIn::BufferCont const & WaveData );

    void CreateSpectrogramBmps();
    void DrawSpectrogramLine( FFTWContN const & FreqDomainWaveData );
    static void AppendAudioSources( TStrings& List );

    static bool IgnoreSettings();

    TChartSeries& GetCurrentFreqSeries() const;
    TChartSeries& GetCurrentTimeSeries() const;

    void UpdateCharts( SignalCont const & TimeDomainWaveData,
                       FFTWContN const & FreqDomainWaveData );

    //void HandleUserWaveData( WaveIn::BufferCont* const DataPtr );
    void HandleUserWaveData( WaveDataTimePoint* const DataRawPtr );
    //void ApplyWindow( SignalCont const & Signal, FFTWContN& FFTPoints ) const;
    void ComputeWindow();
    void ComputeUniformWindow();
    void ComputeHanningWindow();
    void ComputeFlattopWindow();
    void ComputeBlackmanWindow();
    void ComputeHammingWindow();
    void ComputeKaiserBesselWindow();

    //double GetWindowEnergyScalefactor() const;

    enum class WindowType {
        Uniform, Hanning, Flattop, Blackman, Hamming, KaiserBessel
    };

    // See: https://tinyurl.com/fftwinfactcorr
    static std::array<double,6> const windowScaleFactorsEnergy_;

    WindowType selectedWindoType_ {
        //WindowType::Uniform
        WindowType::Hanning
        //WindowType::Flattop
        //WindowType::Blackman
    };

    void UpdateThresholddBControls();
    int ClipThresholdValue( int Val ) const;
    void UpdateThresholddBDisplayControl();
    void ComputeSpectrogramColorMap();
    std::unique_ptr<TBitmap> CreateSpectrogramGradientBitmap( int Width ) const;
    bool SpectrogramGradientMouseOndBIndicator( int X, int Y ) const;
    double CutHandleXCoordFromFreq( double Freq ) const;
    double CutHandleFreqFromXCoord( int X ) const;
    int CutMarkerXCoordFromFreq( double Freq ) const;
    static Gdiplus::Color GetHandleColor( bool Active );
    bool SpectrogramGradientMouseOnLoFreqIndicator( int X, int Y ) const;
    bool SpectrogramGradientMouseOnHiFreqIndicator( int X, int Y ) const;
    void SetCutLoFreq( double Val );
    void SetCutHiFreq( double Val );
    void SetPeakDetectionMinDuration( int Val );
    void SetPeakDetectionConfidence( int Val );
    void SetPeakMinDetectionTimeDistance( int Val );

    FreqCutHandlePolygonType GetFreqCutHandlePolygon( double Freq, bool Mirror ) const;
    FreqCutHandlePolygonType GetFreqCutLoHandlePolygon() const;
    FreqCutHandlePolygonType GetFreqCutHiHandlePolygon() const;

    __property double CutLoFreq = { read = cutLoFreq_, write = SetCutLoFreq  };
    __property double CutHiFreq = { read = cutHiFreq_, write = SetCutHiFreq  };

    void UpdateFreqCutControls();

    int SampleIdxFromFreq( double Freq ) const;

    void PeakDetection( FFTWContN const & FreqDomainWaveData,
                        TDateTime TimePoint );

    int GetModbusTesterEnabled() const;
    void SetModbusTesterEnabled( int Val );

    int GetPollingTimerDisabled() const;
    void SetPollingTimerDisabled( int Val );

    void ShowAdditionalSettingsWarning();

    __property int PeakDetectionMinDuration = {
        read = peakDetMinDuration_, write = SetPeakDetectionMinDuration
    };
    __property int PeakDetectionConfidence = {
        read = peakDetConf_, write = SetPeakDetectionConfidence
    };

    __property int PeakMinDetectionTimeDistance = {
        read = peakMinDetectionTimeDistance_,
        write = SetPeakMinDetectionTimeDistance
    };

    __property int ModbusTesterEnabled = {
        read = GetModbusTesterEnabled,
        write = SetModbusTesterEnabled
    };

    __property int PollingTimerDisabled = {
        read = GetPollingTimerDisabled,
        write = SetPollingTimerDisabled
    };

    __property String SoundFolder = {
        read = soundFolder_,
        write = soundFolder_
    };
public:		// User declarations
	using inherited = TConfigRegistryForm;

	__fastcall TfrmMain( TComponent* Owner ) override;
	__fastcall TfrmMain( TComponent* Owner, StoreOpts StoreOptions,
                         Anafestica::TConfigNode* const RootNode = 0 );
	__fastcall ~TfrmMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

