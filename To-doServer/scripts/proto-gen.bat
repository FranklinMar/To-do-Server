@echo off

:: Get current directory
set CURRENT_DIR=%cd%
for /f "delims=" %%F in ('where grpc_cpp_plugin.exe') do set GRPC_CPP_PLUGIN=%%F
:: echo %GRPC_CPP_PLUGIN%
:: Create genproto folder if it does not exist
if exist "%CURRENT_DIR%\genproto" (

	:: del /q "%CURRENT_DIR%\genproto\*"
	rd /s /q "%CURRENT_DIR%\genproto"
)

md "%CURRENT_DIR%\genproto"

:: Iterate over all subdirectories inside protos
:: for /d %%D in ("%CURRENT_DIR%\protos\*") do (
::     echo Processing %%D
::     for %%F in ("%%D\*.proto") do (
::         echo Generating from %%F
::         protoc -I "%CURRENT_DIR%\protos" --cpp_out="%CURRENT_DIR%\genproto" "%%F"       
::     )
:: )
for %%F in ("%CURRENT_DIR%\protos\*.proto") do (
	echo Generating from %%F
	protoc -I "%CURRENT_DIR%\protos" --cpp_out="%CURRENT_DIR%\genproto" "%%F"
	protoc -I "%CURRENT_DIR%\protos" --grpc_out="%CURRENT_DIR%\genproto" --plugin=protoc-gen-grpc="%GRPC_CPP_PLUGIN%" "%%F"    
)
echo Done.

:: protoc -I "%CURRENT_DIR%\protos" -I "%%D" --cpp_out="%CURRENT_DIR%\genproto" --grpc_out="%CURRENT_DIR%\genproto" "%%F"
:: protoc -I "%cd%" --cpp_out="%cd%" --grpc_out="%cd%" "todo.proto"
:: protoc -I "%cd%" --cpp_out="%cd%" "todo.proto"
:: --grpc_out="%CURRENT_DIR%\genproto" --plugin=protoc-gen-grpc="where grpc_cpp_plugin" "%%F"