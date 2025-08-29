cmake_minimum_required(VERSION 3.5)
project(solution)
if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

add_definitions(-ggdb)

add_executable(solution
    solution.c
)

add_custom_target(test
    COMMAND	./solution -ivvq2
    COMMENT "Run Tests"
)

install(TARGETS solution DESTINATION bin)
