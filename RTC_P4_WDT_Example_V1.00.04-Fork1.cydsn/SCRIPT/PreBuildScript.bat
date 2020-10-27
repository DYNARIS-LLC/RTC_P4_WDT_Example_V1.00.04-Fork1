::@ECHO OFF
SET rootDir=%cd%
SET folder=\SCRIPT
SET fileScript=\PreBuildScript.ps1
::ECHO %rootDir%
SET cmdPath = %rootDir%%folder%%fileScript%
SET myNote = ""My Path:
SET myEnd = ""
SET myPath = %myNote%%cmdPath%%myEnd%
ECHO %cmdPath%
::PowerShell.exe -ExecutionPolicy Bypass -Command "& "%cmdPath%"
::PowerShell.exe -ExecutionPolicy Bypass -Command "& ""V:\Dynaris-V\Psoc-Sleep_Docks\2020-10-14_Testing\RTC_P4_WDT_Example_V1.00.03-Fork1\RTC_P4_WDT_Example_V1.00.03-Fork1.cydsn\SCRIPT\PreBuildScript.ps1""
PowerShell.exe -ExecutionPolicy Bypass -Command "& "".\SCRIPT\PreBuildScript.ps1"""
