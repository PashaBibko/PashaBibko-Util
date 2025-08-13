@echo off

:: Sets up the optional CMake build settings ::

set "CMake_Config=%1"
if "%CMake_Config%"=="" set "CMake_Config=-DCMAKE_BUILD_TYPE=Release"

:: Makes sure the working directory is repo-root and not scripts/ ::

for %%I in ("%~dp0.") do set "SCRIPT_DIRNAME=%%~nxI"

if /i "%SCRIPT_DIRNAME%"=="scripts" (
	cd /d "%~dp0.."
)

:: Prepares the build files ::
mkdir build
cmake . -G Ninja -B build %CMake_Config%

:: Builds the project ::
cmake --build build
