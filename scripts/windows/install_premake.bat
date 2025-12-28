:: This script installs premake at the provided path (--path) or in the current working directory if no path is provided

@echo off

setlocal
set "premake_path=."
if "%~1"=="--path" if not "%~2"=="" set "premake_path=%~2"

if not exist "%premake_path%\premake5.exe" (
	echo Downloading Premake...
	powershell -Command "Invoke-WebRequest -Uri 'https://github.com/premake/premake-core/releases/download/v5.0.0-beta7/premake-5.0.0-beta7-windows.zip' -OutFile 'premake.zip'"
	if not exist "%premake_path%" mkdir "%premake_path%"
	tar -xf premake.zip -C "%premake_path%"
	del "premake.zip"
)
endlocal