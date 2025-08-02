cmake_minimum_required(VERSION 3.0)
if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

include_directories(/usr/local/include /usr/include /usr/include/pgsql /usr/include/postgresql)
link_directories(/usr/local/lib)
##  posgresql test
add_executable(pqtest
main.c
)
target_link_libraries(pqtest pq)
add_definitions(-ggdb)
install(TARGETS pqtest DESTINATION bin)

