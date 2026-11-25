@echo off
title Employee Management System - DSA in C
cd /d "%~dp0"

if exist "EmployeeManagement.exe" (
    "EmployeeManagement.exe"
    exit /b
)

echo [*] Compiling EmployeeManagement system (main.c)...
gcc -std=c99 -Wall -Wextra main.c -o EmployeeManagement.exe
if %errorlevel% equ 0 (
    "EmployeeManagement.exe"
) else (
    echo [!] Compilation failed. Please make sure GCC (MinGW) is installed and on your PATH.
    pause
)
