cmake_minimum_required(VERSION 3.0...3.10)
project(solution)
if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

## include_directories(/usr/local/include /usr/include src)
## link_directories(/usr/local/lib)

add_definitions(-ggdb)

## executble
add_executable(solution
solution.c
)

add_custom_target(test
COMMAND	./solution
COMMENT "Run Tests"
DEPENDS solution
)

##target_link_libraries(nonestl curl json-c)

install(TARGETS solution DESTINATION bin)
