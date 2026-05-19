; Inno Setup script for Sagome

#define MyAppExeName "Sagome.exe"
#define MyAppExePath "Win64x\Release\" + MyAppExeName
#define MyAppPublisher GetStringFileInfo(MyAppExePath, "CompanyName")
#define MyAppName GetStringFileInfo(MyAppExePath, "ProductName")
#define MyAppVersion GetStringFileInfo(MyAppExePath, "ProductVersion")
#define MyAppRegistryKey "Software\" + MyAppPublisher + "\" + MyAppName + "\" + MyAppVersion

[Setup]
AppId={{E0E7B9B8-4B2E-4F07-9DAE-0A8B49F723A1}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={autopf64}\{#MyAppPublisher}\{#MyAppName}\{#MyAppVersion}
DefaultGroupName={#MyAppName}
DisableProgramGroupPage=yes
OutputDir=Setup
OutputBaseFilename=SagomeSetup-{#MyAppVersion}
Compression=lzma
SolidCompression=yes
WizardStyle=modern
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
UninstallDisplayIcon={app}\{#MyAppExeName}

[Languages]
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#MyAppExePath}"; DestDir: "{app}"; Flags: ignoreversion
Source: "FFTW\fftw-3.3-dll64\libfftw3-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Risorse\*.wav"; DestDir: "{app}"; Flags: ignoreversion

[Registry]
Root: HKCU; Subkey: "Software\{#MyAppPublisher}"; Flags: uninsdeletekeyifempty
Root: HKCU; Subkey: "Software\{#MyAppPublisher}\{#MyAppName}"; Flags: uninsdeletekeyifempty
Root: HKCU; Subkey: "{#MyAppRegistryKey}"; Flags: uninsdeletekeyifempty
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; Flags: uninsdeletekeyifempty
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: dword; ValueName: "Bottom"; ValueData: "$000002c5"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: dword; ValueName: "Left"; ValueData: "$000000b8"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: string; ValueName: "ModbusProtocolName"; ValueData: "Modbus RTU"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: dword; ValueName: "Right"; ValueData: "$00000482"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: string; ValueName: "State"; ValueData: "wsMaximized"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: dword; ValueName: "Top"; ValueData: "$0000002e"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: dword; ValueName: "FnIdx"; ValueData: "$00000000"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: dword; ValueName: "MainPanelSize"; ValueData: "$00000164"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: dword; ValueName: "PeakDetectionConfidence"; ValueData: "$0000004b"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: dword; ValueName: "Threshold"; ValueData: "$ffffffda"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "{#MyAppRegistryKey}\frmMain"; ValueType: string; ValueName: "SoundFolder"; ValueData: "C:\Users\OPeratore\Desktop\Sagome\MP3"; Flags: uninsdeletevalue

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
