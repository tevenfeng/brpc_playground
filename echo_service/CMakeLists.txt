cmake_minimum_required(VERSION 2.4.1)

find_package(Protobuf REQUIRED)

set (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
                    /usr/include)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib
            /usr/lib)

add_compile_options(-std=c++11 -g)

include_directories(${INCLUDE_DIR})
link_directories(${LIB_DIR})

FILE(GLOB ALL_PROTOS "*.proto")

SET(PROTO_META_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})
LIST(APPEND PROTO_FLAGS -I${CMAKE_CURRENT_SOURCE_DIR})


FOREACH(FIL ${ALL_PROTOS})
    GET_FILENAME_COMPONENT(FIL_WE ${FIL} NAME_WE)

    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FIL})
    string(REGEX REPLACE "(.+)\\${FILE_NAME}.*" "\\1" FILE_PATH ${FIL})


    LIST(APPEND PROTO_SRCS "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc")
    LIST(APPEND PROTO_HDRS "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h")
 
    EXECUTE_PROCESS(
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${PROTO_META_BASE_DIR} ${FIL}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    file(COPY ${PROTO_SRCS} DESTINATION ${FILE_PATH})
    file(COPY ${PROTO_HDRS} DESTINATION ${FILE_PATH})
ENDFOREACH()

add_executable(client client.cpp ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(server server_main.cpp server.cpp ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(client
    -lgflags
    -lbrpc
    -lprotobuf
    -lleveldb
)

target_link_libraries(server
    -lgflags
    -lbrpc
    -lprotobuf
    -lleveldb
)