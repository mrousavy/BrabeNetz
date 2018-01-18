@echo off
msbuild ..\BrabeNetz\BrabeNetz.vcxproj /p:Configuration=Release /p:Platform=x64
msbuild ..\BrabeNetz\BrabeNetz.vcxproj /p:Configuration=Release /p:Platform=x86
msbuild ..\BrabeNetz\BrabeNetz.vcxproj /p:Configuration=Debug /p:Platform=x64
msbuild ..\BrabeNetz\BrabeNetz.vcxproj /p:Configuration=Debug /p:Platform=x86
D:\nuget.exe pack BrabeNetz.nuspec
