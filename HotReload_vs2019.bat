@echo off

SET visualstudio=vs2019
SET project=ProjectA
SET script=GameEngine\Script\GenerateProjectFiles.bat

%script% %visualstudio% %project% Off