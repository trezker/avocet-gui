cmake_minimum_required(VERSION 3.16)
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


file(CREATE_LINK ../data data SYMBOLIC)

project(test)
file(GLOB test_SRC "src/*.h" "src/*.c")
add_library(avocetgui STATIC ${test_SRC})
add_executable(test "test/main.c")
target_link_libraries(test avocetgui allegro allegro_primitives allegro_image allegro_font allegro_ttf)