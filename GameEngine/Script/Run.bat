@echo off

@REM 실행 파일 경로입니다.
SET exe_path=%~dp0..\..\Solution\bin\Win64

@REM 실행할 파일 이름입니다.
SET exe_file=%1

@REM 실행할 모드입니다.
SET mode=%2

@REM 실행할 파일 이름의 유효성을 검사합니다.
if "%exe_file%" == "" (
    echo execute file name is empty...
    GOTO:EOF
)

@REM 빌드 모드의 유효성을 검사합니다.
if "%mode%" == "Debug" (
    echo Run %mode% mode game...
) else if "%mode%" == "Release" (
    echo Run %mode% mode game...
) else if "%mode%" == "Shipping" (
    echo Run %mode% mode game...
) else (
    echo %mode% is illegal mode...
    GOTO:EOF
)

start %exe_path%\%mode%\%exe_file%.exe