
# N-Body Simulation Project

## Overview

This project contains an implementation of the N-Body problem, a classic problem in computational physics. The solution includes both serial and parallel implementations.

## Directory Structure

```
projectpp/
├── body.h                      # Header file containing body definitions
├── build.bat                   # Batch script for building the project on Windows
├── main_parallel.cpp           # Parallel implementation of the N-Body simulation
├── main_serial.cpp             # Serial implementation of the N-Body simulation
├── Makefile                    # Makefile for building the project on Unix-based systems
├── README.md                   # Project documentation
├── .vscode/                    # VSCode configuration files
│   ├── c_cpp_properties.json
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
└── bin/                        # Directory for compiled binaries
    ├── nbody_parallel.exe      # Compiled parallel implementation (Windows)
    └── nbody_serial.exe        # Compiled serial implementation (Windows)
```

## Getting Started

### Prerequisites

- **Windows**
  - A C++ compiler like MinGW
  - Visual Studio Code (optional, for using provided VSCode configurations)
- **Unix-based systems (Linux, macOS)**
  - `gcc` or `g++` compiler

### Building the Project

#### On Windows

1. Open a Command Prompt or PowerShell.
2. Navigate to the project directory.
3. Run the build script:
   ```sh
   build.bat
   ```

#### On Unix-based Systems

1. Open a terminal.
2. Navigate to the project directory.
3. Run `make`:
   ```sh
   make
   ```

### Running the Simulation

#### Serial Implementation

- **Windows**:
  ```sh
  bin\nbody_serial.exe
  ```
- **Unix-based systems**:
  ```sh
  ./bin/nbody_serial
  ```

#### Parallel Implementation

- **Windows**:
  ```sh
  bin\nbody_parallel.exe
  ```
- **Unix-based systems**:
  ```sh
  ./bin/nbody_parallel
  ```

## Configuration

The `.vscode` directory contains configuration files for Visual Studio Code, which can help in setting up the development environment quickly.

- `c_cpp_properties.json`: Configures include paths and other settings for C++ IntelliSense.
- `launch.json`: Configures debugging settings.
- `settings.json`: General settings for the VSCode workspace.
- `tasks.json`: Defines build tasks.

## File Descriptions

- **`body.h`**: Header file defining the properties and behaviors of the bodies in the simulation.
- **`main_serial.cpp`**: Contains the code for the serial implementation of the N-Body problem.
- **`main_parallel.cpp`**: Contains the code for the parallel implementation of the N-Body problem.
- **`Makefile`**: Build instructions for Unix-based systems.
- **`build.bat`**: Build script for Windows systems.
- **`bin/`**: Directory containing compiled executables.

## Authors

- Fadi Abbara
- Hayan Azzam
- Baraa Alkilany
- Anas Zahran
- Omar Radwan

## Professor

- Ali Vaisifard

## Contributing

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -m 'Add some feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Open a pull request.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

- University Of Europe For Applied Sciences  - Potsadm
