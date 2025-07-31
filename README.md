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
As said in [vcpkg documentation](https://learn.microsoft.com/uk-ua/vcpkg/get_started/get-started-vs?pivots=shell-cmd) you have to first
```
git clone https://github.com/microsoft/vcpkg.git
```
After cloning vcpkg, run the following commands to install it:
```
cd vcpkg && bootstrap-vcpkg.bat
```
You also need to set up the environment variable `VCPKG_ROOT` to point to the vcpkg directory, and include it to the `PATH` variable.
```
set "VCPKG_ROOT=C:\path\to\vcpkg"
set PATH=%VCPKG_ROOT%;%PATH%
```
Also, you might need as well to specify the triplet for your platform inside `VCPKG_TARGET_TRIPLET` variable, e.g. `x64-windows`/`x86-windows` for Windows (`x64-linux`/`x86-linux` for Linux). This would be required for future instructions.
```
set VCPKG_TARGET_TRIPLET=PLATFORM
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

After this, you should have the server executable built successfully inside the `/build/To-doServer/` directory.
Use the respective `.exe` files to run both server and client applications.