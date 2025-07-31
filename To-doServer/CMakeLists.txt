# CMakeList.txt : CMake project for To-doServer, include source and define
# Add source to this project's executable.
cmake_minimum_required(VERSION 3.20)
project(To-doServer)


# execute_process(
# 	COMMAND ${PROJECT_SOURCE_DIR}/scripts/proto-gen.bat
#)

# Variables for genproto lib target
set(GENPROTO_LIB "genproto_lib")
set(GENPROTO_DIR "${PROJECT_SOURCE_DIR}/genproto")

# Necessary package
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(utf8_range REQUIRED)


# Loop through genproto lib files
file(GLOB_RECURSE PROTO_SRC "${GENPROTO_DIR}/*.pb.cc")
file(GLOB_RECURSE PROTO_HDR "${GENPROTO_DIR}/*.pb.h")

add_library(${GENPROTO_LIB} ${PROTO_SRC} ${PHOTO_HDR})

target_link_libraries(${GENPROTO_LIB}
 	PUBLIC
 		protobuf::libprotobuf
 		gRPC::grpc++
 		utf8_range::utf8_range
 		utf8_range::utf8_validity
)


target_include_directories(${GENPROTO_LIB}
 	PUBLIC
		${GENPROTO_DIR}
)

# add_executable (To-doServer "To-doServer.cpp" "To-doServer.h")

# Source files
add_executable(${PROJECT_NAME}
    src/To-doServer.cpp
    src/ToDo_Service.cpp)

target_link_libraries(${PROJECT_NAME}
 	PRIVATE
 		${GENPROTO_LIB}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
	${PROJECT_SOURCE_DIR}/include
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET To-doServer PROPERTY CXX_STANDARD 20)
endif()