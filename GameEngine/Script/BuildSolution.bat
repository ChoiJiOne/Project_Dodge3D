@echo off
setlocal enabledelayedexpansion

@REM 게임 엔진 경로입니다.
SET engine_path=%~dp0..\

@REM vswhere 실행 파일 경로입니다.
SET vswhere_path=%engine_path%Bin\vswhere.exe

@REM 빌드할 프로젝트 이름입니다.
SET project=%1

@REM 빌드할 모드입니다.
SET mode=%2

@REM 빌드할 솔루션 경로입니다.
SET solution_path=Solution\%project%.sln

@REM 프로젝트 이름의 유효성을 검사합니다.
if "%project%" == "" (
    echo project name is empty...
    GOTO:EOF
)

@REM 빌드 모드의 유효성을 검사합니다.
if "%mode%" == "Debug" (
    echo Build %mode% mode game...
) else if "%mode%" == "Release" (
    echo Build %mode% mode game...
) else if "%mode%" == "Shipping" (
    echo Build %mode% mode game...
) else (
    echo %mode% is illegal mode...
    GOTO:EOF
)

for /f "usebackq tokens=*" %%i in (`%vswhere_path% -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
    set path="%%i"
)

%path% %solution_path% -property:Configuration=%mode% -target:Rebuild