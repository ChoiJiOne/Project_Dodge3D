@echo off

@REM 게임 엔진 경로입니다.
SET engine_path=%~dp0..\

@REM Premake5 실행 파일 경로입니다.
SET premake5_path=%engine_path%Bin\premake5.exe

@REM Visual Studio 버전입니다. 
SET visualstudio=%1

@REM 프로젝트 이름입니다.
SET project=%2

echo START GenerateProjectFiles.bat...

@REM visual studio 버전을 검사합니다. 2019 혹은 2022입니다.
if "%visualstudio%" == "vs2019" (
    echo Visual Studio version is %visualstudio%...
) else if "%visualstudio%" == "vs2022" (
    echo Visual Studio version is %visualstudio%...
) else (
    echo Visual Studio version %visualstudio% is illegal...
    GOTO:EOF
)

@REM 프로젝트 이름의 유효성을 검사합니다.
if "%project%" == "" (
    echo project name is empty...
    GOTO:EOF
) else (
    echo Project name is %project%
)

echo START premake5.exe...
%premake5_path% %visualstudio% %project%

echo START visual studio solution...
start Solution\%project%.sln