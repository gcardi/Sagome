//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <System.SyncObjs.hpp>
#include <System.DateUtils.hpp>
#include <System.Win.ComObj.hpp>
#include <System.IOUtils.hpp>

#include <memory>
#include <iterator>
#include <algorithm>
#include <vector>
#include <array>
#include <complex>

#include <anafestica/FileVersionInfo.h>

#include "Utils.h"
#include "RegexDefs.h"
#include "SerEnum.h"
#include "ModbusRTU.h"
#include "ModbusTCP_Indy.h"
#include "ModbusUDP_Indy.h"
#include "ModbusDummy.h"
#include "FormMain.h"
#include "Cursor.h"
#include "Led.h"
#include "MP3Mod.h"

//#include <mfidl.h>

#include <Mmsystem.h>
#include <Dshow.h>
#include <Strmif.h>
#include "WavInfo.h"
#include "ColorCvt.h"
#include "FormWaveParams.h"

using Anafestica::TFileVersionInfo;

using std::unique_ptr;
using std::back_inserter;
using std::min;
using std::max;
using std::vector;
using std::make_unique;
using std::array;
using std::unique_lock;
using std::mutex;
using std::complex;
using std::swap;

using SclLedCtrl::Led;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FrameSerialSettings"
#pragma link "FrameLog"
#pragma link "FrameModbusFunctions"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------

__fastcall TfrmMain::TfrmMain(TComponent* Owner)
  : TfrmMain( Owner, IgnoreSettings() ? StoreOpts::None : StoreOpts::All, nullptr )
{
}
//---------------------------------------------------------------------------

__fastcall TfrmMain::TfrmMain( TComponent* Owner, StoreOpts StoreOptions,
                               Anafestica::TConfigNode* const RootNode )
  : TConfigRegistryForm( Owner, StoreOptions, RootNode )
//  , FFTPlan_( FFTIn_, FFTOut_ )
{
    Init();
}
//---------------------------------------------------------------------------

__fastcall TfrmMain::~TfrmMain() /* throw() */
{
    try {
        DisableAll();
        Destroy();
    }
    catch ( ... ) {
    }
}
//---------------------------------------------------------------------------

void TfrmMain::LogException( Exception const & E )
{
    LogMessage( _T( "Exception: %s\n" ), ARRAYOFCONST( ( E.Message ) ), clRed );
}
//---------------------------------------------------------------------------

void TfrmMain::LogStdException( std::exception const & e )
{
    LogMessage( _T( "std::exception: %s\n" ), ARRAYOFCONST( ( e.what() ) ), clRed );
}
//---------------------------------------------------------------------------

