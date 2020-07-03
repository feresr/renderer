project(sandbox)

file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(sandbox ${src})

target_include_directories(sandbox PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(sandbox PRIVATE engine)


