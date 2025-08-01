# To-do Server/Client project

A cross-platform client-server To-Do application using **gRPC**.  
- 🔧 Server: C++20, gRPC, CMake, vcpkg  
- 🖥️ Client: WPF (C#/XAML), gRPC client  
- 📦 Dependency Management: vcpkg  
- 🛠 Build System: CMake + Ninja (multi-platform)

## 🚀 Building the Project

### 🔧 Prerequisites

- [vcpkg](https://github.com/microsoft/vcpkg)
- [Ninja](https://ninja-build.org/)
- [CMake ≥ 3.21](https://cmake.org/download/)
- [.NET 9 SDK](https://dotnet.microsoft.com/ru-ru/download/dotnet/9.0) (for the client project)
- Visual Studio 2022 (Windows) or GCC/Clang (Linux) (for compiling)

### 🛠 Steps

#### 1. Install vcpkg
As said in [vcpkg documentation](https://learn.microsoft.com/uk-ua/vcpkg/get_started/get-started-vs?pivots=shell-cmd) you have to first navigate to the prefered location and clone the Git repository:
```
git clone https://github.com/microsoft/vcpkg.git
```
After cloning vcpkg, run the following commands to install it:
```
cd vcpkg && bootstrap-vcpkg.bat
```
You also need to set up the environment variable `VCPKG_ROOT` to point to the vcpkg directory, and include it to the `PATH` variable.

For wWindows you might use this:
```
set "VCPKG_ROOT=C:\path\to\vcpkg"
set PATH=%VCPKG_ROOT%;%PATH%
```
For Linux, the alternative would be:
```
export VCPKG_ROOT=/path/to/vcpkg
export PATH=$VCPKG_ROOT:$PATH
```
Also, you might need as well to specify the triplet for your platform inside `VCPKG_TARGET_TRIPLET` variable, e.g. `x64-windows`/`x86-windows` for Windows (`x64-linux`/`x86-linux` for Linux). This would be required for future instructions.

Windows:
```
set VCPKG_TARGET_TRIPLET=PLATFORM
```
Linux:
```
export VCPKG_TARGET_TRIPLET=PLATFORM
```

#### 2. Install Ninja
Installing Ninja doesn't require any complex steps, for Windows platform you can use the command inside `CMD.EXE` terminal:
```
winget install --id=Ninja-build.Ninja  -e
```
For Linux, you can use your package manager, e.g. for Ubuntu:
```
sudo apt install ninja-build
```

#### 3. Install CMake
Installing CMake is also straightforward, just head to the [CMake download page](https://cmake.org/download/) and download the installer for your platform.

#### 4. Install .NET SDK
For the client project, you need to have .NET SDK installed. You can download and install it from the [.NET download page](https://dotnet.microsoft.com/ru-ru/download/dotnet/9.0).

#### 5. Clone the Repository
Clone the repository to your prefered location:
```
git clone https://github.com/FranklinMar/To-do-Server
```

#### 6. Installing dependencies
After successfully cloning the repositor, we will use the `vcpkg` tool to install the required dependencies, specifically gRPC and Protobuf.

First, Navigate to the server directory:
```
cd to-doserver
```
Then run the following command:
```
vcpkg install
```
This will install all the required dependencies for the server project, including gRPC and Protobuf. In case it doesn't, run the following commands:
```
vcpkg new --application
vcpkg add port grpc
vcpkg add port protobuf
```
This will create new manifest files for the vcpkg packages. After that, run the `vcpkg install` command again to install the dependencies.

#### 7. Generate gRPC code
The server requires a code to be generated from the `.proto` file to build services and server. At first, navigate to the `To-doServer` directory:
```
cd to-doserver
```
It is an important step to navigate to this specific directory.
After that, we have 2 types of scripts inside `scripts` folder, each for different platform.
For Windows, you would want to run the `.bat` file, while for Linux, you would want to run the `.sh` file.

Running script on Windows:
```
"./scripts/proto-gen.bat"
```
Running script on Linux:
```
"./scripts/proto-gen.sh"
```
After this, a `genproto` folder will be created inside the `To-doServer` directory, containing at least 4 files for the server to build successfully.
If that didn't happen, please make sure you have set up the environment variables correctly, and that you are running the script from the correct directory.
The script must be run from "REPOSITORY_ROOT/To-doServer/" directory.

#### 8. Build the Project
After successfully generating the gRPC code, you can build the server project.
To do that, return to the repository root directory:
```
cd ..
```
Then, run a following `cmake` command to build the CMakeCache files required for the build:

Windows:
```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake
```
Linux:
```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
```

Now, you would need to navigate to the `build` directory:
```
cd build
```
And run the final building command:
```
cmake --build . --config Release
```

After this, you should have the server and client executables built successfully inside the `/build/` directory in respective subdirectories.
Use the respective `.exe` files to run both server and client applications.

## 📝 Design Explanation

The design choices regarding the project were based on pretty simple reasons:

### Why gRPC?
This project is required to be a cross-platform application, so gRPC was selected as a communication protocol.

- **gRPC**: It is a modern, high-performance RPC framework that supports multiple languages and platforms, 
making it suitable for cross-platform applications. Not to mention it's advantages over standart transfer protocols, 
such as performance, ability of real-time synchronization, and more.
- The specifications of the projects required the client to be written on WPF (C#/XAML) platform. Because of 
gRPC's support for multiple languages, the choice was pretty obvious.

### Why CMake as a Build System?
Due to the previous point, gRPC is a bit tricky to set up, especially on Windows platform. Because of that, it was clear
that we need a build system that would allow us to easily manage dependencies and build the project on multiple platforms. 
This would allow us to have a robust application that can be built and run on different operating systems without much hassle.
This is also why the project uses `vcpkg` as a dependency manager, as it integrates well with CMake and allows for easy 
management of libraries.

### Faced challenges
- **gRPC Setup**: The first and probably the most challenging part was setting up gRPC and Protobuf. Unfortunatelly, the	
official documentation is not very clear on how to set it up, especially when encountering issues with the build process,
especially with CMake on Windows platform. In total, it took almost 4 days to figure out how to set it up correctly, using every possible
option available, including using manual build with CMake, `WSL`, `Linux Virtual Machine` and, finally, `vcpkg`. Not to mention the
tricky part of insuring that CMake would use the installed packages.
- **Cross-Platform Compatibility**: Ensuring that the `proto-gen` script for generating C++ code was a tricky part as well, because
as mentioned before, this project is cross-platform and it was required for the scripts to work regardless.
- **Real-time Synchronization**: The last and probably the most satisfying part was implementing the real-time synchronization on the client
application. At first, it seemed too complex and confusing, but after doing some deeper research on how gRPC streaming works, it was just a matter of time.
