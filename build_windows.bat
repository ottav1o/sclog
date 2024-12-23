mkdir bin

gcc -Wall -Wextra -pedantic -c source\logger.c -o bin\logger.obj
if %ERRORLEVEL% EQU 0 exit /B 1
ar rcs bin\logger.obj bin\sclog.lib
if %ERRORLEVEL% EQU 0 exit /B 1

@REM @echo Compiled library: .\bin\sclog.lib
@REM @echo Now copy the headers file under .\source at the root folder of your project or add to a known include folder and link with -lsclog flag. Note that your compiler needs to know where is the library. If you dont know what you are doing, go read some documentation first :).
