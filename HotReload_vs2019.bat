@echo off

SET visualstudio=vs2019
SET project=ProjectA
SET script=GameEngine\Script\HotReload.bat

%script% %visualstudio% %project%