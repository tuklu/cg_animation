@echo off
setlocal enabledelayedexpansion
title CG Animation Auto Setup

echo ============================
echo   CG Animation Setup (Win)
echo ============================

:: SETUP DIRS
set "MINGW_DIR=%ProgramFiles%\mingw-w64"
set "FREEGLUT_URL=https://www.transmissionzero.co.uk/files/software/development/freeglut-MSVC.zip"
set "FREEGLUT_ZIP=freeglut.zip"
set "FREEGLUT_DIR=C:\freeglut"

:: 1. CHECK & INSTALL MINGW-W64
where gcc >nul 2>nul
if %errorlevel% neq 0 (
    echo 🔽 GCC not found. Downloading MinGW-w64 installer...
    powershell -Command "Invoke-WebRequest -Uri https://sourceforge.net/projects/mingw-w64/files/latest/download -OutFile mingw-w64.exe"
    echo 🛠 Running installer...
    start /wait mingw-w64.exe
    echo ⚠️ Please ensure you select architecture = x86_64 and threads = posix in the installer.
    echo.
)

:: Try reloading PATH
echo ✅ Trying to detect gcc again...
set PATH=%PATH%;C:\Program Files\mingw-w64\mingw64\bin
where gcc >nul 2>nul
if %errorlevel% neq 0 (
    echo ❌ Still can't find gcc. Please add MinGW bin folder to PATH manually.
    pause
    exit /b
) else (
    echo ✅ gcc is now available.
)

:: 2. DOWNLOAD & EXTRACT FREEGLUT
if not exist "%FREEGLUT_DIR%\include\GL\freeglut.h" (
    echo 🔽 Downloading freeglut precompiled binaries...
    powershell -Command "Invoke-WebRequest -Uri %FREEGLUT_URL% -OutFile %FREEGLUT_ZIP%"
    
    echo 📦 Extracting to %FREEGLUT_DIR%...
    powershell -Command "Expand-Archive -LiteralPath '%FREEGLUT_ZIP%' -DestinationPath '%FREEGLUT_DIR%'"

    echo ✅ freeglut extracted.
)

:: 3. COMPILE
echo 🔧 Compiling animation with:
echo gcc main.c -IC:\freeglut\include -LC:\freeglut\lib -lfreeglut -lopengl32 -o cg_anim.exe

gcc main.c -IC:\freeglut\include -LC:\freeglut\lib -lfreeglut -lopengl32 -o cg_anim.exe

:: 4. COPY DLL
echo 🔄 Copying freeglut.dll...
copy "%FREEGLUT_DIR%\bin\x64\freeglut.dll" cg_anim.exe >nul

echo.
echo ✅ Done! Run your animation with:
echo cg_anim.exe

pause