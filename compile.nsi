; MyAppInstaller.nsi

; Set the name of the installer
Outfile "MyAppInstaller.exe"

; Set the installation directory
InstallDir "$PROGRAMFILES64\MyApp"

; Default section
Section

    ; Set output path for installed files
    SetOutPath $INSTDIR

    ; Copy files from source directory to installation directory
    File /r "C:\Users\carte\Desktop\code\PlatformerTut\bin\release\*.*"

    ; Create shortcuts
    CreateShortCut "$DESKTOP\main.lnk" "$INSTDIR\release\main.exe"
    ; CreateShortCut "$SMPROGRAMS\main\main.lnk" "$INSTDIR\release\main.exe"

SectionEnd

; Uninstaller section
Section "Uninstall"

    ; Remove installed files
    Delete "$INSTDIR\*.*"

    ; Remove shortcuts
    Delete "$DESKTOP\main.lnk"
    Delete "$SMPROGRAMS\main\main.lnk"

    ; Remove installation directory
    RMDir "$INSTDIR"

SectionEnd

; Set uninstaller name
; UninstallDisplayName "Uninstall MyApp"