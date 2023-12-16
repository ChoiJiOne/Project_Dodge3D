@echo off

SET project=ProjectA
SET mode=Shipping
SET script=GameEngine\Script\BuildSolution.bat

%script% %project% %mode%