@echo off

echo Start "BuildSolution.bat" script...

@REM CMake가 설치되었는지 확인합니다.
@echo off
where cmake > nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo CMake is installed on this system...
) else (
    echo CMake is not installed on this system...
    GOTO:EOF
)

@REM Visual Studio 버전입니다. 
SET vs=%1

@REM visual studio 버전을 검사합니다. 2019 혹은 2022입니다.
if "%vs%" == "vs2019" (
    SET visualstudio="Visual Studio 16 2019"
    echo Visual Studio version is "%vs%"...
) else if "%vs%" == "vs2022" (
    SET visualstudio="Visual Studio 17 2022"
    echo Visual Studio version is "%vs%"...
) else (
    echo Visual Studio version "%vs%" is illegal...
    GOTO:EOF
)

@REM 프로젝트가 존재하지 않으면 프로젝트를 생성합니다.
if not exist %~dp0..\..\Solution (
    echo Start generate Visual Studio Solution...
    mkdir %~dp0..\..\Solution

    pushd %~dp0
    pushd %~dp0..\..\Solution

    cmake .. -G %visualstudio% -A "x64"

    popd
    popd
)

@REM 빌드할 모드입니다.
SET mode=%2

@REM 빌드 모드의 유효성을 검사합니다.
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

pushd %~dp0
pushd %~dp0..\..\Solution

cmake --build . --config %mode% --clean-first --parallel  

popd
popd