@echo off

@REM 실행할 모드입니다.
SET mode=%1

@REM 실행 파일 경로입니다.
SET path=%~dp0..\..\Solution\Client\%mode%

@REM 셰이더 파일 경로입니다.
SET shader=%~dp0..\..\GameEngine\Shader\

@REM 리소스 파일 경로입니다.
SET resource=%~dp0..\..\Client\Resource\

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

start %path%\Client.exe shaderPath=%shader% resourcePath=%resource%