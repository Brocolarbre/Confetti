:: This script installs vcpkg and premake, an optional path for an existing installation of vcpkg can be specified
:: The external dependencies described in the manifest files are installed using vcpkg
:: The workspace is generated using premake

@echo off

setlocal
set "vcpkg_path=.\external\vcpkg"
if "%~1"=="--vcpkg-path" if not "%~2"=="" set "vcpkg_path=%~2"

call .\scripts\windows\install_vcpkg.bat --path "%vcpkg_path%"
if errorlevel 1 exit /b 1

mkdir .\external\premake
call .\scripts\windows\install_premake.bat --path .\external\premake
if errorlevel 1 exit /b 1

call "%vcpkg_path%\vcpkg.exe" install --clean-buildtrees-after-build --x-install-root=.\external\vcpkg_installed --x-manifest-root=.\external\vcpkg_manifests\x64-windows --triplet x64-windows
call "%vcpkg_path%\vcpkg.exe" install --clean-buildtrees-after-build --x-install-root=.\external\vcpkg_installed --x-manifest-root=.\external\vcpkg_manifests\x64-windows-static-md --triplet x64-windows-static-md

call .\scripts\windows\set_workspace.bat
if errorlevel 1 exit /b 1

echo Environment set.
endlocal