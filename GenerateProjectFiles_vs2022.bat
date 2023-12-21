@echo off

SET visualstudio=vs2022
SET project=ProjectA
SET script=GameEngine\Script\GenerateProjectFiles.bat

%script% %visualstudio% %project% On