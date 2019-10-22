@setlocal
@echo off

:: Init submodules
git submodule update --init --recursive

:: Build Botan
call "build_botan.cmd"

:: Build directory
if not exist build_v141_x64 (
  mkdir build_v141_x64
)
pushd "build_v141_x64"

:: Setup developer command prompt for Visual Studio
call "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/Common7/Tools/VsDevCmd.bat" -arch=x64
:: Setup the environement for VS 2017 x64
call "%VS140COMNTOOLS%../../VC/vcvarsall.bat" x64

:: Configure and build
cmake .. -G "Visual Studio 15 2017 Win64" -T host=x64
cmake --build . --config Release --parallel 4

popd
pause
@endlocal
