@echo off

SET visualstudio=vs2022
SET project=ProjectA
SET script=GameEngine\Script\HotReload.bat

%script% %visualstudio% %project%