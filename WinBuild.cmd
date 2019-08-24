@echo off
echo ------- .:: AEColorPicker ::. -------
set sPrjFile=AEColorPicker.sln
set sConfigNameRelease="Release|x86"
set sConfigNameRelease2="Release|x64"


set sVSPathName=%SYSTEMDRIVE%\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.exe

@echo on
"%sVSPathName%" %sPrjFile% /Rebuild %sConfigNameRelease%

"%sVSPathName%" %sPrjFile% /Rebuild %sConfigNameRelease2%


echo [%sPrjName%]: compiling end.
