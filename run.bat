cls
:loop

set PROMPT=$G$G
g++ main.cpp -o main.out
echo off
cls
main.out
echo.
echo.
echo.
echo Press any key to restart application
pause>nul


goto loop

