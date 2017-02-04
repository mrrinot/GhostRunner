; TCR compliant Sample install script.
; Basically put this file in the root for what you want included in the installer,
;   then put everything into the subdirectories as listed in the installer below.
;   Remember to change the AppId
;   Thanks to Dan Weiss (dweiss@digipen.edu) for the original version.
;
; !!NOTE!!
; There are three steps that you must perform in order to customize this script
;   for your project (see "TODO" below):
;   1) Generate a new GUID for your game.
;   2) Search-and-Replace "MyGame" with your game name.
;   3) Update the redistributables required for your game.

[Setup]
; !!NOTE!!: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; TODO: (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{F03D4FB5-7970-261D-901F-91A6EAA745A0}

; Standard app data stuff
; TODO: Search-and-Replace "GameTest" with your game name
AppName=GhostRunner                                                                                                              
AppVerName=GhistRunner Version 1.0
AppPublisher=Epitech
AppPublisherURL=http://www.epitech.eu/
AppSupportURL=http://www.epitech.eu/

; Default path to the file storage directory.
; {pf} is the default program files directory set by Windows
DefaultDirName={pf}\Epitech-KMU\GhostRunner

; Start menu directory
DefaultGroupName=Epitech-KMU\GhostRunner

; Output directory for the installer.
OutputDir=.\INSTALLERR

; Setup executable installer
OutputBaseFilename=GhostRunner_Setup

; Compression scheme for the installer. Check Inno Setup help files for more options.
Compression=lzma
SolidCompression=yes

; Path to the icon for the installer (TCR check requires custom icon)
SetupIconFile=.\INSTALLERFILES\SetupIcon.ico

; This allows the installer to run without admin privileges, which means you can't install
; in the Program Files, or change the registry. This is done to allow installation on Sandbox
; or other intermediate directory
PrivilegesRequired=none

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
; Creates an installer option to allow/disallow desktop shortcut
; Checked by default
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"

; This is the list of files that the installer should grab and install.
;
; Destination Directory Notes
;   {app} is the root directory that you will be installing to.
;   {temp} is a temporary directory that Windows sets that gets deleted after the
;      installer quits.
;   {userdocs} is the directory for My Documents/Documents on Windows XP, Vista, and 7.
;
; For more information on default paths to install to, check the "Constants" article
;   in the Inno Setup 5 documentation.
;
; I recommend placing any installers for required stuff (DirectX, PhysX, etc)
;   in the general structure below to keep things neat for you.
[Files]
; The game directoy is exactly what you want your install directory in program files to look like
Source: .\GAMEDIRECTORY\*; DestDir: {app}; Flags: ignoreversion recursesubdirs createallsubdirs

; Include the redistributable programs and install them to the temp directory
; TODO: Update this list with the correct redistributables for your game.
;       If your game uses DirectX, then please refer to the following forum posting:
;	        https://distance.digipen.edu/mod/forum/discuss.php?d=19674&parent=39276
;Source: .\REDIST\*; DestDir: {tmp}; Flags: ignoreversion

; This is the list of shortcuts that the installer will setup for you.
; Of note, this will create the uninstaller automatically.
;
; Directory Notes
;   {group} is the start menu location that the game will install shortcuts to.
;   {commondesktop} is your Windows desktop directory.
[Icons]
Name: {group}\GhostRunner; Filename: {app}\GhostRunner.exe; WorkingDir: {app}; IconFilename: "{app}\Icon.ico"
Name: {group}\{cm:UninstallProgram,GhostRunner}; Filename: {uninstallexe}
Name: {commondesktop}\GhostRunner; Filename: {app}\GhostRunner.exe; Tasks: desktopicon; WorkingDir: {app}; IconFilename: "{app}\Icon.ico"

; List of items to execute in the installer.
; Note that this will run all executables in their silent versions as required by the TCRs.
;
; The last item being run is the installer option to automatically launch the game after
;   the installer exits as required by the TCRs.
; TODO: Update this list with the correct redistributables for your game.
[Run]
; Filename: {tmp}\vcredist_x86.exe; Parameters: /q; StatusMsg: Installing Visual C++ 2008 Redistributable...
; Filename: {tmp}\dxsetup.exe; Parameters: /q; StatusMsg: Installing DirectX...
Filename: {app}\GhostRunner.exe; Description: {cm:LaunchProgram,GhostRunner}; Flags: nowait postinstall skipifsilent
