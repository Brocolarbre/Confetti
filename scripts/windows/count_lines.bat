:: This script counts source files, directories and lines in the project

@echo off
setlocal enabledelayedexpansion

set cppCount=0
set hppCount=0
set cCount=0
set hCount=0
set totalLines=0
set folderCount=0

for /d /r %%d in (*) do (
    set "p=%%d"
    if "!p:\external\=!"=="!p!" (
        set /a folderCount+=1
    )
)

for /r %%f in (*.cpp *.hpp *.c *.h) do (
    set "p=%%f"

    if "!p:\external\=!"=="!p!" (

        if /i "%%~xf"==".cpp" set /a cppCount+=1
        if /i "%%~xf"==".hpp" set /a hppCount+=1
        if /i "%%~xf"==".c"   set /a cCount+=1
        if /i "%%~xf"==".h"   set /a hCount+=1

        for /f %%l in ('find /v /c "" ^< "%%f"') do (
            set /a totalLines+=%%l
        )
    )
)

echo -----------------------------
echo Folders: %folderCount%
echo -----------------------------
echo Files:
echo   .cpp: %cppCount%
echo   .hpp: %hppCount%
echo   .c: %cCount%
echo   .h: %hCount%
echo -----------------------------
echo Lines: %totalLines%
echo -----------------------------

pause