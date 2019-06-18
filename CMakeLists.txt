cmake_minimum_required(VERSION 3.14)
project(PSS_t4)

set(CMAKE_CXX_STANDARD 14)

include_directories(T4)

add_executable(PSS_t4
        T4/cliente.c
        T4/fun.c
        T4/integral.h
        T4/jsocket.h
        T4/libjsocket.c
        T4/Makefile
        T4/parte-a.c
        T4/parte-b.c
        T4/serv.c
        T4/test-parte-a.c
        T4/test-parte-b.c
        T4/util.c
        T4/util.h
        .gitignore
        LICENSE)
