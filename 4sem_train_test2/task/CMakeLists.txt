cmake_minimum_required(VERSION 3.1)
project(task2)

set(SOURCE ./src/main.cpp ./src/myjson.cpp ./src/generator.cpp ./src/restaraunt.cpp)
set(SERVER ./src/server.cpp ./src/myjson.cpp ./src/generator.cpp ./src/reg.cpp ./src/restaraunt.cpp)
set(CLIENT ./src/client.cpp ./src/restaraunt.cpp)

include_directories(./inc)
include_directories(./ext/cpp-httplib-master)

add_executable(main ${SOURCE})

add_executable(server ${SERVER})

add_executable(client ${CLIENT})

add_custom_command(
TARGET main
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${CMAKE_SOURCE_DIR}/data/restNames.txt
${CMAKE_CURRENT_BINARY_DIR}/restNames.txt
)

add_custom_command(
TARGET main
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${CMAKE_SOURCE_DIR}/data/restRatings.txt
${CMAKE_CURRENT_BINARY_DIR}/restRatings.txt
)