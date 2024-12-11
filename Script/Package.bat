@echo off

echo Start "Package.bat" script...

set solutionPath=%~dp0..\Solution

@REM 프로젝트가 존재하지 않으면 프로젝트를 생성합니다.
if not exist "%solutionPath%" (
    echo Can't find Visual Studio Solution...
    GOTO:EOF
)

@REM 패키징할 모드입니다.
SET mode=%1

@REM 패키징할 모드의 유효성을 검사합니다.
if "%mode%" == "Debug" (
    echo Build "%mode%" mode...
) else if "%mode%" == "Release" (
    echo Build "%mode%" mode...
) else if "%mode%" == "RelWithDebInfo" (
    echo Build "%mode%" mode...
) else if "%mode%" == "MinSizeRel" (
    echo Build "%mode%" mode...
) else (
    echo "%mode%" is illegal mode...
    GOTO:EOF
)

set currentPath=%~dp0

pushd "%currentPath%"
pushd "%solutionPath%"

cpack -C %mode% -G NSIS

popd
popd