void TfrmMain::LogUnknownException()
{
    LogMessage( _T( "Unknown exception\n" ), clRed );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::WndProc( Winapi::Messages::TMessage &Message )
{
    try {
        switch ( Message.Msg ) {
            case WM_USER_WAVE_DATA:
                HandleUserWaveData(
                    //reinterpret_cast<WaveIn::BufferCont*>( Message.WParam )
                    reinterpret_cast<WaveDataTimePoint*>( Message.WParam )
                );
                break;
            case WM_USER_REPAINT_LED_1_5:
                PaintBox1_5->Repaint();
                return;
            case WM_USER_REPAINT_LED_6_10:
                PaintBox6_10->Repaint();
                return;
            case WM_USER_RESTART_STATUS_PORTA:
                tmrReadStatusPorta->Enabled = true;
                return;
            case WM_USER_LOG_EXCEPTION_MSG:
                {
                    unique_ptr<String> MsgPtr(
                        reinterpret_cast<String* const>( Message.WParam )
                    );
                    if ( MsgPtr ) {
                        LogMessage(
                            _T( "Exception: %s\n" ), ARRAYOFCONST( ( *MsgPtr ) ),
                            clRed
                        );
                    }
                    else {
                        LogMessage( _T( "Unknown exception\n" ), clRed );
                    }
                }
                StopGara();
                Close();
                tmrReadStatusPorta->Enabled = true;
                return;
            default:
                break;
        }
        inherited::WndProc( Message );
    }
    catch ( Exception const & E ) {
        LogException( E );
    }
    catch ( std::exception const & e ) {
        LogStdException( e );
    }
    catch ( ... ) {
        LogUnknownException();
    }
}
//---------------------------------------------------------------------------

void TfrmMain::Init()
{
    SetupCaption();

    tbshtMic->ControlStyle = tbshtMic->ControlStyle << csOpaque;
    pnlSpectrogram->ControlStyle = pnlSpectrogram->ControlStyle << csOpaque;

    SetupSerialPortsControls();
    SetupAudioSourcesControls();

    CreateSpectrogramBmps();

    //chartTime->BottomAxis->Maximum = WaveIn::SampleCount - 1;

    chartTime->BottomAxis->Maximum =
        1000.0 * WaveIn::SampleCount / WaveIn::SamplesPerSec;

    if ( !IgnoreSettings() ) {
        RestoreProperties();
    }

    lblFloor_dB->Caption =
        Format(
            _T( "%1.0f dB" ),
            ARRAYOFCONST( (
                static_cast<const long double>( spectrogramdBFloor )
            ) )
        );

    //trackbarThreshold1->Min = -spectrogramThresholdMax_;
    //trackbarThreshold1->Max = -spectrogramThresholdMin_;

    SeriesdBThreshold->XValues->Items[0] = 0.0;
    SeriesdBThreshold->XValues->Items[1] =
        static_cast<double>( WaveIn::SamplesPerSec ) / 2.0;

    UpdateThresholddBControls();

    SeriesFreqCuts->YValues->Items[0] = chartFreq->LeftAxis->Minimum;
    SeriesFreqCuts->YValues->Items[1] = chartFreq->LeftAxis->Maximum;
    SeriesFreqCuts->YValues->Items[2] = chartFreq->LeftAxis->Maximum;
    SeriesFreqCuts->YValues->Items[3] = chartFreq->LeftAxis->Minimum;

    UpdateFreqCutControls();

    ComputeWindow();
}
//---------------------------------------------------------------------------

void TfrmMain::Destroy()
{
    SaveProperties();
    for ( int Idx = 0 ; Idx < comboboxProtocol->Items->Count ; ++Idx ) {
        try {
            delete comboboxProtocol->Items->Objects[Idx];
        }
        catch ( ... ) {
        }
    }
}
//---------------------------------------------------------------------------

String TfrmMain::GetModuleFileName()
{
    return GetModuleName( reinterpret_cast<unsigned>( HInstance ) );
}
//---------------------------------------------------------------------------

void TfrmMain::SetupCaption()
{
    TFileVersionInfo const Info( GetModuleFileName() );
    Caption =
        Format(
            _T( "%s, Ver %s" ),
            ARRAYOFCONST( (
                Application->Title,
                Info.ProductVersion
            ) )
        );
}
//---------------------------------------------------------------------------

void TfrmMain::RestoreProperties()
{
    RESTORE_LOCAL_PROPERTY( ModbusProtocolName );

    RESTORE_LOCAL_PROPERTY( SlaveID );
    RESTORE_LOCAL_PROPERTY( TransactionID );

    RESTORE_LOCAL_PROPERTY( AutoIncTransactionID );

    RESTORE_LOCAL_PROPERTY( TCPIPHost );
    RESTORE_LOCAL_PROPERTY( TCPIPPort );

    RESTORE_LOCAL_PROPERTY( SerialPortName );
    RESTORE_LOCAL_PROPERTY( SerialPortSpeed );
    RESTORE_LOCAL_PROPERTY( SerialPortParity );
    RESTORE_LOCAL_PROPERTY( SerialPortBits );
    RESTORE_LOCAL_PROPERTY( SerialPortStopBits );

    RESTORE_LOCAL_PROPERTY( SerialPortCancelTXEcho );

    RESTORE_LOCAL_PROPERTY( FnIdx );
    RESTORE_LOCAL_PROPERTY( ReadHoldingRegistersAddr );
    RESTORE_LOCAL_PROPERTY( ReadHoldingRegistersPtCnt );
    RESTORE_LOCAL_PROPERTY( ReadInputRegistersAddr );
    RESTORE_LOCAL_PROPERTY( ReadInputRegistersPtCnt );
    RESTORE_LOCAL_PROPERTY( PresetSingleRegisterAddr );
    RESTORE_LOCAL_PROPERTY( PresetSingleRegisterValue );
    RESTORE_LOCAL_PROPERTY( PresetSingleRegisterPulseTime );
    RESTORE_LOCAL_PROPERTY( PresetMultipleRegistersAddr );
    RESTORE_LOCAL_PROPERTY( PresetMultipleRegistersData );
    RESTORE_LOCAL_PROPERTY( PresetMultipleRegisterPulseTime );

    RESTORE_LOCAL_PROPERTY( WaveInDevice );
    RESTORE_LOCAL_PROPERTY( MainPanelSize );
    RESTORE_LOCAL_PROPERTY( Threshold );

    RESTORE_LOCAL_PROPERTY( CutLoFreq );
    RESTORE_LOCAL_PROPERTY( CutHiFreq );

    RESTORE_LOCAL_PROPERTY( PeakDetectionMinDuration );
    RESTORE_LOCAL_PROPERTY( PeakDetectionConfidence );
    RESTORE_LOCAL_PROPERTY( PeakMinDetectionTimeDistance );

    RESTORE_LOCAL_PROPERTY( ModbusTesterEnabled );
    RESTORE_LOCAL_PROPERTY( PollingTimerDisabled );

    RESTORE_LOCAL_PROPERTY( SoundFolder );

    RESTORE_LOCAL_PROPERTY( IgnoreDoor );
}
//---------------------------------------------------------------------------

void TfrmMain::SaveProperties() const
{
    SAVE_LOCAL_PROPERTY( ModbusProtocolName );

    SAVE_LOCAL_PROPERTY( SlaveID );
    SAVE_LOCAL_PROPERTY( TransactionID );
    SAVE_LOCAL_PROPERTY( AutoIncTransactionID );

    SAVE_LOCAL_PROPERTY( TCPIPHost );
    SAVE_LOCAL_PROPERTY( TCPIPPort );

    SAVE_LOCAL_PROPERTY( SerialPortName );
    SAVE_LOCAL_PROPERTY( SerialPortSpeed );
    SAVE_LOCAL_PROPERTY( SerialPortParity );
    SAVE_LOCAL_PROPERTY( SerialPortBits );
    SAVE_LOCAL_PROPERTY( SerialPortStopBits );
    SAVE_LOCAL_PROPERTY( SerialPortCancelTXEcho );

    SAVE_LOCAL_PROPERTY( FnIdx );
    SAVE_LOCAL_PROPERTY( ReadHoldingRegistersAddr );
    SAVE_LOCAL_PROPERTY( ReadHoldingRegistersPtCnt );
    SAVE_LOCAL_PROPERTY( ReadInputRegistersAddr );
    SAVE_LOCAL_PROPERTY( ReadInputRegistersPtCnt );
    SAVE_LOCAL_PROPERTY( PresetSingleRegisterAddr );
    SAVE_LOCAL_PROPERTY( PresetSingleRegisterValue );
    SAVE_LOCAL_PROPERTY( PresetSingleRegisterPulseTime );
    SAVE_LOCAL_PROPERTY( PresetMultipleRegistersAddr );
    SAVE_LOCAL_PROPERTY( PresetMultipleRegistersData );
    SAVE_LOCAL_PROPERTY( PresetMultipleRegisterPulseTime );

    SAVE_LOCAL_PROPERTY( WaveInDevice );
    SAVE_LOCAL_PROPERTY( MainPanelSize );
    SAVE_LOCAL_PROPERTY( Threshold );

    SAVE_LOCAL_PROPERTY( CutLoFreq );
    SAVE_LOCAL_PROPERTY( CutHiFreq );

    SAVE_LOCAL_PROPERTY( PeakDetectionMinDuration );
    SAVE_LOCAL_PROPERTY( PeakDetectionConfidence );
    SAVE_LOCAL_PROPERTY( PeakMinDetectionTimeDistance );
}
//---------------------------------------------------------------------------

int TfrmMain::GetModbusTesterEnabled() const
{
    return tbshtModbus->TabVisible;
}
//---------------------------------------------------------------------------

void TfrmMain::SetModbusTesterEnabled( int Val )
{
    tbshtModbus->TabVisible = Val;
}
//---------------------------------------------------------------------------

int TfrmMain::GetPollingTimerDisabled() const
{
    return pollingTimerDisabled_;
}
//---------------------------------------------------------------------------

void TfrmMain::SetPollingTimerDisabled( int Val )
{
    pollingTimerDisabled_ = Val;
}
//---------------------------------------------------------------------------

void TfrmMain::SetupSerialPortsControls()
{
    ScanSerialPorts();
    if ( int const PortCount = frmeSerialSettings1->PortNameList.Count ) {
        frmeSerialSettings1->PortName =
            frmeSerialSettings1->PortNameList.Strings[0];
    }
    comboboxProtocol->Clear();
    for ( auto Def : Protocols ) {
        comboboxProtocol->Items->Append(
            ( *Def.GetCreateProtocolFn() )()->GetProtocolName()
        );
    }
    comboboxProtocol->ItemIndex = 2;
    comboboxProtocolChange( comboboxProtocol );
}
//---------------------------------------------------------------------------

void TfrmMain::AppendAudioSources( TStrings& List )
{
    using _di_ICreateDevEnum = DelphiInterface<ICreateDevEnum>;

    _di_ICreateDevEnum DevEnum;

    //Initialise Device enumerator
    OleCheck(
        CoCreateInstance(
            CLSID_SystemDeviceEnum, nullptr, CLSCTX_INPROC_SERVER,
            IID_ICreateDevEnum, reinterpret_cast<void **>( &DevEnum )
        )
    );

    _di_IEnumMoniker EnumCat;

    OleCheck(
        DevEnum->CreateClassEnumerator(
            CLSID_AudioInputDeviceCategory, &EnumCat, 0
        )
    );

    _di_IMoniker DeviceMoniker;

    ULONG cFetched;
    while ( EnumCat && EnumCat->Next( 1, &DeviceMoniker, &cFetched ) == S_OK ) {
        _di_IPropertyBag PropBag;

        //bind the properties of the moniker
        OleCheck(
            DeviceMoniker->BindToStorage(
                0, 0, IID_IPropertyBag,
                reinterpret_cast<void **>( &PropBag )
            )
        );

        OleVariant v;
        OleCheck( PropBag->Read( L"FriendlyName", v, 0 ) );
        List.Append( v );
    }
/*
    WAVEINCAPS wic;

    auto NumDevs = waveInGetNumDevs();

    for ( decltype( NumDevs ) i = 0; i < NumDevs ; ++i ) {
        if ( !waveInGetDevCaps( i, &wic, sizeof wic ) ) {
            List.Append( wic.szPname );
        }
    }
*/
}
//---------------------------------------------------------------------------

void TfrmMain::SetupAudioSourcesControls()
{
    comboboxAudioSources->Items->Clear();

    AppendAudioSources( *comboboxAudioSources->Items );

    if ( comboboxAudioSources->Items->Count > 0 ) {
        comboboxAudioSources->ItemIndex = 0;
    }
}
//---------------------------------------------------------------------------

void TfrmMain::LogMessage( String Text, TColor Color )
{
    frmeLog1->LogMessage( Text, Color );
}
//---------------------------------------------------------------------------

void TfrmMain::LogMessage( String FormatText, TVarRec const *Args, int Args_High,
                           TColor Color )
{
    LogMessage( Format( FormatText, Args, Args_High ), Color );
}
//---------------------------------------------------------------------------

template<typename TT>
struct EnumSerialPortFnctr {
    template<typename T1, typename T2>
    TT operator()( T1 const & Name, T2 const & Descr ) {
        return TT( Name );
    }
};

struct ComNumCmp {
    regex_type re;
    ComNumCmp() : re( _T( "^[^\\d]*(\\d+).*$" ), boost::regex::icase ) {}
    template<typename T1, typename T2>
    bool operator()( T1 const & Lhs, T2 const & Rhs )  {
        regex_cmatch_type m;

        if ( regex_match( String( Lhs ).c_str(), m, re ) ) {
            if ( m[1].matched  ) {
                int const L = String( m[1].str().c_str() ).ToInt();
                if ( regex_match( String( Rhs ).c_str(), m, re ) ) {
                    if ( m[1].matched  ) {
                        int const R = String( m[1].str().c_str() ).ToInt();
                        if ( R != L ) {
                            return L < String( m[1].str().c_str() ).ToInt();
                        }
                    }
                }
            }
        }
        return String( Lhs ) < String( Rhs );
    }
};

void TfrmMain::ScanSerialPorts()
{
    auto& PortNameList = frmeSerialSettings1->PortNameList;
    vector<String> Ports;

    SvcApp::Utils::EnumSerialPort( back_inserter( Ports ), EnumSerialPortFnctr<String>() );

    std::stable_sort( begin( Ports ), end( Ports ), ComNumCmp() );

    for ( auto const & Port : Ports ) {
        PortNameList.Append( Port );
    }
}
//---------------------------------------------------------------------------

TfrmMain::ProtoDef const & TfrmMain::GetSelectedProtoDef() const
{
    return Protocols[comboboxProtocol->ItemIndex];
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::comboboxProtocolChange(TObject *Sender)
{
    pgctrlProtocolSettings->ActivePage = GetSelectedProtoDef().GetGuiCtrl();
}
//---------------------------------------------------------------------------

String TfrmMain::GetModbusProtocolName() const
{
    return Trim( comboboxProtocol->Text );
}
//---------------------------------------------------------------------------

void TfrmMain::SetModbusProtocolName( String Val )
{
    int const Idx = comboboxProtocol->Items->IndexOf( Trim( Val ) );
    if ( Idx >= 0 ) {
        comboboxProtocol->ItemIndex = Idx;
        pgctrlProtocolSettings->ActivePage = GetSelectedProtoDef().GetGuiCtrl();
    }
}
//---------------------------------------------------------------------------

TfrmMain::ModbusProtocolPtr TfrmMain::CreateProtocol()
{
    auto const & Def = GetSelectedProtoDef();
    auto Proto = Def.GetCreateProtocolFn()();
    ( this->*Def.GetApplyParamsFn() )( *Proto );
    return Proto;
}
//---------------------------------------------------------------------------

TfrmMain::ModbusProtocolPtr TfrmMain::CreateRTUProtocol()
{
    return make_unique<Modbus::Master::RTUProtocol>();
}
//---------------------------------------------------------------------------

TfrmMain::ModbusProtocolPtr TfrmMain::CreateTCPIndyProtocol()
{
    return make_unique<Modbus::Master::TCPProtocolIndy>();
}
//---------------------------------------------------------------------------

TfrmMain::ModbusProtocolPtr TfrmMain::CreateUDPIndyProtocol()
{
    return make_unique<Modbus::Master::UDPProtocolIndy>();
}
//---------------------------------------------------------------------------

TfrmMain::ModbusProtocolPtr TfrmMain::CreateDummyProtocol()
{
    return make_unique<Modbus::Master::DummyProtocol>();
}
//---------------------------------------------------------------------------

void TfrmMain::ApplyRTUProtoParams( ModbusProtocol& Proto ) const
{
    Modbus::Master::RTUProtocol& RTUProto =
        dynamic_cast<Modbus::Master::RTUProtocol&>( Proto );
    RTUProto.SetCommPort(
        Format(
            _T( "\\\\.\\%s" ),
            ARRAYOFCONST( ( ExtractFileName( SerialPortName ) ) )
        )
    );

    RTUProto.SetCommSpeed( SerialPortSpeed );
    RTUProto.SetCommParity( SerialPortParity );
    RTUProto.SetCommBits( SerialPortBits );
    RTUProto.SetCommStopBits( SerialPortStopBits );

    RTUProto.CancelTXEcho = SerialPortCancelTXEcho;
}
//---------------------------------------------------------------------------

void TfrmMain::ApplyTCPIPProtoParams( ModbusProtocol& Proto ) const
{
    Modbus::Master::TCPIPProtocol& TCPProto =
        dynamic_cast<Modbus::Master::TCPIPProtocol&>( Proto );
    TCPProto.SetHost( TCPIPHost );
    TCPProto.SetPort( TCPIPPort );
}
//---------------------------------------------------------------------------

void TfrmMain::ApplyDummyProtoParams( ModbusProtocol& Proto ) const
{
}
//---------------------------------------------------------------------------

int TfrmMain::GetSlaveID() const
{
    int const Ret = edtSlaveId->Text.ToInt();
    if ( Ret < 0 || Ret > 255 ) {
        throw ERangeError( _T( "Slave ID value is out of range" ) );
    }
    return Ret;
}
//---------------------------------------------------------------------------

void TfrmMain::SetSlaveID( int Val )
{
    edtSlaveId->Text = min( 255, max( 0, Val ) );
}
//---------------------------------------------------------------------------

int TfrmMain::GetTransactionID() const
{
    return ParseWord( edtTransactionID->Text );
}
//---------------------------------------------------------------------------

void TfrmMain::SetTransactionID( int Val )
{
    edtTransactionID->Text = min( 65535, max( 0, Val ) );
}
//---------------------------------------------------------------------------

bool TfrmMain::GetAutoIncTransactionID() const
{
    return cboxAutoIncTransactionID->Checked;
}
//---------------------------------------------------------------------------

void TfrmMain::SetAutoIncTransactionID( bool Val )
{
    cboxAutoIncTransactionID->Checked = Val;
}
//---------------------------------------------------------------------------

String TfrmMain::GetTCPIPHost() const
{
    return Trim( edtTCPIPHost->Text );
}
//---------------------------------------------------------------------------

void TfrmMain::SetTCPIPHost( String Val )
{
    edtTCPIPHost->Text = Trim( Val );
}
//---------------------------------------------------------------------------

int TfrmMain::GetTCPIPPort() const
{
    int const Port = edtTCPIPPort->Text.ToInt();
    if ( Port < 0 || Port > 65535 ) {
        throw ERangeError( _T( "Port value is out of range" ) );
    }
    return Port;
}
//---------------------------------------------------------------------------

void TfrmMain::SetTCPIPPort( int Val )
{
    edtTCPIPPort->Text = min( max( Val, 0 ), 65535 );
}
//---------------------------------------------------------------------------

bool TfrmMain::IsConnectionActive() const
{
    return modbusProto_.get() && modbusProto_->IsConnected();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::EnableIfConnectionIsClose(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = !IsConnectionActive();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::EnableIfConnectionIsOpen(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = IsConnectionActive();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ApplicationEvents1Idle(TObject *Sender, bool &Done)
{
    bool const Enabled = !IsConnectionActive();
    pgctrlProtocolSettings->Enabled = Enabled;
    comboboxProtocol->Enabled = Enabled;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ActionManager1Execute(TBasicAction *Action, bool &Handled)

{
    try {
        if ( TNotifyEvent Evt = Action->OnExecute ) {
            Evt( Action );
        }
    }
    catch ( Modbus::EBaseException const & E ) {
        LogMessage(
            _T( "Modbus exception: %s\n" ), ARRAYOFCONST( ( E.Message ) ), clRed
        );
    }
    catch ( Exception const & E ) {
        LogException( E );
    }
    catch ( std::exception const & e ) {
        LogStdException( e );
    }
    catch ( ... ) {
        LogUnknownException();
    }
    Handled = true;
}
//---------------------------------------------------------------------------

void TfrmMain::DisableAll()
{
    actGareEnb1_5->Checked = false;
    actGareEnb6_10->Checked = false;
    if ( IsConnectionActive() ) {
        Sagome1_5_Out = 0;
        Sagome6_10_Out = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actOpenExecute(TObject *Sender)
{
    portaChiusa_ = DefaultPortaChiusa;
    modbusProto_ = CreateProtocol();
    LogMessage(
        _T( "Open %s%s%s\n" ),
        ARRAYOFCONST( (
            modbusProto_->GetProtocolName()
          , modbusProto_->GetProtocolParamsStr().IsEmpty ? _T( "" ) : _T( " on " )
          , modbusProto_->GetProtocolParamsStr()
        ) )
    );
    modbusProto_->Open();
    SetStopwatchColor( clGray );
    UpdateStopwatch( TDateTime{} );
    DisableAll();
    tmrReadStatusPorta->Enabled = true;
}
//---------------------------------------------------------------------------

void TfrmMain::Close()
{
    if ( modbusProto_ ) {
        LogMessage(
            _T( "Close %s%s%s\n" ),
            ARRAYOFCONST( (
                modbusProto_->GetProtocolName()
              , modbusProto_->GetProtocolParamsStr().IsEmpty ? _T( "" ) : _T( " on " )
              , modbusProto_->GetProtocolParamsStr()
            ) )
        );
    }

    tmrReadStatusPorta->Enabled = false;
    tmrGare->Enabled = false;

    try {
        DisableAll();
    }
    catch ( ... ) {
    }

    waveIn_.reset();
    if ( modbusProto_ ) {
        modbusProto_->Close();
        modbusProto_.reset();
    }
    SetStopwatchColor( clGray );
    UpdateStopwatch( TDateTime{} );
    portaChiusa_ = DefaultPortaChiusa;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actCloseExecute(TObject *Sender)
{
    StopGara();
    Close();
}
//---------------------------------------------------------------------------

int TfrmMain::GetFnIdx() const
{
    return frmeModbusFunctions1->FnIdx;
}
//---------------------------------------------------------------------------

void TfrmMain::SetFnIdx( int Val )
{
    frmeModbusFunctions1->FnIdx = Val;
}
//---------------------------------------------------------------------------

Modbus::RegAddrType TfrmMain::GetReadHoldingRegistersAddr() const
{
    return frmeModbusFunctions1->ReadHoldingRegistersAddr;
}
//---------------------------------------------------------------------------

void TfrmMain::SetReadHoldingRegistersAddr( Modbus::RegAddrType Val )
{
    return frmeModbusFunctions1->ReadHoldingRegistersAddr = Val;
}
//---------------------------------------------------------------------------

Modbus::RegCountType TfrmMain::GetReadHoldingRegistersPtCnt() const
{
    return frmeModbusFunctions1->ReadHoldingRegistersPtCnt;
}
//---------------------------------------------------------------------------

void TfrmMain::SetReadHoldingRegistersPtCnt( Modbus::RegCountType Val )
{
    frmeModbusFunctions1->ReadHoldingRegistersPtCnt = Val;
}
//---------------------------------------------------------------------------

Modbus::RegAddrType TfrmMain::GetReadInputRegistersAddr() const
{
    return frmeModbusFunctions1->ReadInputRegistersAddr;
}
//---------------------------------------------------------------------------

void TfrmMain::SetReadInputRegistersAddr( Modbus::RegAddrType Val )
{
    frmeModbusFunctions1->ReadInputRegistersAddr = Val;
}
//---------------------------------------------------------------------------

Modbus::RegCountType TfrmMain::GetReadInputRegistersPtCnt() const
{
    return frmeModbusFunctions1->ReadInputRegistersPtCnt;
}
//---------------------------------------------------------------------------

void TfrmMain::SetReadInputRegistersPtCnt( Modbus::RegCountType Val )
{
    frmeModbusFunctions1->ReadInputRegistersPtCnt = Val;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actFnReadHoldingRegistersExecute(TObject *Sender)
{
    auto const Addr = ReadHoldingRegistersAddr;
    vector<Modbus::RegDataType> Data( ReadHoldingRegistersPtCnt );

    LogMessage(
        _T( "Read Holding Regs: slave=%d, trns_id=%d, @%d, cnt=%d\n" ),
        ARRAYOFCONST( ( SlaveID, TransactionID, Addr, Data.size() ) )
    );

    ModbusContext Context( SlaveID, TransactionID );
    if ( AutoIncTransactionID ) {
        TransactionID = TransactionID + 1;
    }
    ReadHoldingRegisters( Context, Addr, Data.size(), &Data[0] );

    LogMessage(
        _T( "Reply: %s\n" ), ARRAYOFCONST( ( WordsToString( Data ) ) ), clGreen
    );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actFnReadInputRegistersExecute(TObject *Sender)
{
    auto const Addr = ReadInputRegistersAddr;
    vector<Modbus::RegDataType> Data( ReadInputRegistersPtCnt );

    LogMessage(
        _T( "Read Input Regs: slave=%d, trns_id=%d, @%d, cnt=%d\n" ),
        ARRAYOFCONST( ( SlaveID, TransactionID, Addr, Data.size() ) )
    );

    ModbusContext Context( SlaveID, TransactionID );
    if ( AutoIncTransactionID ) {
        TransactionID = TransactionID + 1;
    }
    ReadInputRegisters( Context, Addr, Data.size(), &Data[0] );

    LogMessage(
        _T( "Reply: %s\n" ), ARRAYOFCONST( ( WordsToString( Data ) ) ), clGreen
    );
}
//---------------------------------------------------------------------------

Modbus::RegAddrType TfrmMain::GetPresetSingleRegisterAddr() const
{
    return frmeModbusFunctions1->PresetSingleRegisterAddr;
}
//---------------------------------------------------------------------------

void TfrmMain::SetPresetSingleRegisterAddr( Modbus::RegAddrType Val )
{
    frmeModbusFunctions1->PresetSingleRegisterAddr = Val;
}
//---------------------------------------------------------------------------

Modbus::RegDataType TfrmMain::GetPresetSingleRegisterValue() const
{
    return frmeModbusFunctions1->PresetSingleRegisterValue;
}
//---------------------------------------------------------------------------

void TfrmMain::SetPresetSingleRegisterValue( Modbus::RegDataType Val )
{
    frmeModbusFunctions1->PresetSingleRegisterValue = Val;
}
//---------------------------------------------------------------------------

bool TfrmMain::GetPresetSingleRegisterPulsed() const
{
    return frmeModbusFunctions1->PresetSingleRegisterPulsed;
}
//---------------------------------------------------------------------------

void TfrmMain::SetPresetSingleRegisterPulsed( bool Val )
{
    frmeModbusFunctions1->PresetSingleRegisterPulsed = Val;
}
//---------------------------------------------------------------------------

uint32_t TfrmMain::GetPresetSingleRegisterPulseTime() const
{
    return frmeModbusFunctions1->PresetSingleRegisterPulseTime;
}
//---------------------------------------------------------------------------

void TfrmMain::SetPresetSingleRegisterPulseTime( uint32_t Val )
{
    frmeModbusFunctions1->PresetSingleRegisterPulseTime = Val;
}
//---------------------------------------------------------------------------

bool TfrmMain::GetPresetMultipleRegisterPulsed() const
{
    return frmeModbusFunctions1->PresetMultipleRegisterPulsed;
}
//---------------------------------------------------------------------------

void TfrmMain::SetPresetMultipleRegisterPulsed( bool Val )
{
    frmeModbusFunctions1->PresetMultipleRegisterPulsed = Val;
}
//---------------------------------------------------------------------------

uint32_t TfrmMain::GetPresetMultipleRegisterPulseTime() const
{
    return frmeModbusFunctions1->PresetMultipleRegisterPulseTime;
}
//---------------------------------------------------------------------------

void TfrmMain::SetPresetMultipleRegisterPulseTime( uint32_t Val )
{
    frmeModbusFunctions1->PresetMultipleRegisterPulseTime = Val;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actFnPresetSingleRegisterExecute(TObject *Sender)
{
    auto const Addr = PresetSingleRegisterAddr;
    auto const Value = PresetSingleRegisterValue;

    LogMessage(
        _T( "Preset Single Reg: slave=%d, trns_id=%d, @%d, value=%d\n" ),
        ARRAYOFCONST( ( SlaveID, TransactionID, Addr, Value ) )
    );

    ModbusContext Context( SlaveID, TransactionID );
    if ( AutoIncTransactionID ) {
        TransactionID = TransactionID + 1;
    }
    if ( PresetSingleRegisterPulsed ) {
        TCursorManager CurMngr;
        auto const TimeMs = PresetSingleRegisterPulseTime;
        Modbus::RegDataType OldVal{};
        ReadHoldingRegisters( Context, Addr, 1, &OldVal );
        PresetSingleRegister( Context, Addr, Value );
        ::Sleep( TimeMs );
        PresetSingleRegister( Context, Addr, OldVal );

    }
    else {
        PresetSingleRegister( Context, Addr, Value );
    }
}
//---------------------------------------------------------------------------

Modbus::RegAddrType TfrmMain::GetPresetMultipleRegistersAddr() const
{
    return frmeModbusFunctions1->PresetMultipleRegistersAddr;
}
//---------------------------------------------------------------------------

void TfrmMain::SetPresetMultipleRegistersAddr( Modbus::RegAddrType Val )
{
    frmeModbusFunctions1->PresetMultipleRegistersAddr = Val;
}
//---------------------------------------------------------------------------

String TfrmMain::GetPresetMultipleRegistersData() const
{
    return frmeModbusFunctions1->PresetMultipleRegistersData;
}
//---------------------------------------------------------------------------

void TfrmMain::SetPresetMultipleRegistersData( String Val )
{
    frmeModbusFunctions1->PresetMultipleRegistersData = Trim( Val );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actFnPresetMultipleRegistersExecute(TObject *Sender)
{
    Modbus::RegAddrType Addr = PresetMultipleRegistersAddr;
    vector<Modbus::RegDataType> Data;

    frmeModbusFunctions1->CopyPresetMultipleRegistersData( back_inserter( Data ) );

    LogMessage(
        _T( "Preset Multiple Regs: slave=%d, trns_id=%d, @%d, cnt=%d\n" ),
        ARRAYOFCONST( ( SlaveID, TransactionID, Addr, Data.size() ) )
    );

    ModbusContext Context( SlaveID, TransactionID );
    if ( AutoIncTransactionID ) {
        TransactionID = TransactionID + 1;
    }

    if ( PresetMultipleRegisterPulsed ) {
        TCursorManager CurMngr;
        auto const TimeMs = PresetMultipleRegisterPulseTime;
        vector<Modbus::RegDataType> OldData( Data.size() );

        ReadHoldingRegisters( Context, Addr, Data.size(), &OldData[0] );
        PresetMultipleRegisters( Context, Addr, Data.size(), &Data[0] );
        ::Sleep( TimeMs );
        PresetMultipleRegisters( Context, Addr, Data.size(), &OldData[0] );
    }
    else {
        PresetMultipleRegisters( Context, Addr, Data.size(), &Data[0] );
    }

    LogMessage(
        _T( "Sent: %s\n" ), ARRAYOFCONST( ( WordsToString( Data ) ) ), clGreen
    );
}
//---------------------------------------------------------------------------

Modbus::RegDataType TfrmMain::GetSagome1_5_Out() const
{
    return sagome1_5_out_;
}
//---------------------------------------------------------------------------

Modbus::RegDataType TfrmMain::GetSagome6_10_Out() const
{
    return sagome6_10_out_;
}
//---------------------------------------------------------------------------

void TfrmMain::SetSagome1_5_Out( Modbus::RegDataType Val )
{
    if ( sagome1_5_out_ != Val ) {
        sagome1_5_out_ = Val;
        PresetSingleRegister( ContextSx, 19, Val );
    }
    ::PostMessage( Handle, WM_USER_REPAINT_LED_1_5, 0, 0 );
}
//---------------------------------------------------------------------------

void TfrmMain::SetSagome6_10_Out( Modbus::RegDataType Val )
{
    if ( sagome6_10_out_ != Val ) {
        sagome6_10_out_ = Val;
        PresetSingleRegister( ContextDx, 19, Val );
    }
    ::PostMessage( Handle, WM_USER_REPAINT_LED_6_10, 0, 0 );
}
//---------------------------------------------------------------------------

void TfrmMain::UpdateOuts( Modbus::RegDataType Val )
{
    Modbus::RegDataType const Sagome1_5 = Sagome1_5_Out;
    Modbus::RegDataType const Sagome6_10 = Sagome6_10_Out;
    Val &= 0x7F;
    Sagome6_10_Out = ( Sagome6_10 & 0x80 ) | Val;
    Sagome1_5_Out = ( Sagome1_5 & 0x80 ) | Val;
}
//---------------------------------------------------------------------------

class AtomicFlagMngr {
public:
    AtomicFlagMngr( std::atomic<bool>& Flag )
        : flag_( Flag ) { flag_ = true; }
    ~AtomicFlagMngr() { flag_ = false; }
    bool GetFlag() const { return flag_; }
    AtomicFlagMngr( AtomicFlagMngr const & ) = delete;
    AtomicFlagMngr& operator=( AtomicFlagMngr const & ) = delete;
    AtomicFlagMngr( AtomicFlagMngr&& ) = default;
    AtomicFlagMngr& operator=( AtomicFlagMngr&& ) = default;
private:
    std::atomic<bool>& flag_;
};

void TfrmMain::ResetCycle()
{
    tmrReadStatusPorta->Enabled = false;

    currentTask_ =
        std::async(
            std::launch::async,
            [this]() {
                AtomicFlagMngr Mngr( taskRunning_ );
                try {
                    UpdateOuts( 0x00 );
                    ::Sleep( 1000 );
                    UpdateOuts( 0x20 );
                    ::Sleep( 1500 );
                    UpdateOuts( 0x00 );
                    ::Sleep( 1000 );
                    UpdateOuts( 0x1F );
                    ::Sleep( 1500 );
                    UpdateOuts( 0x00 );
                    ::Sleep( 2000 );
                    UpdateOuts( 0x40 );
                    UpdateOuts( 0x60 );
                    ::Sleep( 750 );
                    UpdateOuts( 0x00 );
                    ::PostMessage( Handle, WM_USER + 101, 0, 0 );
                }
                catch ( Exception const & E ) {
                    ::PostMessage(
                        Handle, WM_USER_LOG_EXCEPTION_MSG,
                        reinterpret_cast<UINT_PTR>( new String( E.Message ) ),
                        0
                    );
                }
                catch ( std::exception const & e ) {
                    ::PostMessage(
                        Handle, WM_USER_LOG_EXCEPTION_MSG,
                        reinterpret_cast<UINT_PTR>( new String( e.what() ) ),
                        0
                    );
                }
                catch ( ... ) {
                    ::PostMessage( Handle, WM_USER_LOG_EXCEPTION_MSG, 0, 0 );
                }
            }
        );
}
//---------------------------------------------------------------------------

void TfrmMain::Apertura()
{
    currentTask_ =
        std::async(
            std::launch::async,
            [&]() {
                AtomicFlagMngr Mngr( taskRunning_ );
                try {
                    UpdateOuts( 0x1F );
                    ::Sleep( 500 );
                    UpdateOuts( 0x00 );
                    ::PostMessage( Handle, WM_USER_RESTART_STATUS_PORTA, 0, 0 );
                }
                catch ( Exception const & E ) {
                    ::PostMessage(
                        Handle, WM_USER_LOG_EXCEPTION_MSG,
                        reinterpret_cast<UINT_PTR>( new String( E.Message ) ),
                        0
                    );
                }
                catch ( std::exception const & e ) {
                    ::PostMessage(
                        Handle, WM_USER_LOG_EXCEPTION_MSG,
                        reinterpret_cast<UINT_PTR>( new String( e.what() ) ),
                        0
                    );
                }
                catch ( ... ) {
                    ::PostMessage( Handle, WM_USER_LOG_EXCEPTION_MSG, 0, 0 );
                }
            }
        );
}
//---------------------------------------------------------------------------

void TfrmMain::Chiusura()
{
//    WaitTask();

    currentTask_ =
        std::async(
            std::launch::async,
            [&]() {
                AtomicFlagMngr Mngr( taskRunning_ );

                try {
                    UpdateOuts( 0x40 );
                    UpdateOuts( 0x60 );
                    ::Sleep( 500 );
                    UpdateOuts( 0x00 );
                    ::PostMessage( Handle, WM_USER_RESTART_STATUS_PORTA, 0, 0 );
                }
                catch ( Exception const & E ) {
                    ::PostMessage(
                        Handle, WM_USER_LOG_EXCEPTION_MSG,
                        reinterpret_cast<UINT_PTR>( new String( E.Message ) ),
                        0
                    );
                }
                catch ( std::exception const & e ) {
                    ::PostMessage(
                        Handle, WM_USER_LOG_EXCEPTION_MSG,
                        reinterpret_cast<UINT_PTR>( new String( e.what() ) ),
                        0
                    );
                }
                catch ( ... ) {
                    ::PostMessage( Handle, WM_USER_LOG_EXCEPTION_MSG, 0, 0 );
                }
            }
        );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareResetCycleExecute(TObject *Sender)
{
    TCursorManager CurMngr;
    SetStopwatchColor( clGray );
    UpdateStopwatch( TDateTime{} );
    lblStopwatch->Refresh();
    tmrReadStatusPorta->Enabled = false;
    ResetCycle();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::EnableIfConnectionIsOpenAndEnabled(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = !taskRunning_ &&
                  IsConnectionActive() &&
                  ( IgnoreDoor || portaChiusa_ ) &&
                  ( actGareEnb1_5->Checked || actGareEnb6_10->Checked ) &&
                  !tmrGare->Enabled;
}
//---------------------------------------------------------------------------

/*
HRESULT GetSourceDuration(IMFMediaSource *pSource, MFTIME *pDuration)
{
    *pDuration = 0;

    IMFPresentationDescriptor *pPD = NULL;

    HRESULT hr = pSource->CreatePresentationDescriptor(&pPD);
    if (SUCCEEDED(hr))
    {
        hr = pPD->GetUINT64(MF_PD_DURATION, (UINT64*)pDuration);
        pPD->Release();
    }
    return hr;
}
*/

TDateTime TfrmMain::EseguiComando( Cmd const& Comando )
{
    switch ( Comando.GetCmd() ) {
        case CmdType::None:
            LogMessage( Format( _T( "%s\n" ), ARRAYOFCONST( ( Comando.GetMessage() ) ) ) );
            break;
        case CmdType::Apertura:
            LogMessage( Format( _T( "%s\n" ), ARRAYOFCONST( ( Comando.GetMessage() ) ) ) );
            Apertura();
            break;
        case CmdType::Chiusura:
            LogMessage( Format( _T( "%s\n" ), ARRAYOFCONST( ( Comando.GetMessage() ) ) ) );
            Chiusura();
            break;
        case CmdType::MessaggioAsincrono:
            LogMessage( Format( _T( "%s\n" ), ARRAYOFCONST( ( Comando.GetMessage() ) ) ), clWebOrange );
            {
                auto AudioFile = TPath::Combine( SoundFolder, Comando.GetAuxData() );
                if ( FileExists( AudioFile ) ) {
                    ::PlaySound( AudioFile.c_str(), 0, SND_FILENAME | SND_ASYNC );
                }
                else {
                    LogMessage(
                        Format(
                            _T( "Audio file %s doesn't exists\n" ),
                            ARRAYOFCONST( ( AudioFile ) )
                        ),
                        clRed
                    );
                }
            }
            break;
        case CmdType::MessaggioSincrono:
            LogMessage( Format( _T( "%s\n" ), ARRAYOFCONST( ( Comando.GetMessage() ) ) ), clGreen );
            {
                auto AudioFile = TPath::Combine( SoundFolder, Comando.GetAuxData() );
                if ( FileExists( AudioFile ) ) {
                    try {
                        auto const Duration = GetMediaDuration( AudioFile );
                        ::PlaySound( AudioFile.c_str(), 0, SND_FILENAME | SND_ASYNC );
                        return IncSecond( Now(), Duration );
                    }
                    catch ( Exception const & E ) {
                        LogException( E );
                    }
                    catch ( std::exception const & e ) {
                        LogStdException( e );
                    }
                    catch ( ... ) {
                        LogUnknownException();
                    }
                    return {};
                }
                else {
                    LogMessage(
                        Format(
                            _T( "Audio file %s doesn't exists\n" ),
                            ARRAYOFCONST( ( AudioFile ) )
                        ),
                        clRed
                    );
                }
            }
        case CmdType::StartAudioSampling:
            waveIn_.reset(
                new WaveInCO(
                    WaveInId,
                    [this]( WaveIn::BufferCont const & WaveData ) {
                        WaveDataEvtHndlr( WaveData );
                    }
                )
            );
            peaksAbsTimePoint_.clear();
            peaksAbsTimePoint_.reserve( 32 );
            waveIn_->Start();
            detectCnt_ = 0;
            startListeningTimePoint_ = peakDetInhTime_= Now();
            LogMessage( _T( "Listening...\n" ), clGray );
            break;
        case CmdType::StopAudioSampling:
            waveIn_.reset();
            LogMessage( _T( "End listening!\n" ), clGray );
            break;
        default:
            break;
    }
    return IncSecond( Now(), Comando.GetTime() );

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tmrGareTimer(TObject *Sender)
{
    auto NowTime = Now();
    if ( NowTime > deadLine_ ) {
        if ( tmrGare->Tag < stepCount_ ) {
            deadLine_ = EseguiComando( cmds_[tmrGare->Tag] );
            tmrGare->Tag = tmrGare->Tag + 1;
        }
        else {
            tmrGare->Enabled = false;
            NowTime = deadLine_;
            SetStopwatchColor( clGreen );
            LogMessage( _T( "Fine\r\n" ) );
            tmrReadStatusPorta->Enabled = true;
        }
    }
//    auto ToTarget = deadLine_ - NowTime;
//    UpdateStopwatch( ToTarget );
    UpdateStopwatch( deadLine_ - NowTime );
}
//---------------------------------------------------------------------------

void TfrmMain::SetStopwatchColor( TColor Val )
{
    lblStopwatch->Font->Color = Val;
}
//---------------------------------------------------------------------------

void TfrmMain::UpdateStopwatch( TDateTime Val )
{
    lblStopwatch->Caption =
        Val.FormatString( _T( "nn:ss:zzz" ) ).SubString( 1, 7 );
}
//---------------------------------------------------------------------------

void TfrmMain::StartGara( Cmd const * Cmds, size_t CmdsCnt )
{
    tmrReadStatusPorta->Enabled = false;
    tmrGare->Enabled = false;

    Application->ProcessMessages();

    SetStopwatchColor( clLime );
    tmrGare->Tag = 0;
    cmds_ = &Cmds[0];
    stepCount_ = CmdsCnt;
    deadLine_ = TDateTime{};
    tmrGare->Enabled = true;
}
//---------------------------------------------------------------------------

void TfrmMain::StopGara()
{
    waveIn_.reset();
    if ( tmrGare->Enabled ) {
        tmrGare->Enabled = false;
        LogMessage( _T( "FERMATO\r\n" ), clPurple );
        SetStopwatchColor( clRed );
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareStopExecute(TObject *Sender)
{
    StopGara();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::EnabledIfTrialIsRunning(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = IsConnectionActive() && tmrGare->Enabled;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::EnabledIfTrialIsNotRunning(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = !IsConnectionActive() || !tmrGare->Enabled;
}
//---------------------------------------------------------------------------

static constexpr uint16_t Time60sec =
#if defined( _DEBUG )
    6
#else
    60
#endif
;
static constexpr uint16_t AttesaChiusura = 3;
static constexpr uint16_t AttenzioneAttesa = 2;

static constexpr LPCTSTR ApertoSubitoTxt = _T( "Aperto subito" );
static constexpr LPCTSTR Attesa60SecTxt = _T( "Attesa 60 sec" );
static constexpr LPCTSTR AttenzioneTxt = _T( "Attenzione" );
static constexpr LPCTSTR AttenzioneVoice = _T( "Attenzione.wav" );
static constexpr LPCTSTR ChiusoTxt = _T( "Chiuso" );
static constexpr LPCTSTR ScaricareTxt = _T( "Stop. Scaricare. Armi sul banco." );
static constexpr LPCTSTR ScaricareVoice = _T( "Stop_Scaricare_1.wav" );

void __fastcall TfrmMain::actGarePrimaPGCMiratoStartExecute(TObject *Sender)
{
    static constexpr
    array<Cmd,8> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prima serie di gara di tiro mirato in 300 secondi, caricare." ),
                _T( "PGC_Mirato_10.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::Apertura, 300,   _T( "Aperto 300 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prima serie di gara PGC Mirato\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProssimaPGCMiratoStartExecute(TObject *Sender)
{
    static constexpr
    array<Cmd,8> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prossima serie di gara di tiro mirato in 300 secondi, caricare." ),
                _T( "PGC_Mirato_11.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::Apertura, 300,   _T( "Aperto 300 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio serie di gara successiva PGC Mirato\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProvaPGCMiratoStartExecute(TObject *Sender)
{
    static constexpr
    array<Cmd,8> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la serie di prova di tiro mirato in 300 secondi, caricare." ),
                _T( "PGC_Mirato_9.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::Apertura, 300,   _T( "Aperto 300 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prova PGC Mirato\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProvaPGCCelereStartExecute(TObject *Sender)
{
    static constexpr
    array<Cmd,16> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la serie di prova di tiro celere, caricare." ),
            _T( "PGC_Celere_12.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura, 5, _T( "Chiuso 7 sec (1)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (1)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (2)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (2)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (3)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (3)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (4)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (4)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (5)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (5)" ) },
        { CmdType::Chiusura, AttesaChiusura, ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prova PGC Celere\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGarePrimaPGCCelereStartExecute(TObject *Sender)
{
    static constexpr
    array<Cmd,16> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prima serie di gara di tiro celere, caricare." ),
            _T( "PGC_Celere_13.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura, 5, _T( "Chiuso 7 sec (1)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (1)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (2)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (2)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (3)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (3)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (4)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (4)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (5)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (5)" ) },
        { CmdType::Chiusura, AttesaChiusura, ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prima serie di gara PGC Celere\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProssimaPGCCelereStartExecute(TObject *Sender)
{
    static constexpr
    array<Cmd,16> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prossima serie di gara di tiro celere, caricare." ),
            _T( "PGC_Celere_14.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura, 5, _T( "Chiuso 7 sec (1)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (1)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (2)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (2)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (3)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (3)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (4)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (4)" ) },
        { CmdType::Chiusura, 7, _T( "Chiuso 7 sec (5)" ) },
        { CmdType::Apertura, 3, _T( "Aperto 3 sec (5)" ) },
        { CmdType::Chiusura, AttesaChiusura, ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio serie di gara successiva PGC Celere\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareAperturaExecute(TObject *Sender)
{
    TCursorManager CurMngr;
    tmrReadStatusPorta->Enabled = false;
    Application->ProcessMessages();
    Apertura();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareChiusuraExecute(TObject *Sender)
{
    TCursorManager CurMngr;
    tmrReadStatusPorta->Enabled = false;
    Application->ProcessMessages();
    Chiusura();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareEnb1_5Execute(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Sagome1_5_Out = ( Sagome1_5_Out & 0x7F ) | ( Act.Checked ? 0x80 : 0 );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareEnb6_10Execute(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Sagome6_10_Out = ( Sagome6_10_Out & 0x7F ) | ( Act.Checked ? 0x80 : 0 );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProvaPS150Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,8> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la serie di prova in 150 secondi, caricare." ),
            _T( "PS_150s_2.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::Apertura, 150,   _T( "Aperto 150 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio serie di prova PS 150 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGarePrimaPS150Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,8> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prima serie di gara in 150 secondi, caricare." ),
            _T( "PS_150s_3.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::Apertura, 150,   _T( "Aperto 150 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prima serie di gara PS 150 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProssimaPS150Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,8> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prossima serie di gara in 150 secondi, caricare." ),
            _T( "PS_150s_4.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::Apertura, 150,   _T( "Aperto 150 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prossima serie di gara PS 150 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGarePrimaPS20Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,8> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prima serie di gara in 20 secondi, caricare." ),
            _T( "PS_20s_5.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::Apertura,  20,   _T( "Aperto 20 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prima serie PS 20 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProssimaPS20Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,8> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prossima serie di gara in 20 secondi, caricare." ),
            _T( "PS_20s_6.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::Apertura,  20,   _T( "Aperto 20 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prossima PS 20 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGarePrimaPS10Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,8> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prima serie di gara in 10 secondi, caricare." ),
            _T( "PS_10s_7.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::Apertura,  10,   _T( "Aperto 10 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prina serie PS 10 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProssimaPS10Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,8> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prossima serie di gara in 10 secondi, caricare." ),
            _T( "PS_10s_8.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::Apertura,  10,   _T( "Aperto 10 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prossima serie PS 10 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProvaPA8Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,10> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la serie di prova in 8 secondi, caricare." ),
            _T( "PA_8s_15.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::StartAudioSampling,   0,   nullptr },
        { CmdType::Apertura,   8,   _T( "Aperto 8 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::StopAudioSampling,   0,   nullptr },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio serie di prova PA 8 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGarePrimaPA8Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,10> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prima serie di gara in 8 secondi, caricare." ),
            _T( "PA_8s_16.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::StartAudioSampling,   0,   nullptr },
        { CmdType::Apertura,   8,   _T( "Aperto 8 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::StopAudioSampling,   0,   nullptr },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prima serie di gara PA 8 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProssimaPA8Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,10> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prossima serie di gara in 8 secondi, caricare." ),
            _T( "PA_8s_17.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::StartAudioSampling,   0,   nullptr },
        { CmdType::Apertura,   8,   _T( "Aperto 8 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::StopAudioSampling,   0,   nullptr },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prossima serie di gara PA 8 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGarePrimaPA6Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,10> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prima serie di gara in 6 secondi, caricare." ),
            _T( "PA_6s_18.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::StartAudioSampling,   0,   nullptr },
        { CmdType::Apertura,   6,   _T( "Aperto 6 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::StopAudioSampling,   0,   nullptr },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prima serie PA 6 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProssimaPA6Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,10> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prossima serie di gara in 6 secondi, caricare." ),
            _T( "PA_6s_19.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::StartAudioSampling,   0,   nullptr },
        { CmdType::Apertura,   6,   _T( "Aperto 6 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::StopAudioSampling,   0,   nullptr },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prossima serie PA 6 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGarePrimaPA4Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,10> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prima serie di gara in 4 secondi, caricare." ),
            _T( "PA_4s_20.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::StartAudioSampling,   0,   nullptr },
        { CmdType::Apertura,   4,   _T( "Aperto 4 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::StopAudioSampling,   0,   nullptr },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prima serie PA 4 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actGareProssimaPA4Execute(TObject *Sender)
{
    static constexpr
    array<Cmd,10> Cmds = { {
        { CmdType::Apertura, 0, ApertoSubitoTxt },
        {
            CmdType::MessaggioSincrono, 0,
            _T( "Per la prossima serie di gara in 4 secondi, caricare." ),
            _T( "PA_4s_21.wav" )
        },
        { CmdType::Apertura, Time60sec, Attesa60SecTxt },
        { CmdType::MessaggioAsincrono, AttenzioneAttesa, AttenzioneTxt, AttenzioneVoice },
        { CmdType::Chiusura,   5,   _T( "Chiuso 7 sec" ) },
        { CmdType::StartAudioSampling,   0,   nullptr },
        { CmdType::Apertura,   4,   _T( "Aperto 4 sec" ) },
        { CmdType::Chiusura,   AttesaChiusura,   ChiusoTxt },
        { CmdType::StopAudioSampling,   0,   nullptr },
        { CmdType::MessaggioSincrono, 0, ScaricareTxt, ScaricareVoice },
    } };

    StartGara( &Cmds[0], Cmds.size() );
    LogMessage( _T( "Inizio prossima serie PA 4 secondi\r\n" ), clBlue );
}
//---------------------------------------------------------------------------

void TfrmMain::ReadHoldingRegisters( Modbus::Context const & Context,
                                     Modbus::RegAddrType StartAddr,
                                     Modbus::RegCountType PointCount,
                                     Modbus::RegDataType* Data )
{
    unique_lock<mutex> lock( modbusProtoMutex_ );
    modbusProto_->ReadHoldingRegisters( Context, StartAddr, PointCount, Data );
}
//---------------------------------------------------------------------------

void TfrmMain::ReadInputRegisters( Modbus::Context const & Context,
                                   Modbus::RegAddrType StartAddr,
                                   Modbus::RegCountType PointCount,
                                   Modbus::RegDataType* Data )
{
    unique_lock<mutex> lock( modbusProtoMutex_ );
    modbusProto_->ReadInputRegisters( Context, StartAddr, PointCount, Data );
}
//---------------------------------------------------------------------------

void TfrmMain::PresetSingleRegister( Modbus::Context const & Context,
                                     Modbus::RegAddrType Addr,
                                     Modbus::RegDataType Data )
{
    unique_lock<mutex> lock( modbusProtoMutex_ );
    modbusProto_->PresetSingleRegister( Context, Addr, Data );
}
//---------------------------------------------------------------------------

void TfrmMain::PresetMultipleRegisters( Modbus::Context const & Context,
                                        Modbus::RegAddrType StartAddr,
                                        Modbus::RegCountType PointCount,
                                        const Modbus::RegDataType* Data )
{
    unique_lock<mutex> lock( modbusProtoMutex_ );
    modbusProto_->PresetMultipleRegisters( Context, StartAddr, PointCount, Data );
}
//---------------------------------------------------------------------------

void TfrmMain::ReadStatusPorta()
{
    Modbus::RegDataType Data { 0xFFFF };

    if ( IsConnectionActive() ) {
        ReadHoldingRegisters( ContextDx, 0, 1, &Data );
    }
    portaChiusa_ = Data;
    //uff
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tmrReadStatusPortaTimer(TObject *Sender)
{
    if( !PollingTimerDisabled ) {
        try {
            if ( IsConnectionActive() && !tmrGare->Enabled ) {
                ReadStatusPorta();
            }
        }
        catch ( Exception const & E ) {
            Close();
            LogException( E );
        }
        catch ( std::exception const & e ) {
            Close();
            LogStdException( e );
        }
        catch ( ... ) {
            Close();
            LogUnknownException();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::PaintBox1_5Paint(TObject *Sender)
{
    TPaintBox& PaintBox = static_cast<TPaintBox&>( *Sender );

    static Led Led{ 12 };

    auto const Gap = ( PaintBox.ClientWidth - Led.GetSize() * 8 ) / 8;
    auto const HalfGap = Gap / 2;
    auto const Delta = Gap + Led.GetSize();

    Modbus::RegDataType Out {};
    switch ( PaintBox.Tag ) {
        case 0:
            Out = sagome1_5_out_;
            break;
        case 1:
            Out = sagome6_10_out_;
            break;
    }

    Gdiplus::Graphics g( PaintBox.Canvas->Handle );
    g.SetSmoothingMode( Gdiplus::SmoothingModeAntiAlias );
    for ( size_t BitNo = 0 ; BitNo < 8 ; ++BitNo ) {
        Led.Draw(
            g,
            ( Out & ( 1 << BitNo ) ) ? Gdiplus::Color::Lime : Gdiplus::Color::Black,
            Gdiplus::PointF( HalfGap + Delta * BitNo, 0.0F )
        );
    }
}
//---------------------------------------------------------------------------

int TfrmMain::GetWaveInId() const
{
    return comboboxAudioSources->ItemIndex;
}
//---------------------------------------------------------------------------

String TfrmMain::GetWaveInDevice() const
{
    return comboboxAudioSources->Items->Strings[comboboxAudioSources->ItemIndex];
}
//---------------------------------------------------------------------------

void TfrmMain::SetWaveInDevice( String Val )
{
    comboboxAudioSources->ItemIndex =
        comboboxAudioSources->Items->IndexOf( Val );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::WaveDataEvtHndlr( WaveIn::BufferCont const & WaveData )
{
    ::PostMessage(
        Handle,
        WM_USER_WAVE_DATA,
        //reinterpret_cast<WPARAM>( new WaveIn::BufferCont( WaveData ) ),
        reinterpret_cast<WPARAM>( new WaveDataTimePoint( WaveData, Now() ) ),
        0
    );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pboxSpectrogramPaint(TObject *Sender)
{
    auto& PaintBox = static_cast<TPaintBox&>( *Sender );
    auto& PBoxCanvas = *PaintBox.Canvas;

    unique_lock<mutex> lock( spectrogramMutex_ );

    PBoxCanvas.Draw( 0, 0, spectrogramBmps_[0].get() );

    auto XLo = CutMarkerXCoordFromFreq( CutLoFreq );
    auto XHi = CutMarkerXCoordFromFreq( CutHiFreq );

    Gdiplus::Graphics g( PBoxCanvas.Handle );
    g.SetSmoothingMode( Gdiplus::SmoothingModeAntiAlias );
    Gdiplus::Pen MarkerPen( Gdiplus::Color( 0xA0, 0x80, 0xFF, 0xFF ) );
    MarkerPen.SetDashStyle( Gdiplus::DashStyle::DashStyleDot );
    g.DrawLine( &MarkerPen, XLo, 0, XLo, PaintBox.Height );
    g.DrawLine( &MarkerPen, XHi, 0, XHi, PaintBox.Height );

}
//---------------------------------------------------------------------------

void TfrmMain::CreateSpectrogramBmps()
{
//int Idx {};
    for ( auto& Ptr : spectrogramBmps_ ) {
        Ptr.reset( new TBitmap() );
        Ptr->PixelFormat = TPixelFormat::pf24bit;
        //Ptr->Canvas->Brush->Color = Idx ? clRed : clBlack;
        Ptr->Canvas->Brush->Color = clBlack;
        Ptr->SetSize( WaveIn::SampleCount / 2, pboxSpectrogram->ClientHeight );
//++Idx;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ActionManager1Update(TBasicAction *Action, bool &Handled)
{
    comboboxAudioSources->Enabled = !waveIn_;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actWaveStartListeningUpdate(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = !waveIn_ && !tmrGare->Enabled;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actWaveStopListeningUpdate(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = waveIn_ && !tmrGare->Enabled;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actWaveStartListeningExecute(TObject *Sender)
{
    if ( !waveIn_ ) {
        waveIn_.reset(
            new WaveInCO(
                WaveInId,
                [this]( WaveIn::BufferCont const & WaveData ) {
                    WaveDataEvtHndlr( WaveData );
                }
            )
        );
        peaksAbsTimePoint_.clear();
        peaksAbsTimePoint_.reserve( 32 );
        waveIn_->Start();
        detectCnt_ = 0;
        startListeningTimePoint_ = peakDetInhTime_ = Now();
        LogMessage( _T( "Listening...\n" ), clGray );
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actWaveStopListeningExecute(TObject *Sender)
{
    if ( waveIn_ ) {
        waveIn_->Stop();
        waveIn_.reset();
        LogMessage( _T( "End listening!\n" ), clGray );
    }
}
//---------------------------------------------------------------------------

int TfrmMain::GetMainPanelSize() const
{
    return pnlTop->Height;
}
//---------------------------------------------------------------------------

void TfrmMain::SetMainPanelSize( int Val )
{
    pnlTop->Height = Val;
}
//---------------------------------------------------------------------------

int TfrmMain::GetThreshold() const
{
    return cutdBThreshold_;
}
//---------------------------------------------------------------------------

void TfrmMain::SetThreshold( int Val )
{
    Val = ClipThresholdValue( Val );
    if ( cutdBThreshold_ != Val ) {
        cutdBThreshold_ = Val;
        UpdateThresholddBControls();
    }
}
//---------------------------------------------------------------------------

void TfrmMain::UpdateThresholddBControls()
{
    ComputeSpectrogramColorMap();
    auto Bmp =
        CreateSpectrogramGradientBitmap(
            imgSpectrogramGradient->ClientWidth
        );
    imgSpectrogramGradient->Picture->Assign( Bmp.get() );

    UpdateThresholddBDisplayControl();
}
//---------------------------------------------------------------------------

int TfrmMain::ClipThresholdValue( int Val ) const
{
    return max( min( Val, spectrogramThresholdMax_ ), spectrogramThresholdMin_ );
}
//---------------------------------------------------------------------------

void TfrmMain::UpdateThresholddBDisplayControl()
{
    lblThreshold->Caption =
        Format( _T( "%d dB" ), ARRAYOFCONST( ( cutdBThreshold_ ) ) );
    SeriesdBThreshold->BeginUpdate();
    SeriesdBThreshold->YValues->Items[0] = cutdBThreshold_;
    SeriesdBThreshold->YValues->Items[1] = cutdBThreshold_;
    SeriesdBThreshold->EndUpdate();
    chartFreq->Invalidate();
    pboxSpectrogramGradientIndicator->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlSpectrogramResize(TObject *Sender)
{
    CreateSpectrogramBmps();
    lblSpectrogramDuration->Caption =
        Format(
            _T( "↑-%1.1f s" ),
            ARRAYOFCONST( (
                static_cast<const long double>(
                    static_cast<double>( WaveIn::SampleCount ) *
                    pboxSpectrogram->Height /
                    WaveIn::SamplesPerSec
                )
            ) )
        );
    pboxSpectrogram->Invalidate();
}
//---------------------------------------------------------------------------

bool TfrmMain::IgnoreSettings()
{
    bool const ShiftPressed = GetAsyncKeyState( VK_SHIFT ) & 0x8000;
    bool const CtrlPressed = GetAsyncKeyState( VK_CONTROL ) & 0x8000;
    return ShiftPressed && CtrlPressed;
}
//---------------------------------------------------------------------------

TChartSeries& TfrmMain::GetCurrentFreqSeries() const
{
    if ( seriesNo_ & 1 ) {
        return *SeriesFreq1;
    }
    else {
        return *SeriesFreq2;
    }
}
//---------------------------------------------------------------------------

TChartSeries& TfrmMain::GetCurrentTimeSeries() const
{
    if ( seriesNo_ & 1 ) {
        return *SeriesTime1;
    }
    else {
        return *SeriesTime2;
    }
}
//---------------------------------------------------------------------------

//static double A = ( 1.0 + cos( M_PI * 8.0 / 10.0 ) ) / 2.0;
static double A = 1.0;
static double HDPW = 0.5;

//void TfrmMain::HandleUserWaveData( WaveIn::BufferCont* const DataRawPtr )
void TfrmMain::HandleUserWaveData( WaveDataTimePoint* const DataRawPtr )
{
    //if ( unique_ptr<WaveIn::BufferCont> DataPtr{ DataRawPtr } ) {
    if ( unique_ptr<WaveDataTimePoint> DataPtr{ DataRawPtr } ) {
        SignalCont Signal;
        /*
        FFTWContN FFTInWindowed;
        FFTWContN FFTOut;
        FFTWPlan<FFTWContN> FFTPlan( FFTInWindowed, FFTOut );
        */
        FFTWContN FFTInWindowed;
        auto const & Buffer = *DataPtr;
        auto const SampleCount = Buffer.GetWaveData().size();

        for ( decltype( Buffer.GetWaveData().size() ) Idx = 0 ; Idx < SampleCount ; ++Idx ) {
#if 1
            double const SignalPoint = Buffer.GetWaveData()[Idx] / 32768.0 /* / 512.0 */;
#else
  #if 0
            double const SignalPoint =
                sin( 2.0 * M_PI * Idx * 880.0 / 22050.0 ) *  A;

//            A += 0.0001;
  #else
    #if 0
            double const SignalPoint = Idx >= 256 - HDPW && Idx <= 256 + HDPW ? 128.0 : 0.0;
    #else
      #if 0
            double const SignalPoint = Idx & 1 ? -0.707 : 0.707;
      #else
            double const SignalPoint = 0.707;
      #endif
    #endif
  #endif
#endif
            Signal[Idx] = SignalPoint;
            FFTInWindowed[Idx][0] = window_[Idx] * SignalPoint;  // Re
            FFTInWindowed[Idx][1] = 0.0;         // Im
            /*
            double const Window =
                1.0 - cos( 2.0 * M_PI * Idx / SampleCount );
            FFTInWindowed[Idx][0] = Window * SignalPoint;  // Re
            FFTInWindowed[Idx][1] = 0.0;         // Im
            */
        }

        //ApplyWindow( Signal, FFTInWindowed );

        FFTWContN FFTOut;
        FFTWPlan<FFTWContN> FFTPlan( FFTInWindowed, FFTOut );

        fftw_execute( FFTPlan );

        DrawSpectrogramLine( FFTOut );

/*
for ( size_t Idx = 0 ; Idx < WaveIn::SampleCount ; ++Idx ) {
    Signal[Idx] = FFTInWindowed[Idx][0];
}
*/

        UpdateCharts( Signal, FFTOut );

        PeakDetection( FFTOut, Buffer.GetTimePoint() );
    }
}

//---------------------------------------------------------------------------
/*
std::array<double,6> const TfrmMain::windowScaleFactorsEnergy_ = {{
    1.0,   // Uniform
    1.63,  // Hanning
    2.26,  // Flattop
    1.97,  // Blackman
    1.59,  // Hamming
    1.86   // KaiserBessel
}};


double TfrmMain::GetWindowEnergyScalefactor() const
{
    // See: https://tinyurl.com/fftwinfactcorr
    //                 Amplitude    Energy
    // Uniform           1.0         1.0
    // Hanning           2.0         1.63
    // Flattop           4.18        2.26
    // Blackman          2.80        1.97
    // Hamming           1.85        1.59
    // Kaiser-Bessel     2.49        1.86
    return windowScaleFactorsEnergy_[static_cast<size_t>( selectedWindoType_ )];
}
*/
//---------------------------------------------------------------------------

void TfrmMain::ComputeWindow()
{
    switch ( selectedWindoType_ ) {
        case WindowType::Hanning:
            ComputeHanningWindow();
            break;
        case WindowType::Flattop:
            ComputeFlattopWindow();
            break;
        case WindowType::Blackman:
            ComputeBlackmanWindow();
            break;
        case WindowType::Hamming:
            ComputeHammingWindow();
            break;
        case WindowType::KaiserBessel:
            ComputeKaiserBesselWindow();
            break;
        default:
            ComputeUniformWindow();
            break;
    }
}
//---------------------------------------------------------------------------

void TfrmMain::ComputeUniformWindow()
{
    std::fill( begin( window_ ), end( window_ ), 1.0 );
}
//---------------------------------------------------------------------------

void TfrmMain::ComputeHanningWindow()
{
    for ( size_t Idx =  0 ; Idx < WaveIn::SampleCount ; ++Idx ) {
        window_[Idx] =
            1.63 * ( 1.0 - cos( 2.0 * M_PI * Idx / WaveIn::SampleCount ) ) / 2.0;
    }
}
//---------------------------------------------------------------------------

void TfrmMain::ComputeFlattopWindow()
{
    static constexpr double a[5] = {
        0.21557895,
        0.41663158,
        0.277263158,
        0.083578947,
        0.006947368,
    };

    for ( size_t Idx =  0 ; Idx < WaveIn::SampleCount ; ++Idx ) {
        double w = a[0];
        for ( size_t CIdx = 1 ; CIdx < 5 ; ++CIdx ) {
            w += ( ( CIdx & 1 ) ? -1.0 : 1.0 ) * a[CIdx] *
                 cos( 2.0 * CIdx * M_PI * Idx / ( WaveIn::SampleCount - 1 ) );

        }
        window_[Idx] = 2.26 * w;
    }
}
//---------------------------------------------------------------------------
/*


#include <Clipbrd.hpp>

auto SB = make_unique<TStringBuilder>();


        SB->AppendLine( w );
    Clipboard()->AsText = SB->ToString();
*/

void TfrmMain::ComputeBlackmanWindow()
{
}
//---------------------------------------------------------------------------

void TfrmMain::ComputeHammingWindow()
{
}
//---------------------------------------------------------------------------

void TfrmMain::ComputeKaiserBesselWindow()
{

}
//---------------------------------------------------------------------------

/*
void TfrmMain::ApplyWindow( SignalCont const & Signal, FFTWContN& FFTPoints ) const
{
generiamo un array all'inizio, please
    // Hanning
    for ( size_t Idx =  0 ; Idx < WaveIn::SampleCount ; ++Idx ) {
        double const Window =
            ( 1.0 - cos( 2.0 * M_PI * Idx / WaveIn::SampleCount ) ) / 2.0;
        FFTPoints[Idx][0] = Window * Signal[Idx];  // Re
        FFTPoints[Idx][1] = 0,0;  // Im
    }
}
*/
//---------------------------------------------------------------------------

void TfrmMain::ComputeSpectrogramColorMap()
{
    for ( int Idx = 0 ; Idx < 256 ; ++Idx ) {
        auto H = std::fmod( ( static_cast<double>( Idx ) / 256.0 ) * 280.0 + 220.0, 360.0 );
        auto S = 0.7 + 0.3 * sin( ( M_PI * ( Idx / 256.0 ) + M_PI ) / 2.0 );
        auto L = 0.1 + 0.3 * sin( M_PI * ( Idx / 256.0 ) / 2.0 );
        spectrogramColorMap_[Idx] =
            ColorCvt::HSLToRGB( ColorCvt::THSL( H, S, L ) ).ToRGBTRIPLE();
    }
}
//---------------------------------------------------------------------------

std::unique_ptr<TBitmap> TfrmMain::CreateSpectrogramGradientBitmap( int Width ) const
{
    auto Bmp = make_unique<TBitmap>();
    Bmp->PixelFormat = pf24bit;
    TCanvas& C = *Bmp->Canvas;
    Bmp->SetSize( Width, 256 );
    for ( int Y = 0 ; Y < 256 ; ++Y ) {
        auto const & Color = spectrogramColorMap_[Y];
        C.Pen->Color =
            static_cast<TColor>(
                ( static_cast<uint32_t>( Color.rgbtBlue ) << 16 ) |
                ( static_cast<uint32_t>( Color.rgbtGreen ) << 8 ) |
                ( static_cast<uint32_t>( Color.rgbtRed ) )
            );
        C.MoveTo( 0, 255 - Y );
        C.LineTo( Width, 255 - Y );
    }
    return Bmp;
}
//---------------------------------------------------------------------------

void TfrmMain::DrawSpectrogramLine( FFTWContN const & FreqDomainWaveData )
{
    auto& Bmp = *spectrogramBmps_[0];
    auto& NewBmp = *spectrogramBmps_[1];
    auto& NewBmpCanvas = *NewBmp.Canvas;

    NewBmpCanvas.Draw( 0, -1, &Bmp );

    auto const Line = NewBmp.Height - 2;

    auto ScanLine =
        reinterpret_cast<LPRGBTRIPLE>( NewBmp.ScanLine[Line] );

    auto const FFTPointCount = WaveIn::SampleCount;
    auto const Sf = 1.0 / double( FFTPointCount );
    //auto const Sf = GetWindowEnergyScalefactor() / double( FFTPointCount );

    RGBTRIPLE Marker { 255,255,255 };

    for ( int Idx = 0 ; Idx < FFTPointCount / 2 ; ++Idx ) {
        complex<double> DataPoint{
            FreqDomainWaveData[Idx][0], FreqDomainWaveData[Idx][1]
        };
        auto const A = abs( DataPoint ) * Sf * ( Idx ? 2.0 : 1.0 );
        auto const W = 20.0 * log10( max( A, 1e-15 ) );

        BYTE V =
            max(
                min(
                    256.0 * ( W - spectrogramdBFloor ) / -spectrogramdBFloor,
                    255.0
                ),
                0.0
            );

        double const Freq =
            static_cast<double>( WaveIn::SamplesPerSec ) * Idx / FFTPointCount;

        if ( W >= cutdBThreshold_ && Freq >= CutLoFreq && Freq <= CutHiFreq ) {
            ScanLine[Idx] = Marker;
        }
        else {
            ScanLine[Idx] = spectrogramColorMap_[V];
        }
    }

    swap( spectrogramBmps_[0], spectrogramBmps_[1] );

    pboxSpectrogram->Repaint();
    pboxPeaksTimepoint->Repaint();
}
//---------------------------------------------------------------------------

void TfrmMain::UpdateCharts( SignalCont const & TimeDomainWaveData,
                             FFTWContN const & FreqDomainWaveData )
{
    auto& CurrentFreqSeries = GetCurrentFreqSeries();
    CurrentFreqSeries.BeginUpdate();

    auto& CurrentTimeSeries = GetCurrentTimeSeries();
    CurrentTimeSeries.BeginUpdate();


    // Plot the unwindowed time domain signal
    auto const SampleCount = TimeDomainWaveData.size();
    for ( decltype( TimeDomainWaveData.size() ) Idx = 0 ; Idx < SampleCount ; ++Idx ) {
        CurrentTimeSeries.AddXY(
            1000.0 * Idx / WaveIn::SamplesPerSec,  // Time
            TimeDomainWaveData[Idx]
        );
    }

    // freq plot
    auto const FFTPointCount = WaveIn::SampleCount;
    auto const Sf = 1.0 / double( FFTPointCount );
//auto const Sf = GetWindowEnergyScalefactor() / double( FFTPointCount );

    for ( int Idx = 0 ; Idx < FFTPointCount / 2 ; ++Idx ) {
        complex<double> const DataPoint{
            FreqDomainWaveData[Idx][0], // Re
            FreqDomainWaveData[Idx][1]  // Im
        };
        CurrentFreqSeries.AddXY(
            static_cast<double>( WaveIn::SamplesPerSec ) * Idx / FFTPointCount, // freq
//            Log ?
              20.0 * log10( max( abs( DataPoint ) * Sf * ( Idx ? 2.0 : 1.0 ), 1e-15 ) )
//            :
//              abs( Sample ) * Sf
        );
    }

    CurrentFreqSeries.EndUpdate();
    CurrentFreqSeries.Active = true;

    CurrentTimeSeries.EndUpdate();
    CurrentTimeSeries.Active = true;

    ++seriesNo_;

    auto& NextFreqSeries = GetCurrentFreqSeries();
    auto& NextTimeSeries = GetCurrentTimeSeries();

    NextFreqSeries.Active = false;
    NextFreqSeries.Clear();

    NextTimeSeries.Active = false;
    NextTimeSeries.Clear();
}
//---------------------------------------------------------------------------

bool TfrmMain::SpectrogramGradientMouseOndBIndicator( int X, int Y ) const
{
    auto const CY =
        imgSpectrogramGradient->Top - pboxSpectrogramGradientIndicator->Top +
        ( imgSpectrogramGradient->Height - 1 ) *
        cutdBThreshold_ / spectrogramdBFloor;

    static constexpr auto TW = 8;

    TRect HandleRect(
        pboxSpectrogramGradientIndicator->ClientRect.Right - TW,
        CY - TW / 2,
        pboxSpectrogramGradientIndicator->ClientRect.Right,
        CY + TW - TW / 2
    );

    return HandleRect.PtInRect( TPoint( X, Y ) );
}
//---------------------------------------------------------------------------

Gdiplus::Color TfrmMain::GetHandleColor( bool Active )
{
    return
        GdiplusUtils::TColorToGdiplusColor(
            TColor( ColorToRGB( Active ? clHighlight : clCaptionText ) ), 255
        );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pboxSpectrogramGradientIndicatorPaint(TObject *Sender)
{
    static constexpr auto TW = 5.0F;

    auto const CY =
        imgSpectrogramGradient->Top - pboxSpectrogramGradientIndicator->Top +
        ( imgSpectrogramGradient->Height - 1 ) *
        cutdBThreshold_ / spectrogramdBFloor;
    Gdiplus::Graphics g( pboxSpectrogramGradientIndicator->Canvas->Handle );
    g.SetSmoothingMode( Gdiplus::SmoothingModeAntiAlias );

    array<Gdiplus::PointF,3> Ind;

    auto W = pboxSpectrogramGradientIndicator->Width - 1;

    Ind[0] = Gdiplus::PointF( W     , CY      );
    Ind[1] = Gdiplus::PointF( W - TW, CY - TW );
    Ind[2] = Gdiplus::PointF( W - TW, CY + TW );

    Gdiplus::SolidBrush const ClBrush{
        GetHandleColor( spectrogramGradientIndicatorTracking_ )
    };

    g.FillPolygon( &ClBrush, &Ind[0], Ind.size() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pboxSpectrogramGradientIndicatorMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if ( Button == mbLeft ) {
        if ( SpectrogramGradientMouseOndBIndicator( X, Y ) ) {
            spectrogramGradientIndicatorTracking_ = true;
            pboxSpectrogramGradientIndicator->Invalidate();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pboxSpectrogramGradientIndicatorMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
    spectrogramGradientIndicatorTracking_ = false;
    pboxSpectrogramGradientIndicator->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pboxSpectrogramGradientIndicatorMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y)
{
    if ( spectrogramGradientIndicatorTracking_ ) {
        auto CY =
            static_cast<double>(
                min(
                    max( 0, Y ),
                    pboxSpectrogramGradientIndicator->Height
                )
            );
        int Val =
            CY * ( spectrogramThresholdMin_ - spectrogramThresholdMax_ ) /
            pboxSpectrogramGradientIndicator->Height +
            spectrogramThresholdMax_;

        if ( cutdBThreshold_ != Val ) {
            cutdBThreshold_ = Val;
            UpdateThresholddBDisplayControl();
        }
    }
}
//---------------------------------------------------------------------------

double TfrmMain::CutHandleXCoordFromFreq( double Freq ) const
{
    auto const SGTL = pboxSpectrogram->ClientToScreen( TPoint( 0, 0 ) );
    auto const FCTL = pboxFreqCuts->ClientToScreen( TPoint( 0, 0 ) );

    auto const x1 = SGTL.X - FCTL.X;
    auto const x2 = x1 + pboxSpectrogram->Width;
    return Freq * ( x2 - x1 ) / WaveIn::SamplesPerSec * 2.0 + x1;
}
//---------------------------------------------------------------------------

double TfrmMain::CutHandleFreqFromXCoord( int X ) const
{
    auto const SGTL = pboxSpectrogram->ClientToScreen( TPoint( 0, 0 ) );
    auto const FCTL = pboxFreqCuts->ClientToScreen( TPoint( 0, 0 ) );

    auto const x1 = static_cast<int>( SGTL.X - FCTL.X );
    auto const x2 = x1 + pboxSpectrogram->Width;
    X = min( max( X, x1 ), x2 );
    return static_cast<double>( X - x1 ) / ( x2 - x1 ) * WaveIn::SamplesPerSec / 2.0;
}
//---------------------------------------------------------------------------

int TfrmMain::CutMarkerXCoordFromFreq( double Freq ) const
{
    return Freq * 2.0 * pboxSpectrogram->Width / WaveIn::SamplesPerSec;
}
//---------------------------------------------------------------------------

TfrmMain::FreqCutHandlePolygonType TfrmMain::GetFreqCutHandlePolygon(
                                            double Freq, bool Mirror ) const
{
    static constexpr auto TW = 8.0F;

    FreqCutHandlePolygonType Ret;
    auto X = CutHandleXCoordFromFreq( Freq );

    Ret[0] = Gdiplus::PointF( X,  0 );
    Ret[1] = Gdiplus::PointF( X, 2.0F * TW );
    Ret[2] = Gdiplus::PointF( X + ( Mirror ? 1.0 : -1.0 ) * TW, 2.0F * TW );

    return Ret;
}
//---------------------------------------------------------------------------

TfrmMain::FreqCutHandlePolygonType TfrmMain::GetFreqCutLoHandlePolygon() const
{
    return GetFreqCutHandlePolygon( cutLoFreq_, false );
}
//---------------------------------------------------------------------------

TfrmMain::FreqCutHandlePolygonType TfrmMain::GetFreqCutHiHandlePolygon() const
{
    return GetFreqCutHandlePolygon( cutHiFreq_, true );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pboxFreqCutsPaint(TObject *Sender)
{
    auto const LoHandlePoly = GetFreqCutLoHandlePolygon();

    Gdiplus::Font GFont(
        pboxFreqCuts->Font->Name.c_str(), pboxFreqCuts->Font->Size
    );

    Gdiplus::Graphics g( pboxFreqCuts->Canvas->Handle );
    g.SetSmoothingMode( Gdiplus::SmoothingModeAntiAlias );

    Gdiplus::SolidBrush const LoBrush{
        GetHandleColor( freqCutTracking_ == FreqCutTracking::Lo )
    };

    Gdiplus::StringFormat LoStringFormat;
    LoStringFormat.SetAlignment( Gdiplus::StringAlignment ::StringAlignmentFar );
    LoStringFormat.SetLineAlignment( Gdiplus::StringAlignment ::StringAlignmentNear );

    g.DrawString(
        Format(
            _T( "%1.0f Hz" ),
            ARRAYOFCONST( ( static_cast<long double>( cutLoFreq_ ) ) )
        ).c_str(), -1,
        &GFont,
        Gdiplus::RectF(
            0, LoHandlePoly[1].Y + 2,
            LoHandlePoly[1].X, pboxFreqCuts->Height
        ),
        &LoStringFormat,
        &LoBrush
    );

    g.FillPolygon( &LoBrush, &LoHandlePoly[0], LoHandlePoly.size() );

    auto const HiHandlePoly = GetFreqCutHiHandlePolygon();

    Gdiplus::SolidBrush const HiBrush{
        GetHandleColor( freqCutTracking_ == FreqCutTracking::Hi )
    };

    Gdiplus::StringFormat HiStringFormat;
    HiStringFormat.SetAlignment( Gdiplus::StringAlignment ::StringAlignmentNear );
    HiStringFormat.SetLineAlignment( Gdiplus::StringAlignment ::StringAlignmentNear );

    g.DrawString(
        Format(
            _T( "%1.0f Hz" ),
            ARRAYOFCONST( ( static_cast<long double>( cutHiFreq_ ) ) )
        ).c_str(), -1,
        &GFont,
        Gdiplus::RectF(
            HiHandlePoly[1].X, HiHandlePoly[1].Y + 2,
            pboxFreqCuts->Width, pboxFreqCuts->Height
        ),
        &HiStringFormat,
        &HiBrush
    );

    g.FillPolygon( &HiBrush, &HiHandlePoly[0], HiHandlePoly.size() );
}
//---------------------------------------------------------------------------

bool TfrmMain::SpectrogramGradientMouseOnLoFreqIndicator( int X, int Y ) const
{
    auto Poly = GetFreqCutLoHandlePolygon();
    Gdiplus::GraphicsPath gp;
    gp.AddPolygon( &Poly[0], Poly.size() );
    Gdiplus::Graphics g( pboxFreqCuts->Canvas->Handle );
    return gp.IsVisible( X, Y, &g );
}
//---------------------------------------------------------------------------

bool TfrmMain::SpectrogramGradientMouseOnHiFreqIndicator( int X, int Y ) const
{
    auto Poly = GetFreqCutHiHandlePolygon();
    Gdiplus::GraphicsPath gp;
    gp.AddPolygon( &Poly[0], Poly.size() );
    Gdiplus::Graphics g( pboxFreqCuts->Canvas->Handle );
    return gp.IsVisible( X, Y, &g );
}
//---------------------------------------------------------------------------

void TfrmMain::SetCutLoFreq( double Val )
{
    if ( Val != cutLoFreq_ ) {
        cutLoFreq_ = Val;
        UpdateFreqCutControls();
        pboxSpectrogram->Invalidate();
    }
}
//---------------------------------------------------------------------------

void TfrmMain::SetCutHiFreq( double Val )
{
    if ( Val != cutHiFreq_ ) {
        cutHiFreq_ = Val;
        UpdateFreqCutControls();
        pboxSpectrogram->Invalidate();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pboxFreqCutsMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    if ( Button == mbLeft ) {
        if ( SpectrogramGradientMouseOnLoFreqIndicator( X, Y ) ) {
            freqCutTracking_ = FreqCutTracking::Lo;
            pboxFreqCuts->Invalidate();
        }
        else if ( SpectrogramGradientMouseOnHiFreqIndicator( X, Y ) ) {
            freqCutTracking_ = FreqCutTracking::Hi;
            pboxFreqCuts->Invalidate();
        }
        else {
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pboxFreqCutsMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    freqCutTracking_ = FreqCutTracking::None;
    pboxFreqCuts->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pboxFreqCutsMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
    switch ( freqCutTracking_ ) {
        case FreqCutTracking::Lo:
            CutLoFreq =
                min(
                    CutHandleFreqFromXCoord( X ),
                    CutHiFreq -
                    static_cast<double>( WaveIn::SamplesPerSec ) /
                    WaveIn::SampleCount
                );
            break;
        case FreqCutTracking::Hi:
            CutHiFreq =
                max(
                    CutHandleFreqFromXCoord( X ),
                    CutLoFreq +
                    static_cast<double>( WaveIn::SamplesPerSec ) /
                    WaveIn::SampleCount
                );
            break;
        default:
            break;
    }
}
//---------------------------------------------------------------------------

void TfrmMain::UpdateFreqCutControls()
{
    pboxFreqCuts->Invalidate();
    SeriesFreqCuts->BeginUpdate();
    SeriesFreqCuts->XValues->Items[0] = cutLoFreq_;
    SeriesFreqCuts->XValues->Items[1] = cutLoFreq_;
    SeriesFreqCuts->XValues->Items[2] = cutHiFreq_;
    SeriesFreqCuts->XValues->Items[3] = cutHiFreq_;
    SeriesFreqCuts->EndUpdate();
    chartFreq->Invalidate();
}
//---------------------------------------------------------------------------

int TfrmMain::SampleIdxFromFreq( double Freq ) const
{
    return Freq * WaveIn::SampleCount / WaveIn::SamplesPerSec;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pboxPeaksTimepointPaint(TObject *Sender)
{
    TPaintBox& PaintBox = static_cast<TPaintBox&>( *Sender );
    auto& PCanvas = *PaintBox.Canvas;
    auto const TimeWindowWidth =
        static_cast<double>( WaveIn::SampleCount ) *
        pboxSpectrogram->Height / ( WaveIn::SamplesPerSec * 86400.0 );

    TDateTime const TimeWindowEnd = Now();
    TDateTime const TimeWindowStart = TimeWindowEnd - TimeWindowWidth;

    Gdiplus::Graphics g( PaintBox.Canvas->Handle );
    g.SetSmoothingMode( Gdiplus::SmoothingModeAntiAlias );
    auto MColor = Gdiplus::Color( 0xFF, 0xFF, 0xFF, 0x00 );
    Gdiplus::Pen MarkerPen( MColor, 1 );
    Gdiplus::SolidBrush const TextBrush{ MColor };

    Gdiplus::StringFormat StrFmt;
    StrFmt.SetAlignment( Gdiplus::StringAlignment ::StringAlignmentFar );
    StrFmt.SetLineAlignment( Gdiplus::StringAlignment ::StringAlignmentCenter );

    Gdiplus::Font GFont( PaintBox.Font->Name.c_str(), PaintBox.Font->Size );

    auto It =
        std::upper_bound(
            begin( peaksAbsTimePoint_ ),
            end( peaksAbsTimePoint_ ),
            TimeWindowStart
        );

    for ( ; It != end( peaksAbsTimePoint_ ) ; ++It ) {
        auto const TimePoint = *It;

        if ( TimePoint > TimeWindowEnd ) {
            break;
        }
        else if ( TimePoint > TimeWindowStart ) {
            auto Span = static_cast<double>( *It - TimeWindowStart );

            auto const Y =
                static_cast<double>( *It - TimeWindowStart ) *
                pboxSpectrogram->Height / TimeWindowWidth;
            g.DrawLine( &MarkerPen, PaintBox.Width / 2, Y, PaintBox.Width, Y );

            auto n = distance( begin( peaksAbsTimePoint_ ), It ) + 1;

            g.DrawString(
                Format( _T( "%d" ), ARRAYOFCONST( ( n ) ) ).c_str(), -1,
                &GFont,
                Gdiplus::RectF( 0, Y - 10, PaintBox.Width / 2, 20 ),
                &StrFmt,
                &TextBrush
            );
        }
    }
}
//---------------------------------------------------------------------------

void TfrmMain::PeakDetection( FFTWContN const & FreqDomainWaveData,
                              TDateTime TimePoint )
{
    if ( Now() >= peakDetInhTime_ ) {
        auto const Sf = 1.0 / double( WaveIn::SampleCount );
        auto Start = max( SampleIdxFromFreq( cutLoFreq_ ), 0 );
        auto const End =
            min( SampleIdxFromFreq( cutHiFreq_ ) + 1, WaveIn::SampleCount / 2 );
        size_t HitCnt {};
        for ( auto Idx = Start ; Idx != End ; ++Idx ) {
            complex<double> DataPoint{
                FreqDomainWaveData[Idx][0], FreqDomainWaveData[Idx][1]
            };
            auto const A = abs( DataPoint ) * Sf * ( Idx ? 2.0 : 1.0 );
            auto const W = 20.0 * log10( max( A, 1e-15 ) );
            if ( W >= cutdBThreshold_ ) {
                ++HitCnt;
            }
        }
        double Conf = static_cast<double>( peakDetConf_ ) / 100.0;


        size_t const MaxDetectCnt =
            max(
                1,
                static_cast<int>(
                    static_cast<double>( WaveIn::SamplesPerSec ) *
                    PeakDetectionMinDuration /
                    1000.0 / WaveIn::SampleCount
                )
            );


        if ( static_cast<double>( HitCnt ) / ( End - Start ) >= Conf ) {
            ++detectCnt_;
            if ( detectCnt_ == 1 ) {
                detectTimePoint_ = TimePoint;
            }
            else if ( detectCnt_ == MaxDetectCnt ) {

LogMessage(
    Format(
        _T( "Peak @%s\n" ),
        ARRAYOFCONST( ( ( startListeningTimePoint_ - detectTimePoint_ ).FormatString( _T( "nn:ss:zzz" ) ) ) )
    )
);
                peaksAbsTimePoint_.push_back( detectTimePoint_ );
                //peaksAbsTimePoint_.push_back( TimePoint );
                peakDetInhTime_ =
                    IncMilliSecond( Now(), PeakMinDetectionTimeDistance );
                detectCnt_ = 0;
            }
        }
        else {
            detectCnt_ = 0;
            peakDetInhTime_ = Now();
        }
    }
    else {
        detectCnt_ = 0;
    }
}
//---------------------------------------------------------------------------

void TfrmMain::SetPeakDetectionMinDuration( int Val )
{
    if ( Val != peakDetMinDuration_ ) {
        peakDetMinDuration_ = min( max( Val, 20 ), 500 );
    }
}
//---------------------------------------------------------------------------

void TfrmMain::SetPeakDetectionConfidence( int Val )
{
    if ( Val != peakDetConf_ ) {
        peakDetConf_ = min( max( Val, 10 ), 100 );
    }
}
//---------------------------------------------------------------------------

void TfrmMain::SetPeakMinDetectionTimeDistance( int Val )
{
    if ( Val != peakMinDetectionTimeDistance_ ) {
        peakMinDetectionTimeDistance_ = min( max( Val, 0 ), 10000 );
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actWaveSetParametersExecute(TObject *Sender)
{
    auto Form = make_unique<TfrmWaveParameters>( nullptr );
    Form->PeakDetectionConfidence = PeakDetectionConfidence;
    Form->PeakDetectionMinDuration = PeakDetectionMinDuration;
    Form->PeakMinDetectionTimeDistance = PeakMinDetectionTimeDistance;
    if ( Form->ShowModal() == mrOk ) {
        PeakDetectionConfidence = Form->PeakDetectionConfidence;
        PeakDetectionMinDuration = Form->PeakDetectionMinDuration;
        PeakMinDetectionTimeDistance = Form->PeakMinDetectionTimeDistance;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actWaveSetParametersUpdate(TObject *Sender)
{
    TAction& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = !waveIn_ && !tmrGare->Enabled;
}
//---------------------------------------------------------------------------

void TfrmMain::ShowAdditionalSettingsWarning()
{
    if ( ModbusTesterEnabled || PollingTimerDisabled || IgnoreDoor ) {
        String Message;

        if ( ModbusTesterEnabled ) {
            Message += _D( " - Tester del protocollo Modbus\r\n" );
        }

        if ( PollingTimerDisabled ) {
            Message += _D( " - Verifica porta sagome aperta disabilitata\r\n" );
        }

        if ( IgnoreDoor ) {
            Message += _D( " - **ATTENZIONE** Contatto porta aperta ignorato\r\n" );
        }

        TaskDialog1->Text = Message;
        TaskDialog1->Execute();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormShow(TObject *Sender)
{
    ShowAdditionalSettingsWarning();
}
//---------------------------------------------------------------------------

double TfrmMain::GetMediaDuration( String AudioFile ) const
{
    try {
        Mp3 mp3;
        mp3.LoadFromFile( AudioFile );
        return mp3.GetDuration() / 10000000.0;
    }
    catch ( Exception const & E ) {
        return WavInfo( AudioFile ).GetDuration();
    }
}
//---------------------------------------------------------------------------

