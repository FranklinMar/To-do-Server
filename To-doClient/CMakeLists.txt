# CMakeList.txt : CMake project for To-doServer, include source and define
cmake_minimum_required(VERSION 3.8)
project(To-doClient VERSION 0.1.0)

add_custom_target(ToDoClient ALL
    COMMAND dotnet build ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.csproj
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building WPF C# Client"
)

#[[include(CSharpUtilities)

add_executable(WpfApp
    ${CMAKE_CURRENT_SOURCE_DIR}/App.xaml.cs
    ${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.xaml.cs
    ${CMAKE_CURRENT_SOURCE_DIR}/App.xaml
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.xaml
)
# Build the WPF client, depending on code generation
add_custom_target(ToDoClient ALL
    COMMAND dotnet build ${CMAKE_CURRENT_SOURCE_DIR}/To-doClient.csproj
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS GenerateCSharpGrpc
    COMMENT "Building WPF C# Client"
)

set_property(SOURCE App.xaml PROPERTY VS_XAML_TYPE "ApplicationDefinition")

SET_PROPERTY(TARGET ${PROJECT_NAME}  PROPERTY VS_PACKAGE_REFERENCES "Serilog_2.9.0;Serilog.Sinks.Console_3.1.1")

target_compile_options(${PROJECT_NAME} PRIVATE "/langversion:latest")
# Visual Studio project type GUIDs for WPF and C#
set_target_properties(${PROJECT_NAME} PROPERTIES
    DOTNET_SDK "Microsoft.NET.Sdk"
    DOTNET_TARGET_FRAMEWORK "net9.0-windows"
    # These GUIDs define the project types, which control things like what context menus are available in VS.
    # The first is WPF, the second is C#.
    WIN32_EXECUTABLE TRUE
    VS_GLOBAL_UseWPF "true"
    VS_GLOBAL_PROJECT_TYPES "{60dc8134-eba5-43b8-bcc9-bb4bc16c2548};{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}"
)]]#