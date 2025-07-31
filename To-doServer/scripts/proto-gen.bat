::@echo off

:: Get current directory
set CURRENT_DIR=%cd%
:: cd ..
:: set PROJECT_DIR=%cd%
:: cd %CURRENT_DIR%
if exist "%CURRENT_DIR%\genproto" (

	:: del /q "%CURRENT_DIR%\genproto\*"
	rd /s /q "%CURRENT_DIR%\genproto"
)

:: for /f "delims=" %%F in ('where grpc_cpp_plugin.exe') do set GRPC_CPP_PLUGIN=%%F
:: echo %GRPC_CPP_PLUGIN%
:: Create genproto folder if it does not exist

md "%CURRENT_DIR%\genproto"

:: Check if VCPKG_ROOT is set
::if "%VCPKG_ROOT%"=="" (
::    echo [ERROR] VCPKG_ROOT environment variable is not set.
::    exit /b 1
::)
::if "%VCPKG_TARGET_TRIPLET%"=="" (
::    echo [ERROR] VCPKG_TARGET_TRIPLET environment variable is not set.
::    exit /b 1
::)


:: Iterate over all subdirectories inside protos
:: for /d %%D in ("%CURRENT_DIR%\protos\*") do (
::     echo Processing %%D
::     for %%F in ("%%D\*.proto") do (
::         echo Generating from %%F
::         protoc -I "%CURRENT_DIR%\protos" --cpp_out="%CURRENT_DIR%\genproto" "%%F"       
::     )
:: )
set PROTOC_EXE=%VCPKG_ROOT%\installed\%VCPKG_TARGET_TRIPLET%\tools\protobuf\protoc.exe
set GRPC_PLUGIN_EXE=%VCPKG_ROOT%\installed\%VCPKG_TARGET_TRIPLET%\tools\grpc\grpc_cpp_plugin.exe
echo %PROTOC_EXE%
echo %GRPC_PLUGIN_EXE%

for %%F in ("%CURRENT_DIR%\..\protos\*.proto") do (
	echo Generating from %%F
    "%PROTOC_EXE%" -I "%CURRENT_DIR%\..\protos" --cpp_out="%CURRENT_DIR%\genproto" "%%F"
	"%PROTOC_EXE%" -I "%CURRENT_DIR%\..\protos" --grpc_out="%CURRENT_DIR%\genproto" --plugin=protoc-gen-grpc="%GRPC_PLUGIN_EXE%" "%%F"    
)
    :: "D:\Programs\vcpkg\installed\x64-windows\tools\protobuf\protoc.exe" -I "%CURRENT_DIR%\..\protos" --grpc_out="%CURRENT_DIR%\genproto" --plugin=protoc-gen-grpc="D:\Programs\vcpkg\installed\x64-windows\tools\grpc\grpc_cpp_plugin.exe" "%%F"    
echo Done.

:: protoc -I "%CURRENT_DIR%\protos" -I "%%D" --cpp_out="%CURRENT_DIR%\genproto" --grpc_out="%CURRENT_DIR%\genproto" "%%F"
:: protoc -I "%cd%" --cpp_out="%cd%" --grpc_out="%cd%" "todo.proto"
:: protoc -I "%cd%" --cpp_out="%cd%" "todo.proto"
:: --grpc_out="%CURRENT_DIR%\genproto" --plugin=protoc-gen-grpc="where grpc_cpp_plugin" "%%F"