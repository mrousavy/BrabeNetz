@echo off
msbuild ..\BrabeNetz\BrabeNetz.vcxproj /p:Configuration=Release
msbuild ..\BrabeNetz\BrabeNetz.vcxproj /p:Configuration=Debug
D:\nuget.exe pack BrabeNetz.nuspec
