cmake_minimum_required(VERSION 3.5)
project(solution)
if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

## include_directories(/usr/local/include /usr/include src)
## link_directories(/usr/local/lib)

add_definitions(-ggdb)

## forktest
add_executable(solution
solution.c
)

add_custom_target(test
COMMAND	./solution -ivvq2
COMMENT "Run Tests"
)

##target_link_libraries(nonestl curl json-c)

install(TARGETS solution DESTINATION bin)
