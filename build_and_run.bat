@echo off
REM Hotel Management System Build Script
cd /d D:\HotelManagementSystem

REM Check if g++ is available
where g++ >nul 2>nul
if %ERRORLEVEL% == 0 (
    echo Compiling with g++...
    g++ -std=c++11 -O2 -Wall -o HotelManagementSystem.exe HotelManagementSystem.cpp
    if %ERRORLEVEL% == 0 (
        echo Build successful!
        echo Running program...
        HotelManagementSystem.exe
    ) else (
        echo Build failed!
        pause
    )
) else (
    echo g++ not found. Please install MinGW-w64.
    echo You can download it from: https://www.mingw-w64.org/
    pause
)
