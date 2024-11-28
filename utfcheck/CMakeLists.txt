cmake_minimum_required(VERSION 3.5)
project(utfcheck)
    add_executable(utfcheck
            main.c)
    add_executable(utfcheck_w
            main_w.c)
    add_definitions(-ggdb -O0)

