## Supported Platforms
- Windows (x86)
- Linux

## Unsupported Platforms
- MacOS
- Windows (x64)

Note: PassPro may still build and run as intended on unsupported platforms. Unfortunately,
we do not have any developers on these platforms to verify PassPro functionality.

## Requrements
- CMAKE 3.5 or above
- GCC or MinGw supporting QT 5.15.11
- OpenSSL
- QT 5.15.11
- GNU Make
- QT Creator (QT Creator build only)
- VSCode (VSCode build only)
- VSCode C++ Build Extensions (VSCode build only)

## Build Instructions - QT Creator (Recommended)
- Clone the repository
- Clone submodules (git submodule init && git submodule update)
- Open QT Creator and open the CMakeLists.txt file to open the project
- Press the run button

## Build Instructions - VSCode
- Clone the repository
- Update submodules (git submodule init && git submodule update)
- Open VSCode and navigate to the cloned project
- Press build on the bottom

## Build Instructions - Terminal
- Open the terminal
- Clone the repository (git clone <url>)
- Clone submodules (git submodule init && git submodule update)
- Navigate to the project root (using cd <target directory>)
- Execute "cmake ." to generate the makefile
- Execute "make -o PassPro" to generate an executable
