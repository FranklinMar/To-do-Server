﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)
# set(CMAKE_TOOLCHAIN_FILE D:/Programs/vcpkg/scripts/buildsystems/vcpkg.cmake)
# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (To-do)

# Include sub-projects.
add_subdirectory ("To-doServer")
add_custom_target(To-doClient ALL
    COMMAND dotnet build ${CMAKE_SOURCE_DIR}/To-doClient/To-doClient.csproj
            -c Debug
            -o ${CMAKE_BINARY_DIR}/To-doClient/
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/To-doClient
)