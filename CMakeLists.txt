cmake_minimum_required(VERSION 3.17)
project(encodeInput C)

set(CMAKE_C_STANDARD 11)

#set(APP_SRC ./src)
#set(APP_INC ./inc)

#include_directories(${APP_SRC})
#include_directories(${APP_INC})

include_directories(./src)
include_directories(./inc)

#set(
#    SOURCE_FILES
#        ${APP_SRC}/main.c
#        ${APP_SRC}/middleman.c
#        ${APP_SRC}/encoder.c
#        ${APP_INC}/encodeInput.h
#)

add_executable(encodeInput
        ./src/main.c
        ./src/middleman.c
        ./src/encoder.c
        ./inc/encodeInput.h
        )