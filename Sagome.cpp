//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#pragma comment( lib, "libfftw3-3" )

//---------------------------------------------------------------------------
USEFORM("FrameSerialSettings.cpp", frmeSerialSettings); /* TFrame: File Type */
USEFORM("FormWaveParams.cpp", frmWaveParameters);
USEFORM("FrameLog.cpp", frmeLog); /* TFrame: File Type */
USEFORM("FrameModbusFunctions.cpp", frmeModbusFunctions); /* TFrame: File Type */
USEFORM("FrameProtocolSettings.cpp", frmeProtocolSettings); /* TFrame: File Type */
USEFORM("FormMain.cpp", frmMain);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
         Application->Initialize();
         Application->MainFormOnTaskBar = true;
         Application->Title = "Sagome";
         Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->Run();
         while ( Screen->FormCount ) {
            delete Screen->Forms[0];
         }
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------

