@echo off

@REM 실행할 프로젝트 이름입니다.
SET project=%1

@REM 실행할 모드입니다.
SET mode=%2

@REM 실행 파일 경로입니다.
SET path=%~dp0..\..\Solution\%project%\%mode%

@REM 실행할 파일 이름의 유효성을 검사합니다.
if %project% == "" (
    echo Project name is empty...
    GOTO:EOF
) else (
    echo Project name is "%project%"...
)

if "%mode%" == "Debug" (
    echo Run %mode% mode...
) else if "%mode%" == "Release" (
    echo Run %mode% mode game...
) else if "%mode%" == "RelWithDebInfo" (
    echo Run %mode% mode game...
) else if "%mode%" == "MinSizeRel" (
    echo Run %mode% mode game...
) else (
    echo "%mode%" is illegal mode...
    GOTO:EOF
)

start %path%\%project%.exe