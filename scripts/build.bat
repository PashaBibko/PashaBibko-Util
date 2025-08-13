@echo off

:: Makes sure the working directory is repo-root and not scripts/ ::

for %%I in ("%~dp0.") do set "SCRIPT_DIRNAME=%%~nxI"

if /i "%SCRIPT_DIRNAME%"=="scripts" (
	cd /d "%~dp0.."
)

:: Prepares the build files ::
mkdir build
cmake . -G Ninja -B build -DCMAKE_BUILD_TYPE=Release

:: Builds the project ::
cmake --build build
