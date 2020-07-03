project(engine)

find_package(glfw3 3.3 REQUIRED)
find_package(assimp REQUIRED)

file(GLOB src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/*.cpp)
file(GLOB vendor ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/*.c)
add_library(engine ${src} ${vendor})

target_include_directories(engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/)

file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC glfw assimp)