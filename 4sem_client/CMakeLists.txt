cmake_minimum_required(VERSION 3.1)
project(task3)

set(SERVER ./src/server2.cpp ./src/task.cpp ./src/reg.cpp)
set(CLIENT ./src/client.cpp)

include_directories(./inc)
include_directories(./ext)
include_directories(./ext/cpp-httplib-master)
include_directories(./ext/nlohmann)

add_executable(server ${SERVER})

add_executable(client ${CLIENT})

add_custom_command(
TARGET server
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${CMAKE_SOURCE_DIR}/data/datalist.json
${CMAKE_CURRENT_BINARY_DIR}/datalist.json
)