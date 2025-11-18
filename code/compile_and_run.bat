
@echo off
echo This is a file to make running the program simpler, faster and easier, instead of stressing one's self with
echo uneccesary stress of running Msys and having to deal with path file issues.
echo .
echo  All one needs is to install this file into thier PC and runn it and it works successfully
echo --------------------------------
echo   Student Record System Compiler
echo ---------------------------------
echo.
echo.
echo.
echo.
echo Compiling the program...
gcc -o student_system student_record_system.c
REM THis is a loop that allows us to debug the file and even checks the file if it has errors.
REM IF the file hass even a single error the .bat file wont even open. 
if %errorlevel% == 0 (
    echo Compilation successful!
    echo.
    echo Running the program...
    echo 
    student_system.exe
) else (
    echo Compilation failed! Please check your code.
    pause
)
