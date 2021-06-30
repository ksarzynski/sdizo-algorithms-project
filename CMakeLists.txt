cmake_minimum_required(VERSION 3.19)
project(sdizo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(sdizo
        Console_app.cpp
        Console_app.h
        Edge.h
        Fifo_queue.cpp
        Fifo_queue.h
        main.cpp
        Matrix_rep.cpp
        Matrix_rep.h
        N_list_el.h
        N_list_rep.cpp
        N_list_rep.h
        Reader.cpp
        Reader.h)
