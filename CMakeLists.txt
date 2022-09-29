file(CREATE_LINK ../data data SYMBOLIC)

project(test)
file(GLOB test_SRC "src/*.h" "src/*.c")
add_executable(test ${test_SRC})
target_link_libraries(test allegro allegro_primitives allegro_image allegro_font allegro_ttf)