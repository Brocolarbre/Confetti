:: This script generates the workspace using the premake scripts, the arguments are forwarded to the premake scripts

@echo off

setlocal
set "target=vs2022"
if "%~1"=="--target" if not "%~2"=="" set "target=%~2"

if not exist .\external\premake\premake5.exe (
    echo Premake not found, run the setup_environment script first.
    exit /b 1
)
.\external\premake\premake5.exe "%target%"
echo Workspace set.
endlocal