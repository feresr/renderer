project(sandbox)



file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
#file(GLOB vendor ${CMAKE_CURRENT_SOURCE_DIR}/vendor/*.c ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/*.c)
add_executable(sandbox ${src} ${vendor})

target_include_directories(sandbox PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)

target_link_libraries(sandbox PRIVATE engine)





