@echo off

REM Fetch parent folder.
set "parent_dir=%cd%\.."

REM Display parent directory for debugging
echo Parent directory: %parent_dir%

REM Fetch configfile path.
for %%f in ("%parent_dir%\Makefile") do set "configfile_path=%%f"

REM Display configfile path for debugging
echo ConfigFile path: %configfile_path%

REM List files in the parent directory for debugging
dir "%parent_dir%"

REM Return if not find a solution file
if not defined configfile_path (
    echo ConfigFile is not found
    PAUSE
    exit /b 1
)

REM To parent directory
cd "%parent_dir%"

REM Make with configure
call make config=debug

PAUSE