:: This script installs vcpkg and premake, an optional path for an existing installation of vcpkg can be specified
:: The external dependencies described in the manifest files are installed using vcpkg
:: The workspace is generated using premake

@echo off

setlocal
set "vcpkg_path=.\external\vcpkg"
set "skip_vcpkg=0"

:parse_args
if "%~1"=="" goto args_done
if "%~1"=="--vcpkg-path" (
    if not "%~2"=="" (
        set "vcpkg_path=%~2"
        shift
    )
) else if "%~1"=="--skip-vcpkg" (
    set "skip_vcpkg=1"
)
shift
goto parse_args

:args_done

if "%skip_vcpkg%"=="0" (
    call .\scripts\windows\install_vcpkg.bat --path "%vcpkg_path%"
    if errorlevel 1 exit /b 1

    call "%vcpkg_path%\vcpkg.exe" install --clean-buildtrees-after-build --x-install-root=.\external\vcpkg_installed --x-manifest-root=.\external\vcpkg_manifests\x64-windows --triplet x64-windows
    call "%vcpkg_path%\vcpkg.exe" install --clean-buildtrees-after-build --x-install-root=.\external\vcpkg_installed --x-manifest-root=.\external\vcpkg_manifests\x64-windows-static-md --triplet x64-windows-static-md
)

mkdir .\external\premake
call .\scripts\windows\install_premake.bat --path .\external\premake
if errorlevel 1 exit /b 1

call .\scripts\windows\set_workspace.bat
if errorlevel 1 exit /b 1

echo Environment set.
endlocal