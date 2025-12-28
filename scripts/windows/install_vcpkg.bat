:: This script installs vcpkg at the provided path (--path) or in the current working directory if no path is provided
:: If vcpkg is already installed, it is updated without overriding

@echo off

setlocal
set "vcpkg_path=."
if "%~1"=="--path" if not "%~2"=="" set "vcpkg_path=%~2"

if not exist "%vcpkg_path%" (
    echo Cloning vcpkg...
    mkdir "%vcpkg_path%"
    git clone https://github.com/microsoft/vcpkg.git "%vcpkg_path%"
	echo Initializing vcpkg...
	call "%vcpkg_path%\bootstrap-vcpkg.bat" -disableMetrics
) else (
    echo Updating vcpkg...
    pushd "%vcpkg_path%"
    git pull
    popd
)
endlocal