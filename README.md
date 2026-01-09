# HotelManagementSystem

A simple C++ console application for managing basic hotel operations.

## Project Overview

This repository contains a single-file C++ application `HotelManagementSystem.cpp` implementing a basic hotel management program (reservations, check-in/out, and simple record storage). It's intended as a starting point for learning C++ console applications and for expanding into a fuller system.

## Features

- Console-based interface
- Simple reservation and guest record handling
- Single-file implementation for easy compilation

## Requirements

- A C++ compiler supporting C++11 or later (e.g., MinGW-w64, MSVC, or clang)
- Windows (instructions below), but code should compile on other platforms with a compatible compiler.

## Build and Run (Windows - Command Prompt / PowerShell)

1. Open a terminal in the project folder (where `HotelManagementSystem.cpp` is located).
2. Compile with `g++` (MinGW) or use Visual Studio tools.

Using MinGW (g++):

```powershell
g++ -std=c++11 -O2 -Wall -o HotelManagementSystem HotelManagementSystem.cpp
.\HotelManagementSystem.exe
```

Using Visual Studio Developer Command Prompt (MSVC):

```powershell
cl /EHsc /O2 HotelManagementSystem.cpp
HotelManagementSystem.exe
```

## Usage

Run the compiled executable and follow the on-screen prompts. Typical operations include creating reservations, checking guests in/out, and listing records.

## Contributing

Contributions are welcome. If you plan to expand this project consider:

- Adding a proper data persistence layer (files or database)
- Splitting functionality into multiple source/header files
- Adding unit tests and CI

## License

This project has no license file. If you want to make it open-source, add a `LICENSE` file (for example, MIT license).

## Contact

Repository owner: Abdul-Kabeer78
