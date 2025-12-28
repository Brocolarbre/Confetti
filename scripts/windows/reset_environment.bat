:: This script removes the external dependencies from their respective folders as well as vcpkg and premake
:: The workspace and build are also cleared

@echo off

setlocal
for /d %%D in (.\external\*) do (
    if /I not "%%~nxD"=="vcpkg_manifests" if /I not "%%~nxD"=="licenses" (
        rmdir /s /q "%%D"
    )
)

del /q .\external\*.* 2>nul

mkdir .\external\include
mkdir .\external\lib\release
mkdir .\external\lib\debug
mkdir .\external\bin\release
mkdir .\external\bin\debug

type nul > .\external\include\.gitkeep
type nul > .\external\lib\release\.gitkeep
type nul > .\external\lib\debug\.gitkeep
type nul > .\external\bin\release\.gitkeep
type nul > .\external\bin\debug\.gitkeep

call .\scripts\windows\clear_build.bat
call .\scripts\windows\reset_workspace.bat

echo Environment reset.
endlocal