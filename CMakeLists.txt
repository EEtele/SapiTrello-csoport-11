cmake_minimum_required(VERSION 3.17)
project(SapiTrello_csoport_11 C)

set(CMAKE_C_STANDARD 11)

include_directories(/include)

add_executable(SapiTrello src/main.c src/example.c)