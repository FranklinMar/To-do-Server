@echo off

:: Get current directory
set CURRENT_DIR=%cd%
for /f "delims=" %%F in ('where grpc_cpp_plugin.exe') do set GRPC_CPP_PLUGIN=%%F
:: Create genproto folder if it does not exist
if exist "%CURRENT_DIR%\genproto" (

	rd /s /q "%CURRENT_DIR%\genproto"
)

md "%CURRENT_DIR%\genproto"

for %%F in ("%CURRENT_DIR%\..\protos\*.proto") do (
	echo Generating from %%F
	protoc -I "%CURRENT_DIR%\..\protos" --csharp_out="%CURRENT_DIR%\genproto" --csharp_opt=base_namespace=ToDoService "%%F"
	protoc -I "%CURRENT_DIR%\..\protos" --grpc_out="%CURRENT_DIR%\genproto" --plugin=protoc-gen-grpc="%GRPC_CPP_PLUGIN%" "%%F"    
)
echo Done.
