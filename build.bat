@echo off

set CXX=g++
set CXXFLAGS=-O3 -std=c++11
set BINDIR=bin

if not exist %BINDIR% mkdir %BINDIR%

if "%1" == "all" goto all
if "%1" == "serial" goto serial
if "%1" == "parallel" goto parallel
if "%1" == "clean" goto clean
goto end

:all
call %0 serial
call %0 parallel
goto end

:serial
echo Compiling serial version...
%CXX% %CXXFLAGS% -o %BINDIR%\nbody_serial main_serial.cpp
goto end

:parallel
echo Compiling parallel version...
%CXX% %CXXFLAGS% -fopenmp -o %BINDIR%\nbody_parallel main_parallel.cpp
goto end

:clean
echo Cleaning up...
del /f %BINDIR%\nbody_serial.exe
del /f %BINDIR%\nbody_parallel.exe
goto end

:end
echo Done.